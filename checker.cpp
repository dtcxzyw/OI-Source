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

为什么这些事我不一次性搞定呢？当然是需求推进科技进步啦！\sout{还是我懒}

TODO
使用正则表达式匹配输入输出文件名
跨Windows平台
修正内存大小测量
perf信息读入，全部AC后自动做perf给出性能指标
*/
#include <algorithm>
#include <cerrno>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <sys/resource.h>
#include <sys/types.h>
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
            return "SIGFPE:Floating Point Error";
            break;
        case RuntimeError::FloatingPointErrorO2:
            return "SIGILL(SIGFPE):Floating Point "
                   "Error(-O2?)";
            break;
        case RuntimeError::NonzeroExitCode:
            return "Nonzero Exit Code";
            break;
        case RuntimeError::SegmentationFault:
            return "SIGSEGV:Segmentation Fault";
            break;
        case RuntimeError::Exception:
            return "SIGABRT:Uncaught C++ Exception";
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
    int64_t time, mem;
    Status st;
    RuntimeError ret;
    RunResult()
        : time(0), mem(0), st(Status::UKE),
          ret(RuntimeError::Unknown) {}
};
std::string exec;
int64_t maxTime, maxMem, type;
const int magic = 0xe7;
RunResult run(const std::string& in,
              const std::string& out) {
    pid_t id = vfork();
    if(id < 0) {
        RunResult res;
        res.st = Status::SE;
        return res;
    } else if(id == 0) {
        if(type & 2) {
            auto cmd = "perf stat -e "
                       "cache-misses,branch-misses,"
                       "instructions,branches,cache-"
                       "references,cpu-cycles ./" +
                exec + " <" + in + " >" + out;
            std::cout << "Command:" << cmd
                      << std::endl;
            quick_exit(system(cmd.c_str()));
        } else {
            bool flag = true;
            flag &= freopen(in.c_str(), "r", stdin) !=
                NULL;
            flag &= freopen(out.c_str(), "w",
                            stdout) != NULL;
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
                flag &=
                    getrlimit(RLIMIT_CPU, &limit) == 0;
                limit.rlim_cur = maxTime / 1000 + 1;
                flag &=
                    setrlimit(RLIMIT_CPU, &limit) == 0;
            }
            if(!flag)
                quick_exit(magic);
            char* ptr = nullptr;
            if(execv(exec.c_str(), &ptr) == -1)
                quick_exit(magic);
        }
    } else {
        int status = 0;
        struct rusage use;
        wait4(id, &status, 0, &use);
        RunResult res;
        res.time = (use.ru_utime.tv_sec +
                    use.ru_stime.tv_sec) *
                1000LL +
            (use.ru_utime.tv_usec +
             use.ru_stime.tv_usec) /
                1000LL;
        res.mem = use.ru_maxrss >> 10;
        if(WIFEXITED(status)) {
            if(WEXITSTATUS(status) == magic)
                res.st = Status::SE;
            else if(WEXITSTATUS(status)) {
                res.st = Status::RE;
                res.ret =
                    RuntimeError::NonzeroExitCode;
            } else {
                res.st = Status::AC;
                if(res.mem >= maxMem)
                    res.st = Status::MLE;
                if(res.time >= maxTime)
                    res.st = Status::TLE;
            }
        } else if(WIFSIGNALED(status)) {
            res.st = Status::RE;
            res.ret = RuntimeError::Unknown;
            switch(WTERMSIG(status)) {
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
        } else
            res.st = Status::UKE;
        return res;
    }
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
    if(type & 1) {
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
void line() {
    std::cout << "\033[36m----------------------------"
                 "-------\033[0m"
              << std::endl;
}
RunResult test(const Data& data) {
    line();
    std::cout << "Running Test " << data.input.stem()
              << std::endl;
    const path tmp = "tmpY89Y43RB";
    RunResult res = run(data.input, tmp);
    if(res.st == Status::AC &&
       !compare(tmp, data.output))
        res.st = Status::WA;
    std::cout << "Result " << toString(res.st) << " ";
    if(res.st == Status::RE)
        std::cout << "(" << toString(res.ret) << ") ";
    if(res.st == Status::SE || res.st == Status::UKE)
        std::cout << "(" << std::strerror(errno)
                  << ") ";
    std::cout << res.time << " ms " << res.mem << " MB"
              << std::endl;
    return res;
}
using IterT = directory_iterator;
std::vector<Data> scanData(const path& dir) {
    std::map<path, path> in, out;
    std::vector<Data> res;
    for(IterT it(dir); it != IterT(); ++it)
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
    for(IterT it(current_path()); it != IterT(); ++it)
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
#define Input(name)                          \
    std::cout << #name << ":" << std::flush; \
    std::cin >> name
int main() {
    exec = scanExec();
    std::cout << "program:" << exec << std::endl;
    Input(maxTime);
    Input(maxMem);
    Input(type);
    std::vector<Data> data = scanData("data");
    if(data.size() != 0) {
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
        line();
        for(auto x : cnt) {
            std::cout << toString(x.first) << " "
                      << x.second;
            if(x.first != Status::AC)
                std::cout << "(e.g. "
                          << first[x.first].filename()
                          << ")";
            std::cout << std::endl;
        }
        line();
        std::cout << "Score "
                  << cnt[Status::AC] * 100 /
                data.size()
                  << std::endl;
        std::cout << "TotTime " << time << " ms"
                  << std::endl;
        std::cout << "MaxTime " << mt << " ms"
                  << std::endl;
        std::cout << "MaxMemory " << mem << " MB"
                  << std::endl;
    } else
        std::cout << "No Input!!!" << std::endl;
    return 0;
}
