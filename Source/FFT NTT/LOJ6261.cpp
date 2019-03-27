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
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 1 << 18, mod = 998244353;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int root[size], invR[size], rev[size], tot;
void init(int n) {
    tot = n;
    Int64 base = powm(3, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for(int i = 1; i < n; ++i)
        root[i] = root[i - 1] * base % mod;
    for(int i = 1; i < n; ++i)
        invR[i] = invR[i - 1] * invBase % mod;
    int off = 1;
    while((1 << off) < n)
        ++off;
    --off;
    for(int i = 0; i < n; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << off;
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
                int t = asInt64(w[k * fac]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
int A[size], B[size], inv[size];
int main() {
    int n;
    Int64 k;
    scanf("%d%lld", &n, &k);
    for(int i = 0; i < n; ++i)
        A[i] = read();
    inv[1] = 1;
    for(int i = 2; i < n; ++i)
        inv[i] = asInt64(mod - mod / i) *
            inv[mod % i] % mod;
    Int64 off = (k - 1) % mod, cur = 1;
    B[0] = 1;
    for(int i = 1; i < n; ++i) {
        cur = cur * (off + i) % mod * inv[i] % mod;
        B[i] = cur;
    }
    int p = 1;
    while(p < 2 * n)
        p <<= 1;
    init(p);
    NTT(p, A, root);
    NTT(p, B, root);
    for(int i = 0; i < p; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    NTT(p, A, invR);
    Int64 div = mod - (mod - 1) / p;
    for(int i = 0; i < n; ++i) {
        int res = A[i] * div % mod;
        printf("%d\n", res);
    }
    return 0;
}
