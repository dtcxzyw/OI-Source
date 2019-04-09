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
    int64_t time, mem, syscallcnt;
    Status st;
    RuntimeError ret;
    int sig;
    std::map<long, int> callCnt;
    FT maxErr;
    RunResult();
};
void initRunner();
void platformInfo();
RunResult run(const Option& opt, const Timer& timer,
              const fs::path& in, const fs::path& out);
std::string toString(Status st);
std::string toString(RuntimeError st);
std::string getCallName(long callid);
