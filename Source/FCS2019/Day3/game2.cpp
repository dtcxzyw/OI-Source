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
const int size = 100005, mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
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
int getSize(int n) {
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
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
int K;
Poly mul(const Poly& A, const Poly& B) {
    int end = A.size() + B.size() - 1;
    int p = getSize(end);
    Poly X(p);
    copyPoly(X, A, A.size());
    DFT(p, X);
    Poly Y(p);
    copyPoly(Y, B, B.size());
    DFT(p, Y);
    for(int i = 0; i < p; ++i)
        X[i] = asInt64(X[i]) * Y[i] % mod;
    end = std::min(end, K + 1);
    IDFT(p, X, 0, end, false);
    X.resize(end);
    return X;
}
Poly muls(int l, int r, const Poly& A) {
    if(l == r) {
        Poly B(2);
        B[0] = 1, B[1] = A[l];
        return B;
    } else {
        int m = (l + r) >> 1;
        return mul(muls(l, m, A), muls(m + 1, r, A));
    }
}
Poly muls(const Poly& A) {
    if(A.size())
        return muls(0, A.size() - 1, A);
    return Poly(1, 1);
}
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int msiz, crt, tot, siz[size];
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int csiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            csiz = std::max(siz[v], csiz);
        }
    }
    csiz = std::max(csiz, tot - siz[u]);
    if(csiz < msiz)
        crt = u, msiz = csiz;
}
int getRoot(int u, int usiz) {
    msiz = 1 << 30, tot = usiz;
    getRootImpl(u, 0);
    return crt;
}
int fac[size], invFac[size];
Int64 sa, sb, res = 0;
int DFS(int u, int p) {
    Poly tmp;
    int siz = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            int vsiz = DFS(v, u);
            siz += vsiz;
            tmp.push_back(vsiz);
        }
    }
    tmp = muls(tmp);
    for(int i = 0; i < tmp.size(); ++i)
        sb = (sb +
              fac[K] * invFac[K - i] % mod * tmp[i]) %
            mod;
    return siz;
}
void solve(int u) {
    sa = 0;
    Poly csiz, csb;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            sb = 0;
            int vsiz = DFS(v, u);
            res = (res + sa * sb) % mod;
            csiz.push_back(vsiz);
            csb.push_back(sb);
            sa = add(sa, sb);
        }
    }
    std::vector<Poly> P(csiz.size()), S(csiz.size());
    {
        Poly cur(1, 1);
        for(int i = 0; i < csiz.size(); ++i) {
            Poly base(2);
            base[0] = 1, base[1] = csiz[i];
            P[i] = cur;
            cur = mul(cur, base);
        }
    }
    {
        Poly cur(1, 1);
        for(int i = csiz.size() - 1; i >= 0; --i) {
            Poly base(2);
            base[0] = 1, base[1] = csiz[i];
            S[i] = cur;
            cur = mul(cur, base);
        }
    }
    for(int i = 0; i < csiz.size(); ++i) {
        Poly nsiz = mul(P[i], S[i]);
        Int64 cur = 0;
        for(int j = 0; j < nsiz.size(); ++j)
            cur = (cur +
                   fac[K] * invFac[K - j] % mod *
                       nsiz[j]) %
                mod;
        res = (res + cur * csb[i]) % mod;
    }
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            divide(nrt);
        }
    }
}
int main() {
    int n = read();
    K = read();
    int end = std::max(n, K);
    fac[0] = invFac[0] = 1;
    for(int i = 1; i <= end; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    invFac[1] = 1;
    for(int i = 2; i <= end; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 1; i <= end; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    divide(getRoot(1, n));
    printf("%lld\n", res);
    return 0;
}
