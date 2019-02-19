#include "NTT.hpp"
void benchmarkMulImpl(int n, Poly& a, Poly& b) {
    int p = getSize(n);
    DFT(p, a);
    DFT(p, b);
    for(int i = 0; i < p; ++i)
        a[i] = asInt64(a[i]) * b[i] % mod;
    IDFT(p, a, 0, 2 * n - 1);
}
Duration benchmarkMul(int n) {
    int p = getSize(n);
    puts("Generating input data for PolyMul...");
    Poly a = genData(n, p, mod);
    Poly b = genData(n, p, mod);
    puts("Calculating PolyMul...");
    Duration t =
        time([&] { benchmarkMulImpl(n, a, b); });
    puts("Done.");
    return t;
}
int main() {
    init();
    const int n = 1 << 22;
    Duration base = benchmark("NTT", n, benchmarkNTT);
    Duration mul =
        benchmark("PolyMul", n, benchmarkMul);
    printf("ratio(Mul)=%.2lf\n", calcRatio(mul, base));
    return 0;
}
