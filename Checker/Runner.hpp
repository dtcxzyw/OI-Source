#pragma once
#include "Common.hpp"
#include <cstdint>
#include <map>
enum class Status { AC, WA, MLE, TLE, RE, SE, UKE };
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
RunResult run(const Option& opt, const std::string& in,
              const std::string& out);
std::string toString(Status st);
std::string toString(RuntimeError st);
std::string getCallName(long callid);
