#pragma once
#include "Common.hpp"
enum class TimeMode { allTask, perTask };
class Timer final {
public:
    void addTask(int64_t time);
    bool isTLE(int64_t time) const;
    Timer(const Option& opt);
    bool isTLE() const;
    void report() const;
    int64_t remain() const;
    void addSample();

private:
    int64_t mTotTime, mMaxTime, mTimeLimit,
        mLocalSamples, mRemoteSamples;
    TimeMode mMode;
    fs::path mSamples;
};
