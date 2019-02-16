#include "PolyInv.hpp"
#include <cstdio>
int main() {
    init();
    const int n = 1 << 22;
    Clock::duration base =
        benchmark("NTT", n, benchmarkNTT);
    Clock::duration invA =
        benchmark("PolyInv", n, [](int n) {
            return benchmarkInv(n, getInv);
        });
    printf("ratio(Inv)=%.2lf\n",
           calcRatio(invA, base));
    return 0;
}
