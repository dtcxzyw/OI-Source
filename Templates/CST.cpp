// CF487E
#include <algorithm>
#include <cstdio>
#include <set>
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
int getOp() {
    int c;
    do
        c = getchar();
    while(c != 'A' && c != 'C');
    return c;
}
template <int maxv>
struct G {
    struct Edge {
        int to, nxt;
    } E[maxv * 2];
    int last[maxv], cnt;
    G() : cnt(0) {}
    void addEdgeImpl(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
    void addEdge(int u, int v) {
        addEdgeImpl(u, v);
        addEdgeImpl(v, u);
    }
};
const int size = 100005, tsiz = size * 2;
G<size> g1;
G<tsiz> g2;
int dfn[size], low[size], st[size], timeStamp = 0, sttop = 0, nsiz;
void tarjan(int u) {
    dfn[u] = low[u] = ++timeStamp;
    st[++sttop] = u;
    for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if(dfn[v])
            low[u] = std::min(low[u], dfn[v]);
        else {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
            if(dfn[u] <= low[v]) {
                int s = ++nsiz, p;
                g2.addEdge(s, u);
                do {
                    p = st[sttop--];
                    g2.addEdge(s, p);
                } while(p != v);
            }
        }
    }
}
int siz[tsiz], son[tsiz], d[tsiz], p[tsiz];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = g2.last[u]; i; i = g2.E[i].nxt) {
        int v = g2.E[i].to;
        if(v != p[u]) {
            p[v] = u;
            d[v] = d[u] + 1;
            buildTree(v);
            siz[u] += siz[v];
            if(siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}
int top[tsiz], id[tsiz], icnt, map[tsiz];
void buildChain(int u) {
    id[u] = ++icnt;
    map[icnt] = u;
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = g2.last[u]; i; i = g2.E[i].nxt) {
        int v = g2.E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
int minw[tsiz << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void modify(int l, int r, int id, int p, int val) {
    if(l == r)
        minw[id] = val;
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            modify(ls, p, val);
        else
            modify(rs, p, val);
        minw[id] = std::min(minw[id << 1], minw[id << 1 | 1]);
    }
}
int qres;
void query(int l, int r, int id, int nl, int nr) {
    if(minw[id] >= qres)
        return;
    if(nl <= l && r <= nr)
        qres = minw[id];
    else {
        int m = (l + r) >> 1, res = 0;
        if(nl <= m)
            query(ls, nl, nr);
        if(m < nr)
            query(rs, nl, nr);
    }
}
int A[tsiz];
void build(int l, int r, int id) {
    if(l == r)
        minw[id] = A[map[l]];
    else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        minw[id] = std::min(minw[id << 1], minw[id << 1 | 1]);
    }
}
std::multiset<int> B[tsiz];
int n;
void modify(int u, int v) {
    int pu = p[u];
    if(pu > n) {
        int old = *B[pu].begin();
        B[pu].erase(B[pu].find(A[u]));
        B[pu].insert(v);
        int now = *B[pu].begin();
        if(now != old)
            modify(1, nsiz, 1, id[pu], now);
    }
    A[u] = v;
    modify(1, nsiz, 1, id[u], v);
}
int query(int u, int v) {
    qres = 1 << 30;
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]])
            std::swap(u, v);
        query(1, nsiz, 1, id[top[u]], id[u]);
        u = p[top[u]];
    }
    if(d[u] > d[v])
        std::swap(u, v);
    query(1, nsiz, 1, id[u], id[v]);
    if(u > n)
        qres = std::min(qres, A[p[u]]);
    return qres;
}
int main() {
    n = read();
    nsiz = n;
    int m = read();
    int q = read();
    A[0] = 1 << 30;
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    while(m--) {
        int u = read();
        int v = read();
        g1.addEdge(u, v);
    }
    tarjan(1);
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    for(int i = 1; i <= n; ++i)
        if(p[i] > n)
            B[p[i]].insert(A[i]);
    for(int i = n + 1; i <= nsiz; ++i)
        A[i] = *B[i].begin();
    build(1, nsiz, 1);
    while(q--) {
        int op = getOp();
        int u = read();
        int v = read();
        if(op == 'C')
            modify(u, v);
        else
            printf("%d\n", query(u, v));
    }
    return 0;
}
