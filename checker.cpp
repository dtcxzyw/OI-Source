/*
Checker:懒到一定境界的产物

2018修订历史：

fc.cpp
7.11(init) 用眼比对太麻烦了，索性写个类似fc的东西

11.7
LOJ上可以下载数据，懒得手动逐个比对，干脆按照编号自动扫描，同时还能算成绩

checker.cpp
11.16 fc.cpp->checker.cpp

11.21 RE也能AC？得特判system返回值

11.30 读入long long会爆int，干脆用long long吧

12.4
YES/NO怎么判？干脆像diff那样匹配文本，改读std::string

12.10
有些LOJ题目的测试点编号前居然有前缀！！！懒得逐个改前缀，直接在控制台输入前缀。
顺便防止输错前缀导致SIGFPE

12.30
少输出也能AC？不行得把读入头移回去反过来再匹配一遍（后来证明我的algorithm姿势
还是不够）

2019修订历史：

1.6
还有".ans"后缀的答案文件，不想多次改刷change，索性暴力判断两个后缀是否可行

1.7 \sout{我要当rank2！！！}我需要测量运行总时间

1.16
假设std::chrono:high_resolution_clock的单位是纳秒是不对的！！我要跨平台！！！
\sout{我就这一台电脑。}

1.17 似乎自己把判题的时间一起算进去了。。。

3.23（重大更新）
APIO的测试点命名把我搞得很惨，为什么有01开头？为什么有那么多的子任务？
为什么还用字母区分数据种类？为什么还用无后缀和.a表示输入输出？不行我要
自动扫描并匹配输入输出文件！！！为此引入了std::filesystem。

程序超时后面的测试点没法测怎么办？Ctrl+C一不小心就把checker给结束了。
我需要使用类似ulimit的东西来限制时间，同时开栈。似乎不能用system，那就
下决心使用fork+execv，发现wait4可以得到程序的资源使用信息，可以判断TLE
和MLE了！！！居然还有异常退出的情况？那就顺便判断RE（细分各种信号量）。

3.25
通过控制测试程序的浮点输出精度来与标准答案在文本上一模一样做不下去了，
干脆再加个flag指示是否使用浮点比较。同时改了一下智障的双向判断。
\sout{没有好好研究<algorithm>的下场}

3.26
把WA的时间和内存记录进去，同时记录极限测试点的运行时间。（最正经的记录）

3.27
集成perf用于研究CacheMiss等性能指标。给不断成长的Checker写点历史。
懒得输入待测试程序名了，直接使用bin文件夹下除checker,charCounter外的最新
的可执行程序作为测试程序。

3.28
修正内存测量，以/proc下的VmPeak值为标准

3.29
修复SIGTRAP信号导致Checker死循环，支持处理被STOP的程序，记录syscall
perf信息读入，全部AC后自动做perf给出性能指标

为什么这些事我不一次性搞定呢？当然是需求推进科技进步啦！\sout{还是我懒}

TODO
使用正则表达式匹配输入输出文件名
跨Windows平台
支持LOJ的SPJ
支持LOJ的data.yml
*/
#include <algorithm>
#include <cerrno>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
using namespace std::filesystem;
enum class Status { AC, WA, MLE, TLE, RE, SE, UKE };
enum class RuntimeError {
    NonzeroExitCode,
    SegmentationFault,
    FloatingPointError,
    FloatingPointErrorO2,
    Exception,
    Unknown
};
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
// Time:ms Memory:MB
struct RunResult {
    int64_t time, mem, syscallcnt;
    Status st;
    RuntimeError ret;
    int sig;
    RunResult()
        : time(0), mem(0), syscallcnt(0),
          st(Status::UKE), ret(RuntimeError::Unknown),
          sig(-1) {}
};
std::string exec;
int64_t maxTime, maxMem, mode;
const int magic = 0xe7;
void runTask(const std::string& in,
             const std::string& out) {
    ptrace(PT_TRACE_ME, 0, NULL, NULL);
    bool flag = true;
    flag &= freopen(in.c_str(), "r", stdin) != NULL;
    flag &= freopen(out.c_str(), "w", stdout) != NULL;
    /*
    // Stack
    {
        struct rlimit limit;
        limit.rlim_cur = maxMem << 20;
        limit.rlim_max = RLIM_INFINITY;
        flag &=setrlimit(RLIMIT_STACK, &limit)
    ==0;
    }
    */
    // Time
    {
        struct rlimit limit;
        flag &= getrlimit(RLIMIT_CPU, &limit) == 0;
        limit.rlim_cur = maxTime / 1000000 + 1;
        flag &= setrlimit(RLIMIT_CPU, &limit) == 0;
    }
    if(!flag)
        _exit(magic);
    char* ptr = nullptr;
    if(execv(exec.c_str(), &ptr) == -1)
        _exit(magic);
}
int64_t getStatusVal(const std::string& str,
                     const std::string& val) {
    std::regex pattern(val + ":([0-9]*)kB");
    std::smatch match;
    std::regex_search(str, match, pattern);
    if(match.size() == 2) {
        std::string mstr = match[1].str();
        int64_t res = 0;
        std::from_chars(mstr.c_str(),
                        mstr.c_str() + mstr.size(),
                        res);
        return res;
    }
    return 0;
}
using CharIter = std::istream_iterator<char>;
int64_t getVmPeak(pid_t id) {
    std::ifstream status(
        "/proc/" + std::to_string(id) + "/status");
    if(!status)
        return 0;
    std::string str{ CharIter(status), CharIter() };
    int64_t res = getStatusVal(str, "VmPeak") -
        getStatusVal(str, "VmExe") -
        // getStatusVal(str, "VmStk") -
        getStatusVal(str, "VmLib");
    return std::max(res, 0LL);
}
std::map<long, int> callCnt;
RunResult watchTask(pid_t id) {
    RunResult res;
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
        if(res.time >= maxTime) {
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
            } else {
                res.st = Status::AC;
                if(res.mem >= maxMem)
                    res.st = Status::MLE;
                if(res.time >= maxTime)
                    res.st = Status::TLE;
            }
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
                ++callCnt[callid];
            }
            ptrace(PTRACE_SYSCALL, id, NULL, NULL);
        }
    }
    return res;
}
RunResult run(const std::string& in,
              const std::string& out) {
    pid_t id = vfork();
    if(id < 0) {
        RunResult res;
        res.st = Status::SE;
        return res;
    } else if(id == 0)
        runTask(in, out);
    else
        return watchTask(id);
    throw;
}
template <typename T>
bool compareImpl(
    const path& out, const path& stdout,
    const std::function<bool(const T&, const T&)>&
        cmp) {
    std::ifstream outf(out), stdof(stdout);
    using Iter = std::istream_iterator<T>;
    return std::equal(Iter(outf), Iter(), Iter(stdof),
                      Iter(), cmp);
}
bool compare(const path& out, const path& stdout) {
    if(mode & 1) {
        using FT = long double;
        auto cmp = [](FT a, FT b) {
            constexpr FT eps = 1e-5;
            return fabsl(a - b) < eps ||
                fabsl(a - b) / b < eps;
        };
        return compareImpl<FT>(out, stdout, cmp);
    } else {
        return compareImpl<std::string>(
            out, stdout, std::equal_to<std::string>());
    }
}
struct Data {
    path input, output;
    Data(const path& input, const path& output)
        : input(input), output(output) {}
    bool operator<(const Data& rhs) const {
        return input < rhs.input;
    }
};
void line(const std::string& str) {
    std::cout << "\033[36m";
    int mid = (36 - str.size()) / 2;
    for(int i = 0; i < mid; ++i)
        std::cout.put('-');
    std::cout << str;
    for(int i = 0; i < mid; ++i)
        std::cout.put('-');
    std::cout << "\033[0m" << std::endl;
}
const path tmpOutput = "tmpY89Y43RB";
RunResult test(const Data& data) {
    line("Running Task " + data.input.stem().string());
    RunResult res = run(data.input, tmpOutput);
    if(res.st == Status::AC &&
       !compare(tmpOutput, data.output))
        res.st = Status::WA;
    std::cout << "Result " << toString(res.st) << " ";
    if(res.st == Status::RE) {
        if(res.ret == RuntimeError::NonzeroExitCode)
            std::cout << "[Exited with code "
                      << res.sig << "]";
        else if(res.sig != -1)
            std::cout << "[SIG=" << res.sig << ":"
                      << strsignal(res.sig) << "]";
        std::cout << "(" << toString(res.ret) << ") ";
    }
    if(res.st == Status::SE || res.st == Status::UKE)
        std::cout << "(" << std::strerror(errno)
                  << ") ";
    std::cout << res.time / 1000.0 << " ms "
              << res.mem / 1024.0 << " MB"
              << std::endl;
    std::cout << "SyscallCount=" << res.syscallcnt
              << std::endl;
    return res;
}
const int64_t invalid =
    std::numeric_limits<int64_t>::max();
