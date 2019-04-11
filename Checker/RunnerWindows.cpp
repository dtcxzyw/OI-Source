#include "Platforms/PlatformWindows.hpp"
#include "Runner.hpp"
#include <memory>
#include <psapi.h>
static std::pair<HANDLE, HANDLE>
launch(const Option& opt, const Handle& in,
       const Handle& out) {
    STARTUPINFOW start;
    memset(&start, 0, sizeof(start));
    start.cb = sizeof(STARTUPINFOW);
    start.dwFlags = STARTF_USESTDHANDLES;
    start.hStdInput = in.get();
    start.hStdOutput = out.get();
    start.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    PROCESS_INFORMATION info;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    winAssert(CreateProcessW(
        opt.get<fs::path>("Exec", "").c_str(), NULL,
        &sa, &sa, TRUE, CREATE_NO_WINDOW |
            CREATE_SUSPENDED | DEBUG_PROCESS,
        NULL, NULL, &start, &info));
    return std::make_pair(info.hProcess, info.hThread);
}
static RunResult runImpl(const Option& opt,
                         const Timer& timer,
                         const fs::path& in,
                         const fs::path& out) {
    Handle hjob = CreateJobObjectW(NULL, NULL);
    int64_t tlim = timer.remain(),
            mlim = opt.get<int64_t>("MemoryLimit", 0);
    {
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION limit;
        limit.BasicLimitInformation
            .PerProcessUserTimeLimit.QuadPart =
            tlim * 10;
        limit.ProcessMemoryLimit = mlim << 10;
        limit.BasicLimitInformation.LimitFlags =
            JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION |
            JOB_OBJECT_LIMIT_PROCESS_MEMORY |
            JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE |
            JOB_OBJECT_LIMIT_PROCESS_TIME;
        winAssert(SetInformationJobObject(
            hjob.get(),
            JobObjectExtendedLimitInformation, &limit,
            sizeof(limit)));
    }
    {
        JOBOBJECT_END_OF_JOB_TIME_INFORMATION action;
        action.EndOfJobTimeAction =
            JOB_OBJECT_POST_AT_END_OF_JOB;
        winAssert(SetInformationJobObject(
            hjob.get(),
            JobObjectEndOfJobTimeInformation, &action,
            sizeof(action)));
    }
    Handle port = CreateIoCompletionPort(
        INVALID_HANDLE_VALUE, 0, 0, 0);
    {
        JOBOBJECT_ASSOCIATE_COMPLETION_PORT portInfo;
        portInfo.CompletionKey = NULL;
        portInfo.CompletionPort = port.get();
        winAssert(SetInformationJobObject(
            hjob.get(),
            JobObjectAssociateCompletionPortInformation,
            &portInfo, sizeof(portInfo)));
    }
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    Handle ihnd = CreateFileW(
        in.c_str(), GENERIC_READ, FILE_SHARE_READ, &sa,
        OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN |
            FILE_ATTRIBUTE_READONLY,
        NULL);
    Handle ohnd =
        CreateFileW(out.c_str(), GENERIC_WRITE,
                    FILE_SHARE_WRITE, &sa, CREATE_NEW,
                    FILE_ATTRIBUTE_TEMPORARY, NULL);
    std::pair<HANDLE, HANDLE> phnd =
        launch(opt, ihnd, ohnd);
    Handle process(phnd.first);
    {
        Handle thread(phnd.second);
        winAssert(AssignProcessToJobObject(
            hjob.get(), process.get()));
        ResumeThread(thread.get());
    }
    while(true) {
        DWORD MSG;
        ULONG_PTR unusedA;
        LPOVERLAPPED unusedB;
        if(GetQueuedCompletionStatus(port.get(), &MSG,
                                     &unusedA,
                                     &unusedB, 0)) {
            RunResult res;
            {
                FILETIME ct, et, kt, ut;
                winAssert(
                    GetProcessTimes(process.get(), &ct,
                                    &et, &kt, &ut));
                ULARGE_INTEGER user;
                user.LowPart = ut.dwLowDateTime;
                user.HighPart = ut.dwHighDateTime;
                res.time = user.QuadPart / 10;
            }
            {
                PROCESS_MEMORY_COUNTERS info;
                winAssert(K32GetProcessMemoryInfo(
                    process.get(), &info,
                    sizeof(info)));
                res.mem = info.PeakPagefileUsage >> 10;
            }
            if(res.time > tlim) {
                res.st = Status::TLE;
                return res;
            }
            if(res.mem > mlim) {
                res.st = Status::MLE;
                return res;
            }
            DWORD exitCode;
            winAssert(GetExitCodeProcess(process.get(),
                                         &exitCode));
            bool ret = true;
            switch(MSG) {
                case JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS: {
                    res.st = Status::RE;
                    res.sig = exitCode;
                } break;
                case JOB_OBJECT_MSG_EXIT_PROCESS: {
                    res.st = Status::AC;
                    if(res.mem > mlim)
                        res.st = Status::MLE;
                    if(res.time > tlim)
                        res.st = Status::TLE;
                    if(exitCode != 0) {
                        res.st = Status::RE;
                        res.ret = RuntimeError::
                            NonzeroExitCode;
                        res.sig = exitCode;
                    }
                } break;
                case JOB_OBJECT_MSG_END_OF_PROCESS_TIME: {
                    res.st = Status::TLE;
                } break;
                case JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT: {
                    res.st = Status::MLE;
                } break;
                default:
                    ret = false;
                    break;
            }
            if(ret) {
            }
        }
        DEBUG_EVENT event;
        if(WaitForDebugEvent(&event, 0)) {
            switch(event.dwDebugEventCode) {
                case CREATE_PROCESS_DEBUG_EVENT:
                    winAssert(CloseHandle(
                        event.u.CreateProcessInfo
                            .hFile));
                    break;
                case EXCEPTION_DEBUG_EVENT: {
                    RunResult res;
                    res.st = Status::RE;
                    res.sig = event.u.Exception
                                  .ExceptionRecord
                                  .ExceptionCode;
                    TerminateJobObject(hjob.get(), 0);
                    return res;
                } break;
                case LOAD_DLL_DEBUG_EVENT:
                    winAssert(CloseHandle(
                        event.u.LoadDll.hFile));
                    break;
                case RIP_EVENT:
                    throw std::system_error(
                        event.u.RipInfo.dwError,
                        Win32APIError(SourceLocation::
                                          current()));
                    break;
            }
            winAssert(ContinueDebugEvent(
                event.dwProcessId, event.dwThreadId,
                DBG_CONTINUE));
        }
    }
}
RunResult run(const Option& opt, const Timer& timer,
              const fs::path& in,
              const fs::path& out) {
    try {
        return runImpl(opt, timer, in, out);
    } catch(const std::system_error& err) {
        setCodePage(936);
        std::cout << err.what() << std::endl;
        setCodePage(65001);
        RunResult res;
        res.st = Status::SE;
        return res;
    } catch(...) {
        std::cout << "\033[35mUnknown Error\033[0m"
                  << std::endl;
        RunResult res;
        res.st = Status::UKE;
        return res;
    }
}
