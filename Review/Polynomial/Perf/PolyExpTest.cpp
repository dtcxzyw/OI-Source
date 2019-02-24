#include "PolyExp.hpp"
#include <cstdio>
int main() {
    init();
    const int n = 1 << 22;
    Duration base = benchmark("NTT", n, benchmarkNTT);
    Duration expA = benchmark("PolyExp", n, [](int n) {
        return benchmarkExp(n, getExp);
    });
    Duration expB =
        benchmark("PolyExpFast", n, [](int n) {
            return benchmarkExp(n, getExpFast);
        });
    Duration expC =
        benchmark("PolyExpCDQ", n, [](int n) {
            return benchmarkExp(n, getExpCDQ);
        });
    printf("ratio(Exp)=%.2lf\n",
           calcRatio(expA, base));
    printf("ratio(ExpFast)=%.2lf\n",
           calcRatio(expB, base));
    printf("ratio(ExpCDQ)=%.2lf\n",
           calcRatio(expC, base));
    return 0;
}
