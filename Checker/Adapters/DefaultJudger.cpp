#include "../Judger.hpp"
#include "../OJAdapter.hpp"
#include "../Platforms/Platform.hpp"
#include "../Scanner.hpp"
#include "../Timer.hpp"
#include <cmath>
#include <iostream>
#include <map>
bool runAll(const Option& opt,
            const std::vector<Data>& data) {
    Timer timer(opt);
    int64_t mem = 0;
    FT maxErr = 0.0;
    std::map<long, int> sysCall;
    std::map<Status, int> cnt;
    std::map<Status, fs::path> first;
    for(const auto& d : data) {
        RunResult res = test(opt, d, timer);
        ++cnt[res.st];
        if(res.st == Status::AC ||
           res.st == Status::WA) {
            timer.addTask(res.time);
            mem = std::max(mem, res.mem);
            maxErr = std::max(maxErr, res.maxErr);
            for(auto call : res.callCnt) {
                int& val = sysCall[call.first];
                val = std::max(val, call.second);
            }
        } else if(res.st == Status::TLE)
            timer.addTask(res.time);
        if(res.st != Status::AC) {
            if(!first.count(res.st) ||
               file_size(first[res.st]) >
                   file_size(d.input))
                first[res.st] = d.input;
        }
    }
    bool flag = cnt[Status::AC] ==
            static_cast<int>(data.size()) &&
        !timer.isTLE();
#if !defined(__WIN32)
    PerformanceInfo pinfo;
    if(flag) {
        line("PerfAnalyzer");
        for(const auto& d : data)
            pinfo += perf(opt, d);
        showLine("\033[34m",
                 "All analysis has been performed.");
    }
#endif
    line("Summary");
    std::cout << "Score "
              << cnt[Status::AC] * 100 / data.size()
              << std::endl;
    timer.report();
    std::cout << "MaxMemory " << mem / 1024.0 << " MB"
              << std::endl;
    if(flag &&
       (opt.get<CompareMode>("CompareMode",
                             CompareMode::Text) ==
        CompareMode::FloatingPoint)) {
        if(maxErr >= 1e-20l)
            std::cout << "MaxError 10^"
                      << std::log10(maxErr)
                      << std::endl;
        else
            std::cout << "\033[32mNo Error\033[0m"
                      << std::endl;
    }
    line("Detailed Result");
    for(auto x : cnt)
        if(x.second) {
            std::cout << toString(x.first) << " "
                      << x.second;
            if(x.first != Status::AC)
                std::cout << "(e.g. "
                          << first[x.first].filename()
                          << ")";
            std::cout << std::endl;
        }
    if(flag) {
#if !defined(__WIN32)
        pinfo.report();
        line("Hot System Call");
        std::vector<std::pair<int, long>> info;
        for(auto call : sysCall) {
            if(call.second >= 50)
                info.emplace_back(call.second,
                                  call.first);
        }
        std::sort(info.rbegin(), info.rend());
        for(auto call : info)
            std::cout << "call \033[36m"
                      << getCallName(call.second)
                      << "\033[0m(id=" << call.second
                      << "):" << call.first
                      << std::endl;
#endif
        timer.addSample();
    }
    return flag;
}
#define Input(name)                          \
    std::cout << #name << ":" << std::flush; \
    std::cin >> name
bool runDefault(const fs::path& exec) {
    std::vector<Data> data = scanData("data");
    if(data.size()) {
        line("Arguments");
        int64_t maxTime, maxMem;
        Option opt;
        opt.insert("Exec", exec);
        Input(maxTime);
        opt.insert("TimeLimit", maxTime * 1000);
        Input(maxMem);
        opt.insert("MemoryLimit", maxMem << 10);
        int compareMode;
        Input(compareMode);
        opt.insert("CompareMode", compareMode ?
                       CompareMode::FloatingPoint :
                       CompareMode::Text);
        runAll(opt, data);
    } else
        std::cout << "No Input!!!" << std::endl;
    return true;
}
static OJAdapterInfo reg("DefaultJudger",
                         std::regex("\\w+",
                                    regexFlag4Match),
                         runDefault, -100);
