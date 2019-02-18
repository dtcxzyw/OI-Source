#pragma once
#include <pthread.h>
#include <sched.h>
#include <sys/resource.h>
#include <unistd.h>
using Duration = int64_t;
class TimePoint {
private:
    Duration tp;

public:
    TimePoint() {
        rusage res;
        getrusage(RUSAGE_THREAD, &res);
        constexpr Duration fac = 1000000;
        tp = res.ru_utime.tv_sec * fac +
            res.ru_utime.tv_usec % fac;
    }
    Duration operator-(const TimePoint& rhs) const {
        return tp - rhs.tp;
    }
};

void resetTimer() {
    pid_t pid = getpid();
    struct sched_param param;
    param.sched_priority =
        sched_get_priority_max(SCHED_FIFO);
    sched_setscheduler(pid, SCHED_RR, &param);
    pthread_setschedparam(pthread_self(), SCHED_FIFO,
                          &param);
}

TimePoint now() {
    return TimePoint{};
}

double count(Duration dur) {
    return dur;
}

double toMilliSecond(Duration dur) {
    return dur * 1e-3;
}
