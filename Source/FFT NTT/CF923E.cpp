#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 1 << 18, mod = 998244353;
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
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int root[size], invR[size], rev[size], tot;
void init(int n) {
    tot = n;
    Int64 base = powm(3, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for(int i = 1; i < n; ++i)
        root[i] = asInt64(root[i - 1]) * base % mod;
    for(int i = 1; i < n; ++i)
        invR[i] = asInt64(invR[i - 1]) * invBase % mod;
    int off = 0;
    while((1 << off) != n)
        ++off;
    --off;
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
                int &x = A[j + k], &y = A[j + m + k];
                int t = asInt64(w[fac * k]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
int A[size], B[size];
void mul(int siz) {
    int p = 1;
    while(p < siz * 2)
        p <<= 1;
    NTT(p, A, root);
    NTT(p, B, root);
    for(int i = 0; i < p; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    NTT(p, A, invR);
    Int64 div = mod - (mod - 1) / p;
    for(int i = 0; i < siz; ++i)
        A[i] = A[i] * div % mod;
    memset(A + siz, 0, sizeof(int) * (p - siz));
    memset(B, 0, sizeof(int) * p);
}
int fac[size], invFac[size];
int main() {
    int n;
    Int64 m;
    scanf("%d%lld", &n, &m);
    m = m % (mod - 1) * (mod - 2) % (mod - 1);
    fac[0] = 1;
    for(int i = 1; i <= n; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    invFac[0] = invFac[1] = 1;
    for(int i = 2; i <= n; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 1; i <= n; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    for(int i = 0; i <= n; ++i)
        A[n - i] = read() * asInt64(fac[i]) % mod;
    int siz = n + 1, p = 1;
    while(p < siz * 2)
        p <<= 1;
    init(p);
    memcpy(B, invFac, sizeof(int) * siz);
    mul(siz);
    std::reverse(A, A + siz);
    for(int i = 0; i < siz; ++i)
        A[i] = A[i] * powm(i + 1, m) % mod;
    std::reverse(A, A + siz);
    for(int i = 0; i < siz; ++i) {
        int x = invFac[i];
        if(i & 1)
            B[i] = (x ? mod - x : 0);
        else
            B[i] = x;
    }
    mul(siz);
    std::reverse(A, A + siz);
    for(int i = 0; i < siz; ++i) {
        int x = A[i] * asInt64(invFac[i]) % mod;
        printf("%d ", x);
    }
    return 0;
}
