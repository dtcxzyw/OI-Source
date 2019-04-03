#pragma once
#include "Common.hpp"
#include "Timer.hpp"
#include <cstdint>
#include <map>
enum class Status {
    AC,
    WA,
    MLE,
    TLE,
    RE,
    SE,
    UKE,
    SKIPPED
};
enum class RuntimeError {
    NonzeroExitCode,
    SegmentationFault,
    FloatingPointError,
    FloatingPointErrorO2,
    Exception,
    Unknown
};
// Time:us Memory:KB
struct RunResult {
    int64_t usrTime, totTime, mem, syscallcnt;
    Status st;
    RuntimeError ret;
    int sig;
    std::map<long, int> callCnt;
    FT maxErr;
    RunResult();
};
void initRunner();
RunResult run(const Option& opt, const Timer& timer,
              const std::string& in,
              const std::string& out);
std::string toString(Status st);
std::string toString(RuntimeError st);
std::string getCallName(long callid);
