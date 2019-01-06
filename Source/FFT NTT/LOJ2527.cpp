#include <algorithm>
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
const int size = 1 << 18, maxn = 10000005,
          mod = 1004535809;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int tot, root[size], invR[size], rev[size];
void init(int n, int off) {
    tot = n;
    Int64 base = powm(3, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for(int i = 1; i < n; ++i)
        root[i] = root[i - 1] * base % mod;
    for(int i = 1; i < n; ++i)
        invR[i] = invR[i - 1] * invBase % mod;
    rev[0] = 0;
    for(int i = 1; i < n; ++i)
        rev[i] = rev[i >> 1] >> 1 | ((i & 1) << off);
}
void NTT(int n, int* A, const int* w) {
    for(int i = 0; i < n; ++i)
        if(i < rev[i])
            std::swap(A[i], A[rev[i]]);
    for(int i = 2; i <= n; i <<= 1) {
        int m = i >> 1, fac = tot / i;
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + k + m];
                int t = asInt64(w[k * fac]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
int A[size], B[size], fac[maxn], invFac[maxn];
int main() {
    int n = read();
    int m = read();
    int s = read();
    int end = std::min(m, n / s);
    fac[0] = invFac[0] = invFac[1] = 1;
    int pend = std::max(n, m);
    for(int i = 1; i <= pend; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    for(int i = 2; i <= pend; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 2; i <= pend; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    for(int i = 0; i <= end; ++i)
        A[i] = asInt64(read()) * invFac[i] % mod;
    for(int i = 0; i <= end; ++i) {
        int x = invFac[i];
        B[i] = (i & 1 ? mod - x : x);
    }
    int p = 1, off = -1;
    while(p <= (end << 1))
        p <<= 1, ++off;
    init(p, off);
    NTT(p, A, root);
    NTT(p, B, root);
    for(int i = 0; i < p; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    NTT(p, A, invR);
    Int64 sum = 0;
    for(int i = 0; i <= end; ++i) {
        int x = n - i * s;
        Int64 c = powm(m - i, x) * invFac[m - i] %
            mod * powm(invFac[s], i) % mod *
            invFac[x] % mod;
        sum = (sum + A[i] * c) % mod;
    }
    Int64 scale =
        powm(p, mod - 2) * fac[n] % mod * fac[m] % mod;
    printf("%lld\n", sum * scale % mod);
    return 0;
}
