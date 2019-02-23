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
const Int64 negInv2 = mod - (mod + 1) / 2;
void sqrt(int n, const Poly& sf, Poly& g, Poly& ig,
          bool doInv) {
    if(n == 1)
        g[0] = ig[0] = 1;
    else {
        int h = n >> 1;
        sqrt(h, sf, g, ig, true);

        Poly dftig(n);
        copy(dftig, ig, h);
        DFT(n, dftig);

        {
            Poly A(n);
            copy(A, g, h);
            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * A[i] % mod;
            IDFT(n, A, h, n);

            for(int i = h; i < n; ++i)
                A[i] = sub(A[i], sf[i]);

            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * dftig[i] % mod;
            IDFT(n, A, h, n, false);

            for(int i = h; i < n; ++i)
                g[i] = A[i] * negInv2 % mod;
        }

        if(doInv) {
            Poly A(n);
            copy(A, g, n);
            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * dftig[i] % mod;
            IDFT(n, A, h, n);

            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * dftig[i] % mod;
            IDFT(n, A, h, n, false);

            for(int i = h; i < n; ++i)
                ig[i] = (A[i] ? mod - A[i] : 0);
        }
    }
}
int main() {
    int n = read();
    int p = 1;
    while(p < n)
        p <<= 1;
    Poly A(p);
    for(int i = 0; i < n; ++i)
        A[i] = read();
    Poly G(p), IG(p);
    sqrt(p, A, G, IG, false);
    for(int i = 0; i < n; ++i)
        printf("%d ", G[i]);
    return 0;
}
