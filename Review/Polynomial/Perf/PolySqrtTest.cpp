#include "PolySqrt.hpp"
#include <cstdio>
int main() {
    init();
    const int n = 1 << 22;
    Duration base = benchmark("NTT", n, benchmarkNTT);
    Duration sqrtA =
        benchmark("PolySqrt", n, [](int n) {
            return benchmarkSqrt(n, getSqrt);
        });
    Duration sqrtB =
        benchmark("PolySqrtFast", n, [](int n) {
            return benchmarkSqrt(n, getSqrtFast);
        });
    printf("ratio(Sqrt)=%.2lf\n",
           calcRatio(sqrtA, base));
    printf("ratio(SqrtFast)=%.2lf\n",
           calcRatio(sqrtB, base));
    return 0;
}
