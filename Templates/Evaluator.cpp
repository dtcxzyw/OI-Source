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
void IDFT(int n, Poly& A, int b, int e,
          bool clear = true) {
    NTT(n, A, getInvRoot);
    Int64 div = powm(n, mod - 2);
    for(int i = b; i < e; ++i)
        A[i] = A[i] * div % mod;
    if(clear) {
        memset(data(A), 0, sizeof(int) * b);
        memset(data(A) + e, 0, sizeof(int) * (n - e));
    }
}
void copyPoly(Poly& dst, const Poly& src, int siz) {
    memcpy(data(dst), data(src), sizeof(int) * siz);
}
void invImpl(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = powm(sf[0], mod - 2);
    else {
        int h = n >> 1;
        invImpl(h, sf, g);

        Poly dftg(n);
        copyPoly(dftg, g, h);
        DFT(n, dftg);

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
}
void inv(int n, const Poly& sf, Poly& g) {
    int p = 1;
    while(p < n)
        p <<= 1;
    invImpl(p, sf, g);
    memset(data(g) + n, 0, sizeof(int) * (p - n));
}
Poly doMod(const Poly& A, const Poly& B) {
    if(A.size() < B.size())
        return A;
    if(A.size() < 100) {
        const Int64 fac = mod - 1;
        Poly res(A);
        for(int i = res.size() - 1; i >= B.size() - 1;
            --i)
            if(res[i]) {
                Int64 k = res[i] * fac % mod;
                for(int j = B.size() - 1, cp = i;
                    j >= 0; --j, --cp)
                    res[cp] =
                        (res[cp] + k * B[j]) % mod;
            }
        res.resize(B.size() - 1);
        return res;
    }
    int p = 1;
    while(p < 2 * A.size())
        p <<= 1;
    Poly AR(p);
    int siz = A.size() - B.size() + 1;
    std::reverse_copy(A.end() - siz, A.end(),
                      AR.begin());
    Poly BR(p);
    std::reverse_copy(
        B.end() -
            std::min(static_cast<int>(B.size()), siz),
        B.end(), BR.begin());
    Poly IBR(p);
    inv(siz, BR, IBR);

    DFT(p, AR);
    DFT(p, IBR);
    Poly C(p);
    for(int i = 0; i < p; ++i)
        C[i] = asInt64(AR[i]) * IBR[i] % mod;
    IDFT(p, C, 0, siz);
    std::reverse(C.begin(), C.begin() + siz);
    p >>= 1;

    Poly dftB(p);
    copyPoly(dftB, B, B.size());
    DFT(p, dftB);
    DFT(p, C);
    for(int i = 0; i < p; ++i)
        C[i] = asInt64(C[i]) * dftB[i] % mod;
    IDFT(p, C, 0, B.size() - 1, false);
    Poly res(B.size() - 1);
    for(int i = 0; i < res.size(); ++i)
        res[i] = sub(A[i], C[i]);
    return res;
}
const int size = 64005;
Poly A[size << 2];
void pre(int l, int r, int id) {
    if(l == r) {
        Poly& P = A[id];
        P.resize(2);
        int x = read();
        P[0] = (x ? mod - x : 0);
        P[1] = 1;
    } else {
        int m = (l + r) >> 1;
        pre(l, m, id << 1);
        pre(m + 1, r, id << 1 | 1);
        if(id == 1)
            return;
        int p = 1, siz = r - l + 1;
        while(p <= siz)
            p <<= 1;
        Poly& P = A[id];
        P.resize(siz + 1);
        Poly X(p), Y(p);
        copyPoly(X, A[id << 1], A[id << 1].size());
        copyPoly(Y, A[id << 1 | 1],
                 A[id << 1 | 1].size());
        DFT(p, X);
        DFT(p, Y);
        for(int i = 0; i < p; ++i)
            X[i] = asInt64(X[i]) * Y[i] % mod;
        IDFT(p, X, 0, siz + 1, false);
        copyPoly(P, X, siz + 1);
    }
}
int res[size];
void solve(int l, int r, int id, const Poly& X) {
    if(l == r)
        res[l] = X[0];
    else {
        int m = (l + r) >> 1;
        solve(l, m, id << 1, doMod(X, A[id << 1]));
        solve(m + 1, r, id << 1 | 1,
              doMod(X, A[id << 1 | 1]));
    }
}
int main() {
    int n = read();
    int m = read();
    Poly A(n + 1);
    for(int i = 0; i <= n; ++i)
        A[i] = read();
    pre(1, m, 1);
    solve(1, m, 1, A);
    for(int i = 1; i <= m; ++i)
        printf("%d\n", res[i]);
    return 0;
}
