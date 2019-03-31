#include "PerfAnalyzer.hpp"
#include "Common.hpp"
#include <iostream>
#include <regex>
const int64_t invalid =
    std::numeric_limits<int64_t>::max();
static int64_t getPerfVal(const std::string& str,
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
PerformanceInfo::PerformanceInfo(
    const std::string& str)
    : cacheRef(getPerfVal(str, "cache-references")),
      cacheMiss(getPerfVal(str, "cache-misses")),
      branchCnt(getPerfVal(str, "branches")),
      branchMiss(getPerfVal(str, "branch-misses")),
      cycleCnt(getPerfVal(str, "cpu-cycles")),
      instCnt(getPerfVal(str, "instructions")) {
    if(cacheRef == invalid || cacheMiss == invalid)
        cacheRef = cacheMiss = 0;
    if(branchCnt == invalid || branchMiss == invalid)
        branchCnt = branchMiss = 0;
    if(cycleCnt == invalid || instCnt == invalid)
        cycleCnt = instCnt = 0;
}
PerformanceInfo::PerformanceInfo()
    : cacheRef(0), cacheMiss(0), branchCnt(0),
      branchMiss(0), cycleCnt(0), instCnt(0) {}
PerformanceInfo& PerformanceInfo::
operator+=(const PerformanceInfo& rhs) {
    cacheRef += rhs.cacheRef;
    cacheMiss += rhs.cacheMiss;
    branchCnt += rhs.branchCnt;
    branchMiss += rhs.branchMiss;
    cycleCnt += rhs.cycleCnt;
    instCnt += rhs.instCnt;
    return *this;
}
void PerformanceInfo::report() const {
    line("Performance");
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
PerformanceInfo perf(const Option& opt,
                     const Data& data) {
    line("Analysing Task " +
         data.input.stem().string());
    TempFile perfFile, tmpOutput;
    auto cmd = "perf stat -e "
               "cache-misses,branch-misses,"
               "instructions,branches,cache-"
               "references,cpu-cycles -o " +
        perfFile.path().string() + " ./" +
        opt.exec.string() + " <" +
        data.input.string() + " >" +
        tmpOutput.path().string();
    std::cout << "Command:" << cmd << std::endl;
    int res = system(cmd.c_str());
    if(!res) {
        return PerformanceInfo(
            file2Str(perfFile.path()));
    } else
        std::cout << "\033[35mPerf Error(exit code="
                  << res << ")\033[0m" << std::endl;
    return {};
}
