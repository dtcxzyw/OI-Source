#include "Judger.hpp"
#include "OJAdapter.hpp"
#include "PerfAnalyzer.hpp"
#include "Scanner.hpp"
#include <cmath>
#include <iostream>
#include <map>
#define Input(name)                          \
    std::cout << #name << ":" << std::flush; \
    std::cin >> opt.name
bool runAll(const Option& opt,
            const std::vector<Data>& data) {
    int64_t time = 0, mem = 0, mt = 0;
    FT maxErr = 0.0;
    std::map<long, int> sysCall;
    std::map<Status, int> cnt;
    std::map<Status, fs::path> first;
    for(const auto& d : data) {
        RunResult res = test(opt, d);
        ++cnt[res.st];
        if(res.st == Status::AC ||
           res.st == Status::WA) {
            time += res.time;
            mem = std::max(mem, res.mem);
            mt = std::max(mt, res.time);
            maxErr = std::max(maxErr, res.maxErr);
            for(auto call : res.callCnt)
                sysCall[call.first] += call.second;
        }
        if(res.st != Status::AC) {
            if(!first.count(res.st) ||
               file_size(first[res.st]) >
                   file_size(d.input))
                first[res.st] = d.input;
        }
    }
    bool flag = cnt[Status::AC] ==
        static_cast<int>(data.size());
    PerformanceInfo pinfo;
    if(flag)
        for(const auto& d : data)
            pinfo += perf(opt, d);
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
    if(flag && (opt.compareMode == 1)) {
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
    if(flag)
        pinfo.report();
    line("System Call");
    for(auto call : sysCall)
        std::cout << "call \033[36m"
                  << getCallName(call.first)
                  << "\033[0m(id=" << call.first
                  << "):"
                  << call.second /
                static_cast<double>(data.size())
                  << std::endl;
    return flag;
}
bool runDefault(const fs::path& exec) {
    std::vector<Data> data = scanData("data");
    if(data.empty()) {
        std::cout << "No Input!!!" << std::endl;
        return true;
    }
    line("Auto Scan Result");
    std::cout << "task count:" << data.size()
              << std::endl;
    {
        uintmax_t maxInput = 0, maxOutput = 0;
        for(auto d : data) {
            maxInput =
                std::max(maxInput, file_size(d.input));
            maxOutput = std::max(maxOutput,
                                 file_size(d.output));
        }
        std::cout << "maxInput:"
                  << maxInput / 1048576.0 << " MB"
                  << std::endl;
        std::cout << "maxOutput:"
                  << maxOutput / 1048576.0 << " MB"
                  << std::endl;
    }
    line("Arguments");
    Option opt;
    opt.exec = exec;
    Input(maxTime);
    opt.maxTime *= 1000;
    Input(maxMem);
    opt.maxMem <<= 10;
    Input(compareMode);
    runAll(opt, data);
    return true;
}
static OJAdapterInfo reg("DefaultJudger",
                         std::regex("\\w+"),
                         runDefault, -100);
