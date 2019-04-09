#include "Runner.hpp"
#include <Windows.h>
#include <experimental/source_location>
#include <memory>
#include <psapi.h>
#include <system_error>
using SourceLocation =
    std::experimental::source_location;
std::string getCallName(long) {
    return "Unknown";
}
static std::string winerr2String(int cond) {
    char buf[1024];
    if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL,
                      cond, 0, buf, sizeof(buf), 0))
        return buf;
    return "Unknown Error";
}
class Win32APIError final
    : public std::error_category {
private:
    SourceLocation mLoc;

public:
    Win32APIError(const SourceLocation& loc)
        : mLoc(loc) {}
    const char* name() const noexcept override {
        return "Win32API";
    }
    std::string
    message(int cond) const noexcept override {
        return "\033[35mSystem Error:\nError Code: " +
            std::to_string(cond) +
            "\nError Message: " + winerr2String(cond) +
            "\nFunction: " + mLoc.function_name() +
            "\nLine: " + std::to_string(mLoc.line()) +
            "\n\033[0m";
    }
    ~Win32APIError() override = default;
};
[[noreturn]] static void
reportError(const SourceLocation& loc =
                SourceLocation::current()) {
    throw std::system_error(GetLastError(),
                            Win32APIError(loc));
}
class Handle final : private Unmovable {
private:
    HANDLE mHandle;

public:
    Handle(HANDLE handle,
           const SourceLocation& loc =
               SourceLocation::current())
        : mHandle(handle) {
        if(handle == INVALID_HANDLE_VALUE ||
           handle == NULL)
            reportError(loc);
    }
    HANDLE get() const {
        return mHandle;
    }
    ~Handle() {
        CloseHandle(mHandle);
    }
};
static void assert(WINBOOL res,
                   const SourceLocation& loc =
                       SourceLocation::current()) {
    if(res == FALSE)
        reportError(loc);
}
void initRunner() {
    HANDLE ohnd = GetStdHandle(STD_OUTPUT_HANDLE);
    if(ohnd == INVALID_HANDLE_VALUE)
        reportError();
    DWORD old = 0;
    assert(GetConsoleMode(ohnd, &old));
    assert(SetConsoleMode(
        ohnd,
        old | ENABLE_VIRTUAL_TERMINAL_PROCESSING));
    assert(SetConsoleCP(65001));
}
void platformInfo() {
    system("ver");
}
static std::pair<HANDLE, HANDLE>
launch(const Option& opt, const Handle& in,
       const Handle& out) {
    STARTUPINFOW cur;
    GetStartupInfoW(&cur);
    STARTUPINFOW start;
    start.dwFlags = STARTF_USESTDHANDLES;
    start.hStdInput = in.get();
    start.hStdOutput = out.get();
    start.hStdError = cur.hStdError;
    PROCESS_INFORMATION info;
    assert(CreateProcessW(
        opt.get<fs::path>("Exec", "").c_str(), NULL,
        NULL, NULL, TRUE, CREATE_NO_WINDOW |
            CREATE_SUSPENDED | DEBUG_ONLY_THIS_PROCESS,
        NULL, NULL, &start, &info));
    return std::make_pair(info.hProcess, info.hThread);
}
static RunResult runImpl(const Option& opt,
                         const Timer& timer,
                         const fs::path& in,
                         const fs::path& out) {
    Handle hjob = CreateJobObjectW(NULL, NULL);
    {
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION limit;
        limit.BasicLimitInformation
            .PerProcessUserTimeLimit.QuadPart =
            timer.remain() * 10;
        limit.ProcessMemoryLimit =
            opt.get<int64_t>("MemoryLimit", 0) << 10;
        limit.BasicLimitInformation.LimitFlags =
            JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION |
            JOB_OBJECT_LIMIT_PROCESS_MEMORY |
            JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE |
            JOB_OBJECT_LIMIT_PROCESS_TIME;
        assert(SetInformationJobObject(
            hjob.get(),
            JobObjectExtendedLimitInformation, &limit,
            sizeof(limit)));
    }
    {
        JOBOBJECT_END_OF_JOB_TIME_INFORMATION action;
        action.EndOfJobTimeAction =
            JOB_OBJECT_TERMINATE_AT_END_OF_JOB;
        assert(SetInformationJobObject(
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
        assert(SetInformationJobObject(
            hjob.get(),
            JobObjectAssociateCompletionPortInformation,
            &portInfo, sizeof(portInfo)));
    }
    Handle ihnd = CreateFileW(
        in.c_str(), GENERIC_READ, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL |
            FILE_FLAG_SEQUENTIAL_SCAN,
        NULL);
    Handle ohnd = CreateFileW(
        out.c_str(), GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
    std::pair<HANDLE, HANDLE> phnd =
        launch(opt, ihnd, ohnd);
    Handle process(phnd.first);
    {
        Handle thread(phnd.second);
        assert(AssignProcessToJobObject(
            hjob.get(), process.get()));
        ResumeThread(thread.get());
    }
    while(true) {
        DWORD MSG;
        ULONG_PTR unusedA;
        LPOVERLAPPED unusedB;
        assert(GetQueuedCompletionStatus(
            port.get(), &MSG, &unusedA, &unusedB,
            INFINITE));
        RunResult res;
        {
            FILETIME ct, et, kt, ut;
            assert(GetProcessTimes(process.get(), &ct,
                                   &et, &kt, &ut));
            int64_t ht = ut.dwHighDateTime,
                    lt = ut.dwLowDateTime;
            res.time = (ht << 32 | lt) / 10;
        }
        {
            PROCESS_MEMORY_COUNTERS info;
            assert(K32GetProcessMemoryInfo(
                process.get(), &info, sizeof(info)));
            res.mem = info.PeakPagefileUsage >> 10;
        }
        bool ret = true;
        switch(MSG) {
            case JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS: {
                res.st = Status::RE;
            } break;
            case JOB_OBJECT_MSG_EXIT_PROCESS: {
                res.st = Status::AC;
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
            TerminateJobObject(hjob.get(), 0);
            return res;
        }
    }
}
RunResult run(const Option& opt, const Timer& timer,
              const fs::path& in,
              const fs::path& out) {
    try {
        return runImpl(opt, timer, in, out);
    } catch(const std::system_error& err) {
        std::cout << err.what() << std::endl;
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
