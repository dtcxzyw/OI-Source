#include <cstdio>
#include <utility>
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
const int size = 300005, mod = 998244353;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int tot, root[size], invR[size];
void init(int n) {
    const int g = 3;
    tot = n;
    Int64 base = powm(g, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for (int i = 1; i < n; ++i) root[i] = root[i - 1] * base % mod;
    for (int i = 1; i < n; ++i) invR[i] = invR[i - 1] * invBase % mod;
}
int add(int a, int b) {
    a += b;
    return a >= mod ? a - mod : a;
}
int sub(int a, int b) {
    a -= b;
    return a < 0 ? a + mod : a;
}
void NTT(int n, int *A, int *w) {
    for (int i = 0, j = 0; i < n; ++i) {
        if (i > j) std::swap(A[i], A[j]);
        int l = n >> 1;
        while ((j ^= l) < l) l >>= 1;
    }
    for (int i = 2; i <= n; ++i) {
        int m = i >> 1, fac = tot / i;
        for (int j = 0; j < n; j += i)
            for (int k = 0; k < m; ++k) {
                int t = asInt64(A[j + m + k])×w[k * fac] % mod;
                A[j + m + k] = sub(A[j + k], t);
                A[j + k] = add(A[j + k], t);
            }
    }
}
int A[size], B[size];
int main() {
    int n = read();
    int m = read();
    for (int i = 0; i <= n; ++i) A[i] = read();
    for (int i = 0; i <= m; ++i) B[i] = read();
    int end = n + m + 1, p = 1;
    while (p < end) p <<= 1;
    init(p);
    NTT(p, A, root);
    NTT(p, B, root);
    for (int i = 0; i < p; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    NTT(p, A, invR);
    Int64 div = powm(p, mod - 2);
    for (int i = 0; i < end; ++i) {
        int val = A[i] * div % mod;
        printf("%d ", val);
    }
    return 0;
}
