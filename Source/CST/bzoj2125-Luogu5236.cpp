#include <algorithm>
#include <cstdio>
typedef long long Int64;
Int64 iabs(Int64 x) {
    return x >= 0 ? x : -x;
}
const int size = 10005, maxv = 2 * size;
struct G {
    struct Edge {
        int to, nxt;
        Int64 w;
    } E[size * 4];
    int last[maxv], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v, Int64 w) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u],
        E[cnt].w = w;
        last[u] = cnt;
    }
} A, B;
int dfn[size], fa[size], pd[size], icnt = 0, ncnt;
Int64 dis[size], mdis[maxv];
bool ring[size];
void DFS(int u) {
    dfn[u] = ++icnt;
    for(int i = A.last[u]; i; i = A.E[i].nxt) {
        int v = A.E[i].to;
        if(v == fa[u])
            continue;
        if(dfn[v]) {
            if(dfn[v] < dfn[u]) {
                int id = ++ncnt, rcnt = 0;
                dis[0] = A.E[i].w;
                for(int j = u; j != v; j = fa[j]) {
                    ++rcnt;
                    dis[rcnt] = dis[rcnt - 1] + pd[j];
                }
                Int64 sum = dis[rcnt];
                rcnt = 0;
                for(int j = u; j != v; j = fa[j]) {
                    Int64 rd = sum - dis[rcnt];
                    mdis[j] = dis[rcnt];
                    B.addEdge(id, j,
                              std::min(rd, dis[rcnt])),
                        ring[j] = true;
                    ++rcnt;
                }
                mdis[id] = sum;
                B.addEdge(v, id, 0), ring[v] = true;
            }
        } else {
            fa[v] = u;
            pd[v] = A.E[i].w;
            ring[u] = false;
            DFS(v);
            if(!ring[u])
                B.addEdge(u, v, A.E[i].w);
        }
    }
}
int son[maxv], p[maxv], d[maxv];
Int64 len[maxv];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        p[v] = u;
        d[v] = d[u] + 1;
        len[v] = len[u] + B.E[i].w;
        int vsiz = buildTree(v);
        siz += vsiz;
        if(vsiz > msiz)
            msiz = vsiz, son[u] = v;
    }
    return siz;
}
int top[maxv];
void buildChain(int u) {
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
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
int jump(int u, int lca) {
    int res;
    while(top[u] != top[lca]) {
        res = top[u];
        u = p[top[u]];
    }
    return u == lca ? res : son[lca];
}
int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        A.addEdge(u, v, w);
        A.addEdge(v, u, w);
    }
    ncnt = n;
    DFS(1);
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    for(int i = 1; i <= q; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        int lca = getLCA(u, v);
        Int64 res;
        if(lca <= n)
            res = len[u] + len[v] - 2 * len[lca];
        else {
            int pu = jump(u, lca), pv = jump(v, lca);
            res = len[u] - len[pu] + len[v] - len[pv];
            Int64 delta = iabs(mdis[pu] - mdis[pv]);
            res += std::min(delta, mdis[lca] - delta);
        }
        printf("%lld\n", res);
    }
    return 0;
}
