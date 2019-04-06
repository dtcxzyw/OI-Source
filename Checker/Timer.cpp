#include "Timer.hpp"
#include "Runner.hpp"
#include <fstream>
#include <iostream>
int64_t Timer::choose(int64_t usr, int64_t tot) const {
    return mVal == TimeVal::totTime ? tot : usr;
}
void Timer::addTask(int64_t usrTime, int64_t totTime) {
    int64_t t = choose(usrTime, totTime);
    mTotTime += t;
    mMaxTime = std::max(mMaxTime, t);
}
bool Timer::isTLE(int64_t usrTime,
                  int64_t totTime) const {
    int64_t t = choose(usrTime, totTime);
    return (mMode == TimeMode::perTask ?
                t :
                t + mTotTime) > mTimeLimit;
}
Timer::Timer(const Option& opt)
    : mTotTime(0), mMaxTime(0),
      mTimeLimit(
          opt.get<int64_t>("TimeLimit", 1000000)),
      mLocalSamples(0), mRemoteSamples(0),
      mMode(opt.get("TimeMode", TimeMode::perTask)),
      mVal(opt.get("TimeVal", TimeVal::totTime)),
      mSamples(opt.get<fs::path>("TimeSamples", "")) {
    std::ifstream sam(mSamples);
    while(sam) {
        int64_t a, b;
        sam >> a >> b;
        mLocalSamples += a, mRemoteSamples += b;
    }
    if(mRemoteSamples) {
        mTimeLimit = mTimeLimit * mLocalSamples /
            mRemoteSamples;
        std::cout << "time scaling factor="
                  << static_cast<FT>(mLocalSamples) /
                mRemoteSamples
                  << std::endl;
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
int64_t Timer::remainSeconds() const {
    int64_t rm = mMode == TimeMode::perTask ?
        mTimeLimit :
        mTimeLimit - mTotTime;
    return rm / 1000000LL + 1;
}
void Timer::addSample() {
    std::ofstream sam(mSamples, std::ios::app);
    if(!sam)
        return;
    line("Add Time Sample");
    int64_t remote = 0,
            local = (mTotTime - 1) / 1000 + 1;
    std::cout << "OJ's time(prediction = "
              << local * mRemoteSamples / mLocalSamples
              << " ms): " << std::flush;
    std::cin >> remote;
    if(remote)
        sam << local << ' ' << remote << std::endl;
}
