#include <algorithm>
#include <cstdio>
#include <unordered_map>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 20005;
struct G {
    struct Edge {
        int to, nxt;
    } E[size * 2];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} g1, g2;
struct Base {
    Int64 b[64];
    void insert(Int64 x) {
        for(int i = 60; i >= 0; --i)
            if(x & (1LL << i)) {
                if(b[i])
                    x ^= b[i];
                else {
                    b[i] = x;
                    break;
                }
            }
    }
    Int64 maxv() const {
        Int64 res = 0;
        for(int i = 60; i >= 0; --i)
            res = std::max(res, res ^ b[i]);
        return res;
    }
};
Base merge(Base a, const Base& b) {
    for(int i = 60; i >= 0; --i)
        if(b.b[i])
            a.insert(b.b[i]);
    return a;
}
Base B[size * 16];
int bcnt = 0;
std::unordered_map<int, int> fap[size];
Int64 g[size];
bool vis[size];
int nrt, msiz, tsiz, siz[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int ssiz = 0;
    for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if(!vis[v] && v != p) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            ssiz = std::max(ssiz, siz[v]);
        }
    }
    ssiz = std::max(ssiz, tsiz - siz[u]);
    if(ssiz < msiz)
        msiz = ssiz, nrt = u;
}
int getRoot(int u, int siz) {
    msiz = 1 << 30, tsiz = siz;
    getRootImpl(u, 0);
    return nrt;
}
void DFS(int u, int rt, int p, const Base& base) {
    int id = ++bcnt;
    fap[u][rt] = id;
    B[id] = base;
    B[id].insert(g[u]);
    for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if(!vis[v] && v != p)
            DFS(v, rt, u, B[id]);
    }
}
void divide(int u) {
    vis[u] = true;
    DFS(u, u, 0, Base());
    for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if(!vis[v]) {
            int rt = getRoot(v, siz[v]);
            g2.addEdge(u, rt);
            divide(rt);
        }
    }
}
int d[size], L[size], A[16][size * 2], icnt = 0;
void scan(int u) {
    L[u] = ++icnt;
    A[0][icnt] = u;
    for(int i = g2.last[u]; i; i = g2.E[i].nxt) {
        int v = g2.E[i].to;
        d[v] = d[u] + 1;
        scan(v);
        A[0][++icnt] = u;
    }
}
int lg2[1024];
int choose(int a, int b) {
    return d[a] < d[b] ? a : b;
}
void initLCA(int rt) {
    for(int i = 2; i < 1024; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    scan(rt);
    for(int i = 1; i < 16; ++i) {
        int end = icnt - (1 << i) + 1, off = 1
            << (i - 1);
        for(int j = 1; j <= end; ++j)
            A[i][j] =
                choose(A[i - 1][j], A[i - 1][j + off]);
    }
}
int getLog(int x) {
    return x < 1024 ? lg2[x] : 10 + lg2[x >> 10];
}
int getLCA(int u, int v) {
    int l = L[u], r = L[v];
    if(l > r)
        std::swap(l, r);
    int p = getLog(r - l + 1);
    return choose(A[p][l], A[p][r - (1 << p) + 1]);
}
int main() {
    int n = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        g[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        g1.addEdge(u, v);
        g1.addEdge(v, u);
    }
    int rt = getRoot(1, n);
    divide(rt);
    initLCA(rt);
    for(int i = 0; i < q; ++i) {
        int u = read();
        int v = read();
        int lca = getLCA(u, v);
        Base &ud = B[fap[u][lca]],
             &vd = B[fap[v][lca]];
        Base ch = merge(ud, vd);
        printf("%lld\n", ch.maxv());
    }
    return 0;
}