int64_t getPerfVal(const std::string& str,
                   const std::string& val) {
    std::regex pattern("([0-9,]+)" + val);
    std::smatch match;
    std::regex_search(str, match, pattern);
    if(match.size() == 2) {
        std::string mstr = match[1].str();
        int64_t res = 0;
        for(auto ch : mstr)
            if(ch != ',')
                res = res * 10 + ch - '0';
        return res;
    }
    return invalid;
}
class PerformanceInfo {
private:
    int64_t cacheRef, cacheMiss, branchCnt, branchMiss,
        cycleCnt, instCnt;

public:
    explicit PerformanceInfo(const std::string& str)
        : cacheRef(
              getPerfVal(str, "cache-references")),
          cacheMiss(getPerfVal(str, "cache-misses")),
          branchCnt(getPerfVal(str, "branches")),
          branchMiss(getPerfVal(str, "branch-misses")),
          cycleCnt(getPerfVal(str, "cpu-cycles")),
          instCnt(getPerfVal(str, "instructions")) {
        if(cacheRef == invalid || cacheMiss == invalid)
            cacheRef = cacheMiss = 0;
        if(branchCnt == invalid ||
           branchMiss == invalid)
            branchCnt = branchMiss = 0;
        if(cycleCnt == invalid || instCnt == invalid)
            cycleCnt = instCnt = 0;
    }
    PerformanceInfo()
        : cacheRef(0), cacheMiss(0), branchCnt(0),
          branchMiss(0), cycleCnt(0), instCnt(0) {}
    PerformanceInfo&
    operator+=(const PerformanceInfo& rhs) {
        cacheRef += rhs.cacheRef;
        cacheMiss += rhs.cacheMiss;
        branchCnt += rhs.branchCnt;
        branchMiss += rhs.branchMiss;
        cycleCnt += rhs.cycleCnt;
        instCnt += rhs.instCnt;
        return *this;
    }
    void report() const {
        if(cacheRef)
            std::cout << "Cache Miss:"
                      << 100.0 * cacheMiss / cacheRef
                      << "%" << std::endl;
        if(branchCnt)
            std::cout << "Branch Miss:"
                      << 100.0 * branchMiss / branchCnt
                      << "%" << std::endl;
        if(cycleCnt)
            std::cout << "IPC:"
                      << static_cast<double>(instCnt) /
                    cycleCnt
                      << std::endl;
    }
};
PerformanceInfo perf(const Data& data) {
    line("Analysing Task " +
         data.input.stem().string());
    const std::string perfFile = "tmpFIYGB32YRG";
    auto cmd = "perf stat -e "
               "cache-misses,branch-misses,"
               "instructions,branches,cache-"
               "references,cpu-cycles -o " +
        perfFile + " ./" + exec + " <" +
        data.input.string() + " >" +
        tmpOutput.string();
    std::cout << "Command:" << cmd << std::endl;
    int res = system(cmd.c_str());
    if(!res) {
        std::ifstream file(perfFile);
        if(file) {
            std::string str{ CharIter(file),
                             CharIter() };
            return PerformanceInfo(str);
        }
    } else
        std::cout << "\033[35mPerf Error(exit code="
                  << res << ")\033[0m" << std::endl;
    return {};
}
using DirIter = directory_iterator;
std::vector<Data> scanData(const path& dir) {
    std::map<path, path> in, out;
    std::vector<Data> res;
    for(DirIter it(dir); it != DirIter(); ++it)
        if(it->status().type() == file_type::regular) {
            path cp = it->path();
            path name = cp.stem(),
                 ext = cp.extension();
            if(!cp.has_extension() || ext == ".in") {
                if(out.count(name))
                    res.push_back(Data(cp, out[name]));
                else
                    in[name] = cp;
            } else if(ext == ".out" || ext == ".a" ||
                      ext == ".ans") {
                if(in.count(name))
                    res.push_back(Data(in[name], cp));
                else
                    out[name] = cp;
            }
        }
    std::sort(res.begin(), res.end());
    return res;
}
path scanExec() {
    std::set<path> blacklist{ "checker",
                              "charCounter" };
    file_time_type mft;
    path res;
    for(DirIter it(current_path()); it != DirIter();
        ++it)
        if(it->status().type() == file_type::regular) {
            path cp = it->path();
            path name = cp.stem(),
                 ext = cp.extension();
            if(ext != ".out" || blacklist.count(name))
                continue;
            auto cft = last_write_time(cp);
            if(cft > mft)
                mft = cft, res = cp;
        }
    return relative(res);
}
std::string getCallTable() {
#ifdef __i386__
#define FileName "unistd_32.h"
#elif defined(__ILP32__)
#define FileName "unistd_x32.h"
#else
#define FileName "unistd_64.h"
#endif
    std::ifstream LUT(
        "/usr/include/i386-linux-gnu/asm/" FileName);
#undef FileName
    if(!LUT)
        return std::string();
    return std::string(CharIter(LUT), CharIter());
}
std::string getCallName(const std::string& LUT,
                        long callid) {
    std::regex pattern("#define__NR_([a-z0-9_]*)" +
                       std::to_string(callid) + "#");
    std::smatch match;
    std::regex_search(LUT, match, pattern);
    if(match.size() == 2)
        return match[1].str();
    return "Unknown";
}
#define Input(name)                          \
    std::cout << #name << ":" << std::flush; \
    std::cin >> name
