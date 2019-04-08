#include "Runner.hpp"
#include <Windows.h>
void initRunner() {}
std::string getCallName(long) {
    return "Unknown";
}
RunResult run(const Option& opt, const Timer& timer,
              const fs::path& in,
              const fs::path& out) {
    HANDLE hjob = CreateJobObjectA(NULL, NULL);
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION limit;
    limit.BasicLimitInformation.PerProcessUserTimeLimit
        .QuadPart = timer.remain() * 10;
    limit.ProcessMemoryLimit =
        opt.get<int64_t>("MemoryLimit", 0) << 10;
    limit.BasicLimitInformation.LimitFlags =
        JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION |
        JOB_OBJECT_LIMIT_PROCESS_MEMORY |
        JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE |
        JOB_OBJECT_LIMIT_PROCESS_TIME;
    SetInformationJobObject(
        hjob, JobObjectExtendedLimitInformation,
        &limit, sizeof(limit));
    JOBOBJECT_END_OF_JOB_TIME_INFORMATION action;
    action.EndOfJobTimeAction =
        JOB_OBJECT_TERMINATE_AT_END_OF_JOB;
    SetInformationJobObject(
        hjob, JobObjectEndOfJobTimeInformation,
        &action, sizeof(action));
}
