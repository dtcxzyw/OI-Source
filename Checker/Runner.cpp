#include "Runner.hpp"
#include "Common.hpp"
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
RunResult::RunResult()
    : usrTime(0), totTime(0), mem(0), syscallcnt(0),
      st(Status::UKE), ret(RuntimeError::Unknown),
      sig(-1), maxErr(0.0) {}
std::string toString(Status st) {
    switch(st) {
        case Status::AC:
            return "\033[32mAccepted\033[0m";
            break;
        case Status::WA:
            return "\033[31mWrong Answer\033[0m";
            break;
        case Status::MLE:
            return "\033[33mMemory Limit "
                   "Exceeded\033[0m";
            break;
        case Status::TLE:
            return "\033[36mTime Limit "
                   "Exceeded\033[0m";
            break;
        case Status::RE:
            return "\033[35mRuntime Error\033[0m";
            break;
        case Status::UKE:
            return "\033[35mUnknown Error\033[0m";
            break;
        case Status::SE:
            return "\033[35mJudge System Error\033[0m";
            break;
        default:
            throw;
            break;
    }
}
std::string toString(RuntimeError st) {
    switch(st) {
        case RuntimeError::FloatingPointError:
            return "Floating Point Error";
            break;
        case RuntimeError::FloatingPointErrorO2:
            return "(SIGFPE):Floating Point "
                   "Error(-O2?)";
            break;
        case RuntimeError::NonzeroExitCode:
            return "Nonzero Exit Code";
            break;
        case RuntimeError::SegmentationFault:
            return "Segmentation Fault";
            break;
        case RuntimeError::Exception:
            return "Uncaught C++ Exception";
            break;
        case RuntimeError::Unknown:
            return "Unknown";
            break;
        default:
            throw;
            break;
    }
}
const int magic = 0xe7;
static void runTask(const Option& opt,
                    const Timer& timer,
                    const std::string& in,
                    const std::string& out) {
    ptrace(PT_TRACE_ME, 0, NULL, NULL);
    bool flag = true;
    flag &= freopen(in.c_str(), "r", stdin) != NULL;
    flag &= freopen(out.c_str(), "w", stdout) != NULL;
    // Time
    {
        struct rlimit limit;
        flag &= getrlimit(RLIMIT_CPU, &limit) == 0;
        limit.rlim_cur = timer.remainSeconds();
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
    std::regex pattern(val + ":([0-9]*)kB",
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
        res.usrTime = use.ru_utime.tv_sec * 1000000LL +
            use.ru_utime.tv_usec;
        res.totTime = res.usrTime +
            use.ru_stime.tv_sec * 1000000LL +
            use.ru_stime.tv_usec;
        res.mem = std::max(res.mem, getVmPeak(id));
        if(res.mem >= maxMem) {
            res.st = Status::MLE;
            ptrace(PTRACE_KILL, id, NULL, NULL);
            break;
        }
        if(timer.isTLE(res.usrTime, res.totTime)) {
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
                   WSTOPSIG(status) != 5)) {
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
                case SIGXCPU:
                    res.st = Status::TLE;
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
            if(callid != -1) {
                ++res.syscallcnt;
                ++res.callCnt[callid];
            }
            if(callid == __NR_execve) {
                res.syscallcnt = 0;
                res.callCnt.clear();
            }
            ptrace(PTRACE_SYSCALL, id, NULL, NULL);
        }
    }
    return res;
}
RunResult run(const Option& opt, const Timer& timer,
              const std::string& in,
              const std::string& out) {
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
void initRunner() {
    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    limit.rlim_cur = limit.rlim_max;
    setrlimit(RLIMIT_STACK, &limit);
}
static std::string getCallTableName() {
#ifdef __i386__
#define FileName "unistd_32.h"
#elif defined(__ILP32__)
#define FileName "unistd_x32.h"
#else
#define FileName "unistd_64.h"
#endif
    return "/usr/include/i386-linux-gnu/asm/" FileName;
#undef FileName
}
std::string getCallName(long callid) {
    static std::string LUT =
        file2Str(getCallTableName());
    std::regex pattern("#define__NR_([a-z0-9_]*)" +
                           std::to_string(callid) +
                           "#",
                       regexFlag4Search);
    std::smatch match;
    std::regex_search(LUT, match, pattern);
    if(match.size() == 2)
        return match[1].str();
    return "Unknown";
}
