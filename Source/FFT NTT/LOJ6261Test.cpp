#include "../../Review/Polynomial/Perf/PolyExp.hpp"
#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int main() {
    int n;
    Int64 k;
    scanf("%d%lld", &n, &k);
    int p = 1;
    while(p < 2 * n)
        p <<= 1;
    Poly A(p), B(p);
    for(int i = 0; i < n; ++i)
        A[i] = 1;
    lut[1] = 1;
    preInv(p);
    getLnFast(n, A, B);
    for(int i = 0; i < n; ++i)
        B[i] = B[i] * k % mod;
    Poly C(p);
    getExpFast(n, B, C);
    Poly D(p);
    for(int i = 0; i < n; ++i)
        D[i] = read();
    DFT(p, C);
    DFT(p, D);
    for(int i = 0; i < p; ++i)
        D[i] = asInt64(D[i]) * C[i] % mod;
    IDFT(p, D, 0, n, false);
    for(int i = 0; i < n; ++i)
        printf("%d\n", D[i]);
    return 0;
}
