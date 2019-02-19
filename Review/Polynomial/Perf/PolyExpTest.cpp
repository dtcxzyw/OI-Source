#include "PolyExp.hpp"
#include <cstdio>
int main() {
    init();
    const int n = 1 << 4;
    Duration base = benchmark("NTT", n, benchmarkNTT);
    Duration expA = benchmark("PolyExp", n, [](int n) {
        return benchmarkExp(n, getExp);
    });
    Duration expB =
        benchmark("PolyExpFast", n, [](int n) {
            return benchmarkExp(n, getExpFast);
        });
    printf("ratio(Exp)=%.2lf\n",
           calcRatio(expA, base));
    printf("ratio(ExpFast)=%.2lf\n",
           calcRatio(expB, base));
    return 0;
}
