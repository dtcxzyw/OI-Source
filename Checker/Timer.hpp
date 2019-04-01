#pragma once
#include "Common.hpp"
enum class TimeMode { allTask, perTask };
enum class TimeVal { totTime, usrTime };
class Timer final {
public:
    void addTask(int64_t usrTime, int64_t totTime);
    bool isTLE(int64_t usrTime, int64_t totTime) const;
    Timer(const Option& opt);
    bool isTLE() const;
    void report() const;
    int64_t choose(int64_t usrTime,
                   int64_t totTime) const;
    int64_t remainSeconds() const;

private:
    int64_t mTotTime, mMaxTime, mTimeLimit;
    TimeMode mMode;
    TimeVal mVal;
};
