#include <algorithm>
#include <cstdio>
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
const int size = 100005, maxz = 100000;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int p[size][17], d[size];
void DFSA(int u) {
    for(int i = 1; i < 17; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u][0]) {
            p[v][0] = u;
            d[v] = d[u] + 1;
            DFSA(v);
        }
    }
}
int getLCA(int u, int v) {
    if(d[u] < d[v])
        std::swap(u, v);
    int delta = d[u] - d[v];
    for(int i = 0; i < 17; ++i)
        if(delta & (1 << i))
            u = p[u][i];
    if(u == v)
        return u;
    for(int i = 16; i >= 0; --i)
        if(p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    return p[u][0];
}
struct Seg {
    int val, l, r;
} T[size * 80];
int icnt = 0;
void update(int id) {
    int lp = T[id].l;
    int rp = T[id].r;
    T[id].val = std::max(T[lp].val, T[rp].val);
}
void modify(int l, int r, int& id, int p, int op) {
    if(!id)
        id = ++icnt;
    if(l == r)
        T[id].val += op;
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            modify(l, m, T[id].l, p, op);
        else
            modify(m + 1, r, T[id].r, p, op);
        update(id);
    }
}
int query(int l, int r, int id) {
    if(l == r)
        return l;
    else {
        int m = (l + r) >> 1;
        int lp = T[id].l, rp = T[id].r;
        if(T[lp].val >= T[rp].val)
            return query(l, m, lp);
        else
            return query(m + 1, r, rp);
    }
}
int merge(int u, int v) {
    if(u && v) {
        if(T[u].l || T[u].r) {
            T[u].l = merge(T[u].l, T[v].l);
            T[u].r = merge(T[u].r, T[v].r);
            update(u);
        } else
            T[u].val += T[v].val;
        return u;
    }
    return u | v;
}
int root[size], res[size];
void DFSB(int u) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u][0]) {
            DFSB(v);
            root[u] = merge(root[u], root[v]);
        }
    }
    if(root[u] && T[root[u]].val)
        res[u] = query(1, maxz, root[u]);
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    DFSA(1);
    T[0].val = -1;
    while(m--) {
        int u = read();
        int v = read();
        int c = read();
        int lca = getLCA(u, v);
        modify(1, maxz, root[u], c, 1);
        modify(1, maxz, root[v], c, 1);
        modify(1, maxz, root[lca], c, -1);
        if(lca != 1)
            modify(1, maxz, root[p[lca][0]], c, -1);
    }
    DFSB(1);
    for(int i = 1; i <= n; ++i)
        printf("%d\n", res[i]);
    return 0;
}
