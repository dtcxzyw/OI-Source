#include <algorithm>
#include <cstdio>
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
const int size = 100005;
struct BIT {
    std::vector<int> A;
    int n;
    void init(int siz) {
        A.resize(siz + 1);
        n = siz;
    }
    void modify(int x, int v) {
        while(x <= n) {
            A[x] += v;
            x += x & -x;
        }
    }
    int query(int x) {
        x = std::min(n, x);
        if(x <= 0)
            return 0;
        int res = 0;
        while(x) {
            res += A[x];
            x -= x & -x;
        }
        return res;
    }
} sumT[size], subT[size];
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int tsiz, msiz, crt, siz[size];
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
int getRoot(int u, int siz) {
    msiz = 1 << 30, tsiz = siz;
    getRootImpl(u, 0);
    return crt;
}
int w[size], tot;
struct Info {
    int k, u;
    Info() {}
    Info(int k, int u) : k(k), u(u) {}
    bool operator<(const Info& rhs) const {
        return k < rhs.k;
    }
} A[size];
void DFS(int u, int p, int k) {
    if(k)
        A[++tot] = Info(k, u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(p != v && !vis[v])
            DFS(v, u, k + 1);
    }
}
std::vector<std::pair<BIT*, int> > uq[size];
void solve(BIT& T, int u, int k) {
    tot = 0;
    DFS(u, 0, k);
    std::sort(A + 1, A + tot + 1);
    int siz = A[tot].k;
    A[tot + 1].k = -1;
    T.init(siz);
    for(int i = 1, csum = 0; i <= tot; ++i) {
        csum += w[A[i].u];
        uq[A[i].u].push_back(
            std::make_pair(&T, A[i].k));
        if(A[i].k != A[i + 1].k) {
            int p = A[i].k;
            T.A[p] += csum;
            int dst = p + (p & -p);
            if(dst <= siz)
                T.A[dst] += T.A[p];
            csum = 0;
        }
    }
}
int fa[size];
void divide(int u) {
    vis[u] = true;
    solve(sumT[u], u, 0);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            fa[nrt] = u;
            solve(subT[nrt], v, 1);
            divide(nrt);
        }
    }
}
int p[size], d[size], son[size];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u]) {
            p[v] = u;
            d[v] = d[u] + 1;
            int vsiz = buildTree(v);
            siz += vsiz;
            if(msiz < vsiz)
                msiz = vsiz, son[u] = v;
        }
    }
    return siz;
}
int top[size];
void buildChain(int u) {
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
int getLCA(int u, int v) {
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]])
            std::swap(u, v);
        u = p[top[u]];
    }
    return d[u] < d[v] ? u : v;
}
int dis(int u, int v) {
    return d[u] + d[v] - 2 * d[getLCA(u, v)];
}
int src, k;
int query(int x, int rk) {
    int res = rk >= 0 ? w[x] + sumT[x].query(rk) : 0;
    if(fa[x]) {
        int d = dis(fa[x], src);
        res += query(fa[x], k - d);
        res -= subT[x].query(k - d);
    }
    return res;
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i)
        w[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    divide(getRoot(1, n));
    int lastAns = 0;
    for(int t = 1; t <= m; ++t) {
        int op = read();
        int x = read() ^ lastAns;
        int y = read() ^ lastAns;
        if(op) {
            int delta = y - w[x];
            w[x] = y;
            for(int i = 0; i < uq[x].size(); ++i) {
                std::pair<BIT*, int> p = uq[x][i];
                p.first->modify(p.second, delta);
            }
        } else {
            src = x, k = y;
            printf("%d\n", lastAns = query(x, y));
        }
    }
    return 0;
}
