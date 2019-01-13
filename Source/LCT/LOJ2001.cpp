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
const int size = 100005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int p[size], d[size], siz[size], son[size];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
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
int id[size], idd[size], top[size], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
    idd[icnt] = d[u];
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!id[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
int getLCA(int u, int v) {
    while(top[u] != top[v]) {
        int& w = d[top[u]] > d[top[v]] ? u : v;
        w = p[top[w]];
    }
    return d[u] < d[v] ? u : v;
}
int maxv[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void build(int l, int r, int id) {
    if(l == r)
        maxv[id] = idd[l];
    else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        maxv[id] =
            std::max(maxv[id << 1], maxv[id << 1 | 1]);
    }
}
int nl, nr, val;
void modify(int l, int r, int id) {
    if(nl <= l && r <= nr)
        maxv[id] += val;
    else {
        int m = (l + r) >> 1, off = maxv[id] -
            std::max(maxv[id << 1], maxv[id << 1 | 1]);
        if(nl <= m)
            modify(ls);
        if(m < nr)
            modify(rs);
        maxv[id] = off +
            std::max(maxv[id << 1], maxv[id << 1 | 1]);
    }
}
int query(int l, int r, int id) {
    if(nl <= l && r <= nr)
        return maxv[id];
    else {
        int m = (l + r) >> 1, res = 0;
        if(nl <= m)
            res = std::max(res, query(ls));
        if(m < nr)
            res = std::max(res, query(rs));
        int off = maxv[id] -
            std::max(maxv[id << 1], maxv[id << 1 | 1]);
        return res + off;
    }
}
int n;
int queryPoint(int u) {
    nl = nr = id[u];
    return query(1, n, 1);
}
struct Node {
    int c[2], p, rt;
} T[size];
bool isRoot(int u) {
    int p = T[u].p;
    return T[p].c[0] != u && T[p].c[1] != u;
}
int getPos(int u) {
    int p = T[u].p;
    return u == T[p].c[1];
}
void connect(int u, int p, int c) {
    T[u].p = p;
    T[p].c[c] = u;
}
void update(int u) {
    T[u].rt = (T[u].c[0] ? T[T[u].c[0]].rt : u);
}
void rotate(int u) {
    int ku = getPos(u);
    int p = T[u].p;
    int kp = getPos(p);
    int pp = T[p].p;
    int t = T[u].c[ku ^ 1];
    T[u].p = pp;
    if(!isRoot(p))
        T[pp].c[kp] = u;
    connect(p, u, ku ^ 1);
    connect(t, p, ku);
    update(p);
    update(u);
}
void splay(int u) {
    while(!isRoot(u)) {
        int p = T[u].p;
        if(!isRoot(p))
            rotate(getPos(p) == getPos(u) ? p : u);
        rotate(u);
    }
}
void updateLink(int u, int op) {
    u = T[u].rt;
    if(u) {
        nl = id[u], nr = id[u] + siz[u] - 1, val = op;
        modify(1, n, 1);
    }
}
void access(int u) {
    int v = 0;
    do {
        splay(u);
        updateLink(T[u].c[1], 1);
        T[u].c[1] = v;
        updateLink(v, -1);
        v = u;
        u = T[u].p;
    } while(u);
}
int main() {
    n = read();
    int m = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    d[1] = 1;
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    for(int i = 1; i <= n; ++i)
        T[i].p = p[i], T[i].rt = i;
    build(1, n, 1);
    while(m--)
        switch(read()) {
            case 1:
                access(read());
                break;
            case 2: {
                int u = read();
                int v = read();
                int lca = getLCA(u, v);
                printf("%d\n", queryPoint(u) +
                           queryPoint(v) -
                           queryPoint(lca) * 2 + 1);
            } break;
            case 3: {
                int u = read();
                nl = id[u], nr = id[u] + siz[u] - 1;
                printf("%d\n", query(1, n, 1));
            } break;
        }
    return 0;
}
