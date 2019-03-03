#include <algorithm>
#include <cmath>
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
const int size = 100005;
typedef double FT;
struct Edge {
    int to, nxt, w;
    FT rw;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int crt, tsiz, msiz, siz[size];
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int csiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            csiz = std::max(csiz, siz[v]);
        }
    }
    csiz = std::max(csiz, tsiz - siz[u]);
    if(csiz < msiz)
        msiz = csiz, crt = u;
}
int getRoot(int u, int usiz) {
    msiz = 1 << 30, tsiz = usiz;
    getRootImpl(u, 0);
    return crt;
}
const FT inf = 1e20;
int L, U;
FT delta, A[size], B[size];
int maxlenA = 0, maxlenB = 0;
void updateAns(int len, FT res) {
    delta = std::max(delta, res / len);
}
void doClearA() {
    for(int i = 1; i <= maxlenA; ++i)
        A[i] = -inf;
    maxlenA = 0;
}
void doClearB() {
    for(int i = 1; i <= maxlenB; ++i)
        B[i] = -inf;
    maxlenB = 0;
}
void DFS(int u, int p, int len, FT w) {
    if(len >= L)
        updateAns(len, w);
    if(len < U) {
        A[len] = std::max(A[len], w);
        maxlenA = std::max(maxlenA, len);
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(v != p && !vis[v])
                DFS(v, u, len + 1, w + E[i].rw);
        }
    }
}
int q[size];
void dp() {
    int b = 1, e = 0, r = maxlenB;
    for(int i = 1; i <= maxlenA; ++i) {
        while(b <= e && q[b] > U - i)
            ++b;
        while(r >= std::max(L - i, 1)) {
            while(b <= e && B[q[e]] <= B[r])
                --e;
            q[++e] = r;
            --r;
        }
        if(b <= e)
            updateAns(i + q[b], A[i] + B[q[b]]);
    }
}
void solve(int u) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            DFS(v, u, 1, E[i].rw);
            dp();
            for(int j = 1; j <= maxlenA; ++j)
                B[j] = std::max(B[j], A[j]);
            maxlenB = std::max(maxlenB, maxlenA);
            doClearA();
        }
    }
    doClearB();
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
const int eps = 1e-6;
bool iter(int n, FT& val) {
    for(int i = 1; i <= cnt; ++i)
        E[i].rw = E[i].w - val;
    memset(vis + 1, 0, sizeof(bool) * n);
    delta = -inf;
    divide(getRoot(1, n));
    val += delta;
    return fabs(delta) > 1e-4;
}
int main() {
    int n = read();
    L = read();
    U = read();
    for(int i = 1; i < U; ++i)
        A[i] = B[i] = -inf;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    FT res = 6e5;
    while(iter(n, res))
        ;
    printf("%.3lf\n", res);
    return 0;
}
