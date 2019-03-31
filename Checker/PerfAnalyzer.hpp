#pragma once
#include "Common.hpp"
class PerformanceInfo {
private:
    int64_t cacheRef, cacheMiss, branchCnt, branchMiss,
        cycleCnt, instCnt;

public:
    explicit PerformanceInfo(const std::string& str);
    PerformanceInfo();
    PerformanceInfo&
    operator+=(const PerformanceInfo& rhs);
    void report() const;
};
PerformanceInfo perf(const Option& opt,
                     const Data& data);
