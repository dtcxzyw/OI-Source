#include "PolyInv.hpp"
#include <cstdio>
int main() {
    init();
    const int n = 1 << 22;
    Duration base = benchmark("NTT", n, benchmarkNTT);
    Duration invA = benchmark("PolyInv", n, [](int n) {
        return benchmarkInv(n, getInv);
    });
    Duration invB =
        benchmark("PolyInvFast", n, [](int n) {
            return benchmarkInv(n, getInvFast);
        });
    printf("ratio(Inv)=%.2lf\n",
           calcRatio(invA, base));
    printf("ratio(InvFast)=%.2lf\n",
           calcRatio(invB, base));
    return 0;
}
