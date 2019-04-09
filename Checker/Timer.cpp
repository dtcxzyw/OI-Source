#include "Timer.hpp"
#include "Runner.hpp"
#include <fstream>
#include <iostream>
void Timer::addTask(int64_t time) {
    mTotTime += time;
    mMaxTime = std::max(mMaxTime, time);
}
bool Timer::isTLE(int64_t time) const {
    return (mMode == TimeMode::perTask ? time : time +
                    mTotTime) > mTimeLimit;
}
Timer::Timer(const Option& opt)
    : mTotTime(0), mMaxTime(0),
      mTimeLimit(
          opt.get<int64_t>("TimeLimit", 1000000)),
      mLocalSamples(0), mRemoteSamples(0),
      mMode(opt.get("TimeMode", TimeMode::perTask)),
      mSamples(opt.get<fs::path>("TimeSamples", "")) {
    if(fs::exists(mSamples)) {
        std::ifstream sam(mSamples);
        while(sam) {
            int64_t a = 0, b = 0;
            sam >> a >> b;
            mLocalSamples += a, mRemoteSamples += b;
        }
        if(mRemoteSamples) {
            mTimeLimit = mTimeLimit * mLocalSamples /
                mRemoteSamples;
            std::cout
                << "time scaling factor="
                << static_cast<FT>(mLocalSamples) /
                    mRemoteSamples
                << std::endl;
        }
    } else {
        std::ofstream out(mSamples);
    }
}
bool Timer::isTLE() const {
    return mMode == TimeMode::allTask &&
        mTotTime > mTimeLimit;
}
void Timer::report() const {
    if(isTLE())
        std::cout << toString(Status::TLE)
                  << std::endl;
    else {
        std::cout << "TotTime " << mTotTime / 1000.0
                  << " ms";
        if(mTimeLimit && mMode == TimeMode::allTask)
            std::cout << "("
                      << mTotTime * 100 / mTimeLimit
                      << "%)";
        std::cout << std::endl;
        std::cout << "MaxTime " << mMaxTime / 1000.0
                  << " ms";
        if(mTimeLimit && mMode == TimeMode::perTask)
            std::cout << "("
                      << mMaxTime * 100 / mTimeLimit
                      << "%)";
        std::cout << std::endl;
    }
}
int64_t Timer::remain() const {
    return mMode == TimeMode::perTask ?
        mTimeLimit :
        mTimeLimit - mTotTime;
}
void Timer::addSample() {
    std::ofstream sam(mSamples, std::ios::app);
    if(!sam)
        return;
    line("Add Time Sample");
    int64_t remote = 0,
            local = (mTotTime - 1) / 1000 + 1;
    if(mLocalSamples)
        std::cout << "OJ's time(prediction = "
                  << local * mRemoteSamples /
                mLocalSamples
                  << " ms): " << std::flush;
    else
        std::cout << "OJ's time: " << std::flush;
    std::cin >> remote;
    if(remote)
        sam << local << ' ' << remote << std::endl;
}
