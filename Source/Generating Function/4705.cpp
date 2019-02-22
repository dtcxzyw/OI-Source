#include <algorithm>
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
const int size = 1 << 20, mod = 998244353;
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
typedef std::vector<int> Poly;
Poly root[25], invR[25], rev[25];
void initImpl(int k) {
    int n = 1 << k;
    Poly &r = root[k], &ir = invR[k];
    r.resize(n), ir.resize(n);
    Int64 base = powm(3, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    r[0] = ir[0] = 1;
    for(int i = 1; i < n; ++i)
        r[i] = asInt64(r[i - 1]) * base % mod;
    for(int i = 1; i < n; ++i)
        ir[i] = asInt64(ir[i - 1]) * invBase % mod;
    Poly& rv = rev[k];
    rv.resize(n);
    int off = k - 1;
    for(int i = 1; i < n; ++i)
        rv[i] = rv[i >> 1] >> 1 | ((i & 1) << off);
}
void init(int n) {
    for(int i = 0; (1 << i) <= n; ++i)
        if(rev[i].empty())
            initImpl(i);
}
int getSize(int n) {
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
}
void NTT(int n, Poly& A, const Poly* w) {
    int p = 0;
    while((1 << p) != n)
        ++p;
    Poly& R = rev[p];
    for(int i = 0; i < n; ++i)
        if(i < R[i])
            std::swap(A[i], A[R[i]]);
    for(int i = 2, cp = 1; i <= n; i <<= 1, ++cp) {
        int m = i >> 1;
        const Poly& cw = w[cp];
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + m + k];
                int t = asInt64(cw[k]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
int* data(Poly& A) {
    return &*A.begin();
}
const int* data(const Poly& A) {
    return &*A.begin();
}
void DFT(int n, Poly& A) {
    NTT(n, A, root);
}
void IDFT(int n, Poly& A) {
    NTT(n, A, invR);
}
void IDFTEx(int n, Poly& A, int b, int e,
            bool lc = true, bool hc = true) {
    IDFT(n, A);
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
Int64 fac;
Poly mul(const Poly& X, const Poly& Y) {
    int end = X.size() + Y.size() - 1;
    if(end <= 512) {
        Poly res(end);
        for(int i = 0; i < X.size(); ++i)
            for(int j = 0; j < Y.size(); ++j)
                res[i + j] = (res[i + j] +
                              asInt64(X[i]) * Y[j]) %
                    mod;
        return res;
    }
    int siz = getSize(end);
    fac = fac * siz % mod;
    Poly A(siz);
    memcpy(data(A), data(X), sizeof(int) * X.size());
    DFT(siz, A);
    Poly B(siz);
    memcpy(data(B), data(Y), sizeof(int) * Y.size());
    DFT(siz, B);
    for(int i = 0; i < siz; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    IDFT(siz, A);
    Poly res(end);
    memcpy(data(res), data(A), sizeof(int) * end);
    return res;
}
Poly getMImpl(int l, int r) {
    if(l == r) {
        Poly res(2);
        res[0] = 1;
        int x = read();
        res[1] = (x ? mod - x : 0);
        return res;
    } else {
        int m = (l + r) >> 1;
        return mul(getMImpl(l, m), getMImpl(m + 1, r));
    }
}
Poly getM(int n) {
    fac = 1;
    Poly res = getMImpl(1, n);
    fac = powm(fac, mod - 2);
    for(int i = 0; i <= n; ++i)
        res[i] = res[i] * fac % mod;
    return res;
}
void inv(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = powm(sf[0], mod - 2);
    else {
        int h = n >> 1;
        inv(h, sf, g);

        Poly dftg(n);
        copy(dftg, g, h);
        DFT(n, dftg);

        Poly f(n);
        copy(f, sf,
             std::min(n, static_cast<int>(sf.size())));
        DFT(n, f);

        for(int i = 0; i < n; ++i)
            f[i] = asInt64(f[i]) * dftg[i] % mod;
        IDFTEx(n, f, h, n);

        DFT(n, f);
        for(int i = 0; i < n; ++i)
            f[i] = asInt64(f[i]) * dftg[i] % mod;
        IDFTEx(n, f, h, n, false);

        for(int i = h; i < n; ++i)
            g[i] = (f[i] ? mod - f[i] : 0);
    }
}
int invFac[size];
void getF(Poly& g, int t) {
    int n = g.size() - 1;
    if(g.size() > t)
        g.resize(t);
    int siz = getSize(t * 2);
    Poly ig(siz);
    inv(getSize(t), g, ig);
    memset(data(ig) + t, 0,
           sizeof(int) * (getSize(t) - t));
    DFT(siz, ig);
    for(int i = 1; i <= n; ++i)
        g[i - 1] = asInt64(g[i]) * i % mod;
    g[n] = 0;
    g.resize(siz);
    DFT(siz, g);
    for(int i = 0; i < siz; ++i)
        g[i] = asInt64(g[i]) * ig[i] % mod;
    IDFTEx(siz, g, 0, t);
    for(int i = t - 1; i >= 1; --i) {
        int x = g[i - 1];
        g[i] = asInt64(invFac[i]) * (x ? mod - x : 0) %
            mod;
    }
    g[0] = n;
}
int main() {
    int n = read();
    int m = read();
    init(getSize((std::max(n, m) + 1) * 2));
    Poly A = getM(n);
    Poly B = getM(m);
    int t = read() + 1;
    init(getSize(t * 2));
    invFac[0] = invFac[1] = 1;
    for(int i = 2; i < t; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 1; i < t; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    getF(A, t);
    getF(B, t);
    int siz = getSize(t * 2);
    DFT(siz, A);
    DFT(siz, B);
    for(int i = 0; i < siz; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    IDFTEx(siz, A, 1, t, false, false);
    Int64 cur = powm(asInt64(n) * m % mod, mod - 2);
    for(int i = 1; i < t; ++i) {
        cur = cur * i % mod;
        int res = A[i] * cur % mod;
        printf("%d\n", res);
    }
    return 0;
}
