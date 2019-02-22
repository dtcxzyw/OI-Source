#include <cstdio>
#include <cstring>
#include <vector>
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
const int size = 1 << 17, mod = 998244353;
typedef std::vector<int> Poly;
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
Poly root[18], invR[18], rev[18];
void initImpl(int k) {
    int n = 1 << k;
    Poly &r = root[k], &ir = invR[k];
    r.resize(n), ir.resize(n);
    Int64 base = powm(3, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    r[0] = ir[0] = 1;
    for(int i = 1; i < n; ++i)
        r[i] = r[i - 1] * base % mod;
    for(int i = 1; i < n; ++i)
        ir[i] = ir[i - 1] * invBase % mod;
    Poly& rv = rev[k];
    rv.resize(n);
    int off = k - 1;
    for(int i = 1; i < n; ++i)
        rv[i] = rv[i >> 1] >> 1 | ((i & 1) << off);
}
void init(int n) {
    for(int i = 0; (1 << i) <= n; ++i)
        initImpl(i);
}
int* data(Poly& A) {
    return &*A.begin();
}
const int* data(const Poly& A) {
    return &*A.begin();
}
void NTT(int n, Poly& A, const Poly* w) {
    int p = 0;
    while((1 << p) < n)
        ++p;
    Poly& rv = rev[p];
    for(int i = 0; i < n; ++i)
        if(i < rv[i])
            std::swap(A[i], A[rv[i]]);
    for(int i = 2, cp = 1; i <= n; i <<= 1, ++cp) {
        int m = i >> 1;
        const Poly& fac = w[cp];
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + m + k];
                int t = asInt64(fac[k]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
void DFT(int n, Poly& A) {
    NTT(n, A, root);
}
void IDFT(int n, Poly& A, int b, int e, bool lc = true,
          bool hc = true) {
    NTT(n, A, invR);
    Int64 div = powm(n, mod - 2);
    for(int i = b; i < e; ++i)
        A[i] = A[i] * div % mod;
    if(lc)
        memset(data(A), 0, sizeof(int) * b);
    if(hc)
        memset(data(A) + e, 0, sizeof(int) * (n - e));
}
void copy(Poly& dst, const Poly& src, int siz) {
    memcpy(data(dst), data(src), sizeof(int) * siz);
}
void clear(Poly& A) {
    Poly empty;
    A.swap(empty);
}
int lut[size + 100];
void exp(int n, const Poly& sf, Poly& g, Poly& ig,
         bool doInv) {
    if(n == 1)
        g[0] = ig[0] = 1;
    else {
        int h = n >> 1;
        exp(h, sf, g, ig, true);
        Poly dftig(n);
        copy(dftig, ig, h);
        DFT(n, dftig);
        {
            Poly A(n);
            for(int i = 1; i < h; ++i)
                A[i - 1] = asInt64(g[i]) * i % mod;
            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * dftig[i] % mod;
            IDFT(n, A, h - 1, n - 1, false);
            Poly B(n), dftg(n);
            copy(dftg, g, h);
            DFT(n, dftg);
            for(int i = 0; i < n; ++i)
                B[i] =
                    asInt64(dftg[i]) * dftig[i] % mod;
            IDFT(n, B, h, n);
            Poly f(n);
            for(int i = 1; i < h; ++i)
                f[i - 1] = asInt64(sf[i]) * i % mod;
            DFT(n, f);
            DFT(n, B);
            for(int i = 0; i < n; ++i)
                B[i] = asInt64(f[i]) * B[i] % mod;
            clear(f);
            IDFT(n, B, h - 1, n - 1, false);
            for(int i = n - 1; i >= h; --i) {
                Int64 x = sub(A[i - 1], B[i - 1]);
                A[i] = x * lut[i] % mod;
            }
            memset(data(A), 0, sizeof(int) * h);
            clear(B);
            for(int i = h; i < n; ++i)
                A[i] = sub(A[i], sf[i]);
            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * dftg[i] % mod;
            IDFT(n, A, h, n, false);
            for(int i = h; i < n; ++i)
                g[i] = (A[i] ? mod - A[i] : 0);
        }
        if(doInv) {
            Poly f(n);
            copy(f, g, n);
            DFT(n, f);
            for(int i = 0; i < n; ++i)
                f[i] = asInt64(f[i]) * dftig[i] % mod;
            IDFT(n, f, h, n);
            DFT(n, f);
            for(int i = 0; i < n; ++i)
                f[i] = asInt64(f[i]) * dftig[i] % mod;
            IDFT(n, f, h, n, false);
            for(int i = h; i < n; ++i)
                ig[i] = (f[i] ? mod - f[i] : 0);
        }
    }
}
int cnt[size];
int main() {
    int n = read();
    int m = read();
    int p = 1;
    while(p <= m)
        p <<= 1;
    init(p);
    lut[1] = 1;
    for(int i = 2; i < p; ++i)
        lut[i] = asInt64(mod - mod / i) *
            lut[mod % i] % mod;
    Poly A(p);
    for(int i = 1; i <= n; ++i)
        ++cnt[read()];
    for(int i = 1; i <= m; ++i)
        if(cnt[i]) {
            for(int j = 1, vj = i; vj <= m;
                ++j, vj += i)
                A[vj] = (A[vj] +
                         asInt64(cnt[i]) * lut[j]) %
                    mod;
        }
    Poly g(p), ig(p);
    exp(p, A, g, ig, false);
    for(int i = 1; i <= m; ++i)
        printf("%d\n", g[i]);
    return 0;
}
