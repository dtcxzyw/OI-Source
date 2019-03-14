#include <chrono>
#include <cstdio>
#include <random>
using Int64 = long long;
const Int64 mod = 1000000000000037;
Int64 add(Int64 a, Int64 b) {
    a += b;
    return a >= mod ? a - mod : a;
}
Int64 mulmA(Int64 a, Int64 b) {
    Int64 res = 0;
    while(b) {
        if(b & 1)
            res = add(res, a);
        b >>= 1, a = add(a, a);
    }
    return res;
}
Int64 mulmB(Int64 a, Int64 b) {
    Int64 res =
        (a * b -
         static_cast<Int64>(static_cast<double>(a) /
                            mod * b) *
             mod) %
        mod;
    return res < 0 ? res + mod : res;
}
using Clock = std::chrono::high_resolution_clock;
int main() {
    std::mt19937_64 eng(
        Clock::now().time_since_epoch().count());
    std::uniform_int_distribution<Int64> gen(0,
                                             mod - 1);
    for(int i = 0;; ++i) {
        Int64 a = gen(eng), b = gen(eng);
        if(mulmA(a, b) != mulmB(a, b))
            throw;
        if((i & 0xffff) == 0)
            printf("%d\n", i);
    }
    return 0;
}
