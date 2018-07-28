#include <cstdio>
#include <utility>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 300000, mod = 998244353;
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
int root[size], invR[size], tot;
void init(int n) {
    const int g = 3;
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
int fac[size], invFac[size], A[size], B[size];
int main() {
    int n;
    scanf("%d", &n);
    fac[0] = invFac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = asInt64(fac[i - 1]) * i % mod;
    invFac[n] = powm(fac[n], mod - 2);
    for (int i = n; i > 1; --i) invFac[i - 1] = asInt64(invFac[i]) * i % mod;
    for (int i = 0; i <= n; ++i) A[i] = (i & 1 ? mod - invFac[i] : invFac[i]);
    B[0] = 1, B[1] = n + 1;
    for (int i = 2; i <= n; ++i)
        B[i] = sub(powm(i, n + 1), 1) * powm(i - 1, mod - 2) % mod * invFac[i] % mod;
    int siz = 1;
    while (siz < ((n + 1) << 1)) siz <<= 1;
    init(siz);
    NTT(siz, A, root);
    NTT(siz, B, root);
    for (int i = 0; i < siz; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    NTT(siz, A, invR);
    Int64 k = powm(siz, mod - 2);
    int res = 0;
    for (int i = 0; i <= n; ++i) {
        res = (res + k * A[i]) % mod;
        k = k * 2 * (i + 1) % mod;
    }
    printf("%d\n", res);
    return 0;
}
