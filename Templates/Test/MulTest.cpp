#include <chrono>
#include <cstdio>
#include <random>
using Int64 = long long;
Int64 add(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a >= mod ? a - mod : a;
}
Int64 mulmA(Int64 a, Int64 b, Int64 mod) {
    Int64 res = 0;
    while(b) {
        if(b & 1)
            res = add(res, a, mod);
        b >>= 1, a = add(a, a, mod);
    }
    return res;
}
Int64 mulmB(Int64 a, Int64 b, Int64 mod) {
    Int64 res =
        (a * b -
         static_cast<Int64>(
             static_cast<long double>(a) / mod * b) *
             mod) %
        mod;
    return res < 0 ? res + mod : res;
}
using Clock = std::chrono::high_resolution_clock;
int main() {
    std::mt19937_64 eng(
        Clock::now().time_since_epoch().count());
    std::uniform_int_distribution<Int64> mgen(
        1LL << 33, 1LL << 62);
    for(int i = 0;; ++i) {
        Int64 mod = mgen(eng);
        std::uniform_int_distribution<Int64> gen(
            0, mod - 1);
        Int64 a = gen(eng), b = gen(eng);
        if(mulmA(a, b, mod) != mulmB(a, b, mod))
            throw;
        if((i & 0xffff) == 0)
            printf("%d\n", i);
    }
    return 0;
}
