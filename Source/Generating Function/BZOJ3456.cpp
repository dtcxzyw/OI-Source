#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using Int64 = long long;
#define asInt64 static_cast<Int64>
constexpr int mod = 1004535809, size = 1 << 17;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int clamp(int a) {
    return a >= 0 ? a : a + mod;
}
Int64 powm(Int64 a, Int64 k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
typedef std::vector<int> Poly;
Poly rc[25], irc[25], rvc[25];
const Poly& getRev(int k) {
    if(rvc[k].empty()) {
        int n = 1 << k, off = k - 1;
        Poly& rev = rvc[k];
        rev.resize(n);
        for(int i = 1; i < n; ++i)
            rev[i] =
                rev[i >> 1] >> 1 | ((i & 1) << off);
    }
    return rvc[k];
}
const Poly& getRoot(int k) {
    if(rc[k].empty()) {
        int n = 1 << k;
        Int64 base = powm(3, (mod - 1) / n);
        Poly& root = rc[k];
        root.resize(n);
        root[0] = 1;
        for(int i = 1; i < n; ++i)
            root[i] = root[i - 1] * base % mod;
    }
    return rc[k];
}
const Poly& getInvRoot(int k) {
    if(irc[k].empty()) {
        int n = 1 << k;
        Int64 base = powm(3, (mod - 1) / n);
        Int64 invBase = powm(base, mod - 2);
        Poly& invR = irc[k];
        invR.resize(n);
        invR[0] = 1;
        for(int i = 1; i < n; ++i)
            invR[i] = invR[i - 1] * invBase % mod;
    }
    return irc[k];
}
typedef const Poly& (*Func)(int);
void NTT(int n, Poly& A, Func w) {
    int p = 0;
    while((1 << p) != n)
        ++p;
    const Poly& rev = getRev(p);
    for(int i = 0; i < n; ++i)
        if(i < rev[i])
            std::swap(A[i], A[rev[i]]);
    for(int i = 2, cp = 1; i <= n; i <<= 1, ++cp) {
        int m = i >> 1;
        const Poly& cw = w(cp);
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
void copyPoly(Poly& dst, const Poly& src, int siz) {
    memcpy(data(dst), data(src), sizeof(int) * siz);
}
void DFT(int n, Poly& A) {
    NTT(n, A, getRoot);
}
void IDFT(int n, Poly& A, int b, int e,
          bool clear = true) {
    NTT(n, A, getInvRoot);
    Int64 div = mod - (mod - 1) / n;
    for(int i = b; i < e; ++i)
        A[i] = A[i] * div % mod;
    if(clear) {
        memset(data(A), 0, sizeof(int) * b);
        memset(data(A) + e, 0, sizeof(int) * (n - e));
    }
}
int getSize(int n) {
    n <<= 1;
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
}
void fastInvIter(int n, const Poly& sf,
                 const Poly& dftg, Poly& g) {
    int h = n >> 1;
    Poly f(n);
    copyPoly(f, sf, n);
    DFT(n, f);

    for(int i = 0; i < n; ++i)
        f[i] = asInt64(f[i]) * dftg[i] % mod;
    IDFT(n, f, h, n);

    DFT(n, f);
    for(int i = 0; i < n; ++i)
        f[i] = asInt64(f[i]) * dftg[i] % mod;
    IDFT(n, f, h, n, false);

    for(int i = h; i < n; ++i)
        g[i] = (f[i] ? mod - f[i] : 0);
}
void getInvFastImpl(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = powm(sf[0], mod - 2);
    else {
        int h = n >> 1;
        getInvFastImpl(h, sf, g);
        Poly dftg(n);
        copyPoly(dftg, g, h);
        DFT(n, dftg);
        fastInvIter(n, sf, dftg, g);
    }
}
void getInvFast(int n, const Poly& sf, Poly& g) {
    int p = 1;
    while(p < n)
        p <<= 1;
    getInvFastImpl(p, sf, g);
    memset(data(g) + n, 0, sizeof(int) * (p - n));
}
int lut[size];
void preInv(int n) {
    static int cur = 1;
    lut[1] = 1;
    while(cur < n) {
        ++cur;
        lut[cur] = asInt64(mod - mod / cur) *
            lut[mod % cur] % mod;
    }
}
void der(int n, Poly& f) {
    for(int i = 1; i < n; ++i)
        f[i - 1] = i * asInt64(f[i]) % mod;
    f[n - 1] = 0;
}
void inte(int n, Poly& f) {
    preInv(n);
    for(int i = n - 1; i >= 1; --i)
        f[i] = asInt64(lut[i]) * f[i - 1] % mod;
    f[0] = 0;
}
void getLnFast(int n, Poly& sf, Poly& g) {
    int p = getSize(n);
    getInvFast(n, sf, g);
    DFT(p, g);
    der(n, sf);
    DFT(p, sf);
    for(int i = 0; i < p; ++i)
        g[i] = asInt64(sf[i]) * g[i] % mod;
    IDFT(p, g, 0, n);
    inte(n, g);
}
int invFac[size];
int main() {
    int n;
    scanf("%d", &n);
    ++n;
    preInv(n);
    invFac[0] = 1;
    for(int i = 1; i < n; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * lut[i] % mod;
    int p = 1;
    while(p < n * 2)
        p <<= 1;
    Poly F(p), G(p);
    for(int i = 0; i < n; ++i)
        F[i] = asInt64(invFac[i]) *
            powm(2, asInt64(i) * (i - 1) / 2) % mod;
    getLnFast(n, F, G);
    --n;
    printf("%lld\n",
           G[n] * powm(invFac[n], mod - 2) % mod);
    return 0;
}
