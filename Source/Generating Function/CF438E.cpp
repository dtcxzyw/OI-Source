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
const int mod = 998244353;
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
Poly rc[20], irc[20], rvc[20];
const Poly& getRev(int k) {
    if(rvc[k].empty()) {
        int off = k - 1, siz = 1 << k;
        Poly& rev = rvc[k];
        rev.resize(siz);
        for(int i = 1; i < siz; ++i)
            rev[i] =
                rev[i >> 1] >> 1 | ((i & 1) << off);
    }
    return rvc[k];
}
typedef const Poly& (*Func)(int);
const Poly& getRoot(int k) {
    if(rc[k].empty()) {
        int siz = 1 << k;
        Int64 base = powm(3, (mod - 1) / siz);
        Poly& root = rc[k];
        root.resize(siz);
        root[0] = 1;
        for(int i = 1; i < siz; ++i)
            root[i] =
                asInt64(root[i - 1]) * base % mod;
    }
    return rc[k];
}
const Poly& getInvRoot(int k) {
    if(irc[k].empty()) {
        int siz = 1 << k;
        Int64 base = powm(3, (mod - 1) / siz);
        Int64 invBase = powm(base, mod - 2);
        Poly& invR = irc[k];
        invR.resize(siz);
        invR[0] = 1;
        for(int i = 1; i < siz; ++i)
            invR[i] =
                asInt64(invR[i - 1]) * invBase % mod;
    }
    return irc[k];
}
int* data(Poly& A) {
    return &*A.begin();
}
const int* data(const Poly& A) {
    return &*A.begin();
}
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
void DFT(int n, Poly& A) {
    NTT(n, A, getRoot);
}
void IDFT(int n, Poly& A, int b, int e, bool lc = true,
          bool hc = true) {
    NTT(n, A, getInvRoot);
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
void fastInvIter(int n, const Poly& sf,
                 const Poly& dftg, Poly& g) {
    int h = n >> 1;
    Poly f(n);
    copy(f, sf, n);
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
const Int64 negInv2 = mod - (mod + 1) / 2;
void solve(int n, const Poly& sf, Poly& g, Poly& tg,
           Poly& itg, bool doInv = false) {
    if(n == 1) {
        g[0] = 1;
        tg[0] = itg[0] = mod - 1;
    } else {
        int h = n >> 1, p = n << 1;
        solve(h, sf, g, tg, itg, true);

        Poly dftitg(n);
        copy(dftitg, itg, h);
        DFT(n, dftitg);

        Poly f(p);
        copy(f, sf, n);
        DFT(p, f);

        {
            int p = n << 1;
            Poly A(p);
            copy(A, g, h);
            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * A[i] % mod;
            IDFT(n, A, 0, n);

            DFT(p, A);
            for(int i = 0; i < p; ++i)
                A[i] = asInt64(f[i]) * A[i] % mod;
            IDFT(p, A, h, n);

            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * dftitg[i] % mod;
            IDFT(n, A, h, n, false);

            for(int i = h; i < n; ++i)
                g[i] = (A[i] ? mod - A[i] : 0);
        }

        if(doInv) {
            copy(tg, g, n);
            DFT(p, tg);
            for(int i = 0; i < p; ++i)
                tg[i] =
                    asInt64(f[i]) * tg[i] * 2 % mod;
            IDFT(p, tg, 0, n);
            tg[0] = mod - 1;

            fastInvIter(n, tg, dftitg, itg);
        }
    }
}
int main() {
    int n = read();
    int m = read() + 1;
    int p = 1;
    while(p < m)
        p <<= 1;
    int siz = p << 1;

    Poly F(siz);
    for(int i = 0; i < n; ++i) {
        int x = read();
        if(x < m)
            F[x] = 1;
    }

    Poly G(siz), TG(siz), ITG(siz);
    solve(p, F, G, TG, ITG, false);

    for(int i = 1; i < m; ++i)
        printf("%d\n", G[i]);
    return 0;
}
