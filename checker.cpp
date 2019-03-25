/*
TODO
使用正则表达式匹配输入输出文件名
跨Windows平台
修正内存大小测量
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
#include <string>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
using Clock = std::chrono::high_resolution_clock;
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
int64_t maxTime, maxMem;
const int magic = 0xe7;
RunResult run(const std::string& in,
              const std::string& out) {
    pid_t id = vfork();
    if(id < 0) {
        RunResult res;
        res.st = Status::SE;
        return res;
    } else if(id == 0) {
        bool flag = true;
        flag &=
            freopen(in.c_str(), "r", stdin) != NULL;
        flag &=
            freopen(out.c_str(), "w", stdout) != NULL;
        /*
        // Stack
        {
            struct rlimit limit;
            limit.rlim_cur = maxMem << 20;
            limit.rlim_max = RLIM_INFINITY;
            flag &=
                setrlimit(RLIMIT_STACK, &limit) == 0;
        }
        */
        // Time
        {
            struct rlimit limit;
            flag &= getrlimit(RLIMIT_CPU, &limit) == 0;
            limit.rlim_cur = maxTime / 1000 + 1;
            flag &= setrlimit(RLIMIT_CPU, &limit) == 0;
        }
        if(!flag)
            exit(magic);
        char* ptr = nullptr;
        if(execv(exec.c_str(), &ptr) == -1)
            exit(magic);
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
int type;
bool compare(const path& out, const path& stdout) {
    if(type == 0) {
        return compareImpl<std::string>(
            out, stdout, std::equal_to<std::string>());
    } else {
        using FT = long double;
        auto cmp = [](FT a, FT b) {
            constexpr FT eps = 1e-5;
            return fabsl(a - b) < eps ||
                fabsl(a - b) / b < eps;
        };
        return compareImpl<FT>(out, stdout, cmp);
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
std::vector<Data> scan(const path& dir) {
    using IterT = directory_iterator;
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
#define Input(name)                          \
    std::cout << #name << ":" << std::flush; \
    std::cin >> name
int main() {
    std::string name;
    Input(name);
    Input(maxTime);
    Input(maxMem);
    Input(type);
    exec = name + ".out";
    std::vector<Data> data = scan("data");
    if(data.size() != 0) {
        int64_t time = 0, mem = 0;
        std::map<Status, int> cnt;
        std::map<Status, path> first;
        for(const auto& d : data) {
            RunResult res = test(d);
            ++cnt[res.st];
            if(res.st == Status::AC) {
                time += res.time;
                mem = std::max(mem, res.mem);
            } else {
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
        std::cout << "Time " << time << " ms"
                  << std::endl;
        std::cout << "Memory " << mem << " MB"
                  << std::endl;
    } else
        std::cout << "No Input!!!" << std::endl;
    return 0;
}
