#pragma once
#include <chrono>
using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;
using Duration = Clock::duration;

void resetTimer() {}

TimePoint now() {
    return Clock::now();
}

double count(const Duration& dur) {
    return dur.count();
}

double toMilliSecond(const Duration& dur) {
    constexpr double fac =
        static_cast<double>(std::milli::den) /
        static_cast<double>(Clock::period::den);
    return dur.count() * fac;
}
