// FIXME
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
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
const int maxs = 1 << 18;
int root[maxs], invR[maxs];
void init() {
    Int64 base = powm(3, (mod - 1) / maxs);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for(int i = 1; i < maxs; ++i)
        root[i] = root[i - 1] * base % mod;
    for(int i = 1; i < maxs; ++i)
        invR[i] = invR[i - 1] * invBase % mod;
}
void NTT(int n, int* A, const int* w) {
    for(int i = 0, j = 0; i < n; ++i) {
        if(i < j)
            std::swap(A[i], A[j]);
        for(int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
    for(int i = 2; i <= n; i <<= 1) {
        int m = i >> 1, fac = maxs / i;
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + m + k];
                int t = asInt64(w[k * fac]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
int getSize(int n) {
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
}
int X[maxs], Y[maxs];
Poly mul(const Poly& A, const Poly& B) {
    int end = A.size() + B.size() - 1;
    int p = getSize(end);
    memcpy(X, A.data(), sizeof(int) * A.size());
    memset(X + A.size(), 0,
           sizeof(int) * (p - A.size()));
    NTT(p, X, root);
    memcpy(Y, B.data(), sizeof(int) * B.size());
    memset(Y + B.size(), 0,
           sizeof(int) * (p - B.size()));
    NTT(p, Y, root);
    for(int i = 0; i < p; ++i)
        X[i] = asInt64(X[i]) * Y[i] % mod;
    NTT(p, X, invR);
    Int64 div = powm(p, mod - 2);
    Poly res(end);
    for(int i = 0; i < end; ++i)
        res[i] = X[i] * div % mod;
    return res;
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
int fac[size], invFac[size], n, K;
Int64 divL(Poly F, Int64 k) {
    Int64 dpv = 0;
    for(int i = 0; i < F.size() && i <= K; ++i) {
        dpv = (dpv + asInt64(invFac[K - i]) * F[i]) %
            mod;
        if(i + 1 < F.size())
            F[i + 1] = (F[i + 1] - F[i] * k) % mod;
    }
    if(dpv < 0)
        dpv += mod;
    return dpv * asInt64(fac[K]) % mod;
}
Int64 ans = 0;
int siz[size], S[size];
void DFS(int u, int p) {
    siz[u] = 1;
    Poly F;
    std::map<int, int> SS;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            DFS(v, u);
            siz[u] += siz[v];
            F.push_back(siz[v]);
            ans = (ans + asInt64(S[u]) * S[v]) % mod;
            S[u] = add(S[u], S[v]);
            int& val = SS[siz[v]];
            val = add(val, S[v]);
        }
    }
    F.push_back(n - siz[u]);
    F = muls(F);
    S[u] = add(S[u], divL(F, n - siz[u]));
    for(std::map<int, int>::iterator it = SS.begin();
        it != SS.end(); ++it)
        ans = (ans + divL(F, it->first) * it->second) %
            mod;
}
int main() {
    n = read();
    K = read();
    init();
    fac[0] = invFac[0] = 1;
    for(int i = 1; i <= K; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    invFac[1] = 1;
    for(int i = 2; i <= K; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 1; i <= K; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    DFS(1, 0);
    printf("%lld\n", ans);
    return 0;
}