int main() {
    std::cout.precision(2);
    std::cout << std::fixed;
    exec = scanExec();
    std::cout << "program:" << exec << std::endl;
    std::vector<Data> data = scanData("data");
    std::cout << "task count:" << data.size()
              << std::endl;
    if(data.empty()) {
        std::cout << "No Input!!!" << std::endl;
        return 0;
    }
    Input(maxTime);
    maxTime *= 1000;
    Input(maxMem);
    maxMem <<= 10;
    Input(mode);
    int64_t time = 0, mem = 0, mt = 0;
    std::map<Status, int> cnt;
    std::map<Status, path> first;
    for(const auto& d : data) {
        RunResult res = test(d);
        ++cnt[res.st];
        if(res.st == Status::AC ||
           res.st == Status::WA) {
            time += res.time;
            mem = std::max(mem, res.mem);
            mt = std::max(mt, res.time);
        }
        if(res.st != Status::AC) {
            if(!first.count(res.st) ||
               file_size(first[res.st]) >
                   file_size(d.input))
                first[res.st] = d.input;
        }
    }
    PerformanceInfo pinfo;
    if(cnt[Status::AC] ==
       static_cast<int>(data.size()))
        for(const auto& d : data)
            pinfo += perf(d);
    line("Summary");
    std::cout << "Score "
              << cnt[Status::AC] * 100 / data.size()
              << std::endl;
    std::cout << "TotTime " << time / 1000.0 << " ms"
              << std::endl;
    std::cout << "MaxTime " << mt / 1000.0 << " ms"
              << std::endl;
    std::cout << "MaxMemory " << mem / 1024.0 << " MB"
              << std::endl;
    line("Detailed Result");
    for(auto x : cnt) {
        std::cout << toString(x.first) << " "
                  << x.second;
        if(x.first != Status::AC)
            std::cout << "(e.g. "
                      << first[x.first].filename()
                      << ")";
        std::cout << std::endl;
    }
    line("Performance");
    pinfo.report();
    line("Syscall");
    std::string LUT = getCallTable();
    for(auto call : callCnt)
        std::cout << "call \033[36m"
                  << getCallName(LUT, call.first)
                  << "\033[0m(id=" << call.first
                  << "):"
                  << call.second /
                static_cast<double>(data.size())
                  << std::endl;
    return 0;
}
