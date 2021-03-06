#include "../../Common.hpp"
#include "../../Runner.hpp"
#include <algorithm>
#include <asm/unistd.h>
#include <charconv>
#include <cstdint>
#include <iterator>
#include <regex>
#include <string>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
const int magic = 0xe7;
static void runTask(const Option& opt,
                    const Timer& timer,
                    const fs::path& in,
                    const fs::path& out) {
    ptrace(PT_TRACE_ME, 0, NULL, NULL);
    bool flag = true;
    flag &= freopen(in.c_str(), "r", stdin) != NULL;
    flag &= freopen(out.c_str(), "w", stdout) != NULL;
    // Time
    {
        struct rlimit limit;
        flag &= getrlimit(RLIMIT_CPU, &limit) == 0;
        limit.rlim_cur = timer.remain() / 1000000LL;
        flag &= setrlimit(RLIMIT_CPU, &limit) == 0;
    }
    if(!flag)
        _exit(magic);
    char* ptr = nullptr;
    if(execv(opt.get<fs::path>("Exec", "").c_str(),
             &ptr) == -1)
        _exit(magic);
}
static int64_t getStatusVal(const std::string& str,
                            const std::string& val) {
    std::regex pattern(val + "\\s*:\\s*([0-9]*)\\s*kB",
                       regexFlag4Search);
    std::smatch match;
    std::regex_search(str, match, pattern);
    if(match.size() == 2) {
        std::string mstr = match[1].str();
        return scan<int64_t>(mstr);
    }
    return 0;
}
static int64_t getVmPeak(pid_t id) {
    std::string status = file2Str(
        "/proc/" + std::to_string(id) + "/status");
    int64_t res = getStatusVal(status, "VmPeak") -
        getStatusVal(status, "VmExe") -
        getStatusVal(status, "VmLib");
    return std::max(res, static_cast<int64_t>(0));
}
static RunResult watchTask(const Option& opt,
                           const Timer& timer,
                           pid_t id) {
    RunResult res;
    int64_t maxMem =
        opt.get<int64_t>("MemoryLimit", 0);
    while(true) {
        int status = 0;
        struct rusage use;
        wait4(id, &status, 0, &use);
        res.time = use.ru_utime.tv_sec * 1000000LL +
            use.ru_utime.tv_usec;
        res.mem = std::max(res.mem, getVmPeak(id));
        if(res.mem >= maxMem) {
            res.st = Status::MLE;
            ptrace(PTRACE_KILL, id, NULL, NULL);
            break;
        }
        if(timer.isTLE(res.time)) {
            res.st = Status::TLE;
            ptrace(PTRACE_KILL, id, NULL, NULL);
            break;
        }
        if(WIFEXITED(status)) {
            if(WEXITSTATUS(status) == magic)
                res.st = Status::SE;
            else if(WEXITSTATUS(status)) {
                res.st = Status::RE;
                res.ret =
                    RuntimeError::NonzeroExitCode;
                res.sig = WEXITSTATUS(status);
            } else
                res.st = Status::AC;
            break;
        } else if(WIFSIGNALED(status) ||
                  (WIFSTOPPED(status) &&
                   WSTOPSIG(status) != SIGTRAP &&
                   WSTOPSIG(status) != SIGXCPU)) {
            res.st = Status::RE;
            res.ret = RuntimeError::Unknown;
            res.sig = WIFSIGNALED(status) ?
                WTERMSIG(status) :
                WSTOPSIG(status);
            switch(res.sig) {
                case SIGABRT:
                    res.ret = RuntimeError::Exception;
                    break;
                case SIGFPE:
                    res.ret = RuntimeError::
                        FloatingPointError;
                    break;
                case SIGSEGV:
                    res.ret = RuntimeError::
                        SegmentationFault;
                    break;
                case SIGILL:
                    res.ret = RuntimeError::
                        FloatingPointErrorO2;
                    break;
                default:
                    res.ret = RuntimeError::Unknown;
                    break;
            }
            ptrace(PTRACE_KILL, id, NULL, NULL);
            break;
        } else {
            struct user_regs_struct reg;
            ptrace(PTRACE_GETREGS, id, NULL, &reg);
#ifdef __x86_64__
            long callid = reg.orig_rax;
#else
            long callid = reg.orig_eax;
#endif
            if(callid != -1)
                ++res.callCnt[callid];
            if(callid == __NR_execve)
                res.callCnt.clear();
            ptrace(PTRACE_SYSCALL, id, NULL, NULL);
        }
    }
    return res;
}
RunResult run(const Option& opt, const Timer& timer,
              const fs::path& in,
              const fs::path& out) {
    pid_t id = vfork();
    if(id < 0) {
        RunResult res;
        res.st = Status::SE;
        return res;
    } else if(id == 0)
        runTask(opt, timer, in, out);
    else
        return watchTask(opt, timer, id);
    throw;
}
