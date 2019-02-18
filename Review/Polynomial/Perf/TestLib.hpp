#pragma once
#include <algorithm>
#include <cstdio>
#include <functional>
#include <random>
#include <vector>
#ifdef WIN32
#include "WindowsTimer.hpp"
#else
#include "LinuxTimer.hpp"
#endif
constexpr int sampleCount = 1;
std::vector<int> genData(int n, int p, int mod) {
    static std::random_device device;
    std::vector<int> res(p);
    std::uniform_int_distribution<> uid(0, mod - 1);
    std::generate(res.begin(), res.begin() + n,
                  [&] { return uid(device); });
    return res;
}
Duration time(const std::function<void()>& func) {
    resetTimer();
    TimePoint beg = now();
    func();
    return now() - beg;
}
using FT = double;
FT calcRatio(Duration t, Duration base) {
    FT ft = count(t), fb = count(base);
    return ft / fb;
}
Duration
benchmark(const char* name, int n,
          const std::function<Duration(int)>& func) {
    puts("--------------------------------------");
    printf("Benchmark Task:%s\n", name);
    Duration res{};
    for(int i = 0; i < sampleCount; ++i) {
        printf("Running Benchmark Test#%d\n", i);
        Duration t = func(n);
        printf("Used time:%.0lf ms\n",
               toMilliSecond(t));
        res += t;
    }
    printf("Total time:%.0lf ms\n",
           toMilliSecond(res));
    puts("--------------------------------------");
    return res;
}
