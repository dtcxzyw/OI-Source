#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int maxM = 300005, maxN = 10000005, mod = 1004535809, g = 3;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a >= mod ? a - mod : a;
}
int sub(int a, int b) {
    a -= b;
    return a < 0 ? a + mod : a;
}
int root[maxM], invR[maxM], tot;
void init(int n) {
    tot = n;
    Int64 base = powm(g, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for (int i = 1; i < n; ++i) root[i] = root[i - 1] * base % mod;
    for (int i = 1; i < n; ++i) invR[i] = invR[i - 1] * invBase % mod;
}
void NTT(int n, int *A, int *w) {
    for (int i = 0, j = 0; i < n; ++i) {
        if (i > j) std::swap(A[i], A[j]);
        for (int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
    for (int i = 2; i <= n; i <<= 1) {
        int m = i >> 1, fac = tot / i;
        for (int j = 0; j < n; j += i) {
            for (int k = 0; k < m; ++k) {
                int t = asInt64(A[j + k + m]) * w[fac * k] % mod;
                A[j + k + m] = sub(A[j + k], t);
                A[j + k] = add(A[j + k], t);
            }
        }
    }
}
void mul(int n, int *A, int *B) {
    int m = 1;
    while (m < (n << 1)) m <<= 1;
    init(m);
    NTT(m, A, root);
    NTT(m, B, root);
    for (int i = 0; i < m; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    NTT(m, A, invR);
    Int64 div = powm(m, mod - 2);
    for (int i = 0; i < n; ++i)
        A[i] = A[i] * div % mod;
}
int A[maxM] = {}, B[maxM], fac[maxN], invFac[maxN];
void initFac(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    invFac[n] = powm(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        invFac[i - 1] = asInt64(invFac[i]) * i % mod;
}
int main() {
    int n = read();
    int m = read();
    int s = read();
    int e = std::min(n / s, m);
    initFac(std::max(n, m));
    for (int i = 0; i <= e; ++i)
        A[i] = asInt64(read()) * invFac[i] % mod;
    for (int i = 0; i <= e; ++i) {
        Int64 f = (i & 1 ? mod - 1 : 1);
        B[i] = f * invFac[i] % mod;
    }
    mul(e + 1, A, B);
    Int64 k1 = asInt64(fac[m]) * fac[n] % mod, k3 = 1;
    int res = 0;
    for (int i = 0; i <= e; ++i) {
        Int64 k2 = asInt64(invFac[m - i]) * invFac[n - i * s] % mod;
        Int64 k = k1 * k2 % mod * k3 % mod * powm(m - i, n - i * s) % mod;
        res = add(res, k * A[i] % mod);
        k3 = k3 * invFac[s] % mod;
    }
    printf("%d\n", res);
    return 0;
}
