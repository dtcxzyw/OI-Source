#pragma once
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <functional>
#include <random>
#include <vector>
constexpr int sampleCount = 100;
std::vector<int> genData(int n, int p, int mod) {
    static std::random_device device;
    std::vector<int> res(p);
    std::uniform_int_distribution<> uid(0, mod - 1);
    std::generate(res.begin(), res.begin() + n,
                  [&] { return uid(device); });
    return res;
}
using Clock = std::chrono::high_resolution_clock;
Clock::duration
time(const std::function<void()>& func) {
    Clock::time_point beg = Clock::now();
    func();
    return Clock::now() - beg;
}
using FT = double;
FT calcRatio(Clock::duration t, Clock::duration base) {
    FT ft = t.count(), fb = base.count();
    return ft / fb;
}
Clock::duration benchmark(
    const char* name, int n,
    const std::function<Clock::duration(int)>& func) {
    constexpr FT fac =
        static_cast<double>(std::milli::den) /
        static_cast<double>(Clock::period::den);
    puts("--------------------------------------");
    printf("Benchmark Task:%s\n", name);
    Clock::duration res{};
    for(int i = 0; i < sampleCount; ++i) {
        printf("Running Benchmark Test#%d\n", i);
        Clock::duration t = func(n);
        printf("Used time:%.0lf ms\n",
               t.count() * fac);
        res += t;
    }
    printf("Total time:%.0lf ms\n", res.count() * fac);
    puts("--------------------------------------");
    return res;
}
