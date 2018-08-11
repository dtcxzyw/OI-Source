#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 100005;
struct Node {
    int maxi, val, p, c[2];
    bool rev;
} T[size + 1005];
int getPos(int u) {
    return u == T[T[u].p].c[1];
}
bool isRoot(int u) {
    int p = T[u].p;
    return T[p].c[0] != u && T[p].c[1] != u;
}
#define ls T[u].c[0]
#define rs T[u].c[1]
void pushDown(int u) {
    if (T[u].rev) {
        std::swap(ls, rs);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
int choose(int u, int v) {
    return T[u].val > T[v].val ? u : v;
}
void update(int u) {
    T[u].maxi = choose(choose(T[ls].maxi, T[rs].maxi), u);
}
void connect(int u, int p, int c) {
    T[u].p = p;
    T[p].c[c] = u;
}
void rotate(int u) {
    int ku = getPos(u);
    int p = T[u].p;
    int kp = getPos(p);
    int pp = T[p].p;
    int t = T[u].c[ku ^ 1];
    T[u].p = pp;
    if (!isRoot(p))
        connect(u, pp, kp);
    connect(t, p, ku);
    connect(p, u, ku ^ 1);
    update(p);
    update(u);
}
void push(int u) {
    if (!isRoot(u)) push(T[u].p);
    pushDown(u);
}
void splay(int u) {
    push(u);
    while (!isRoot(u)) {
        int p = T[u].p;
        if (!isRoot(p)) rotate((getPos(u) == getPos(p)) ? p : u);
        rotate(u);
    }
}
void access(int u) {
    int v = 0;
    while (u) {
        splay(u);
        rs = v;
        update(u);
        v = u;
        u = T[u].p;
    }
}
void makeRoot(int u) {
    access(u);
    splay(u);
    T[u].rev ^= 1;
    pushDown(u);
}
void link(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
    T[u].p = v;
}
void cut(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
    T[u].p = T[v].c[0] = 0;
    update(v);
}
int fa[1005];
int find(int u) {
    return fa[u] == u ? u : fa[u] = find(fa[u]);
}
int query(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
    return T[v].maxi;
}
struct Edge {
    int u, v, t;
    bool mark;
    bool operator<(const Edge &rhs) const {
        return u != rhs.u ? u < rhs.u : v < rhs.v;
    }
} E[size];
int getId(int u, int v, int m) {
    Edge e;
    e.u = u, e.v = v;
    return std::lower_bound(E, E + m, e) - E;
}
void tryAdd(int i, int off) {
    int id = off + i;
    int u = E[i].u, v = E[i].v;
    int fu = find(u), fv = find(v);
    if (fu == fv) {
        int e = query(u, v);
        if (T[e].val > E[i].t) {
            int eid = e - off;
            cut(e, E[eid].u);
            cut(e, E[eid].v);
        } else
            return;
    } else
        fa[fu] = fv;
    T[id].val = E[i].t;
    T[id].maxi = id;
    link(id, u);
    link(id, v);
}
struct Operator {
    int op, u, v;
} op[size];
int ans[size];
int main() {
    int n = read();
    int m = read();
    int q = read();
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 0; i < m; ++i) {
        E[i].u = read();
        E[i].v = read();
        if (E[i].u > E[i].v) std::swap(E[i].u, E[i].v);
        E[i].t = read();
        E[i].mark = false;
    }
    std::sort(E, E + m);
    for (int i = 0; i < q; ++i) {
        op[i].op = read();
        op[i].u = read();
        op[i].v = read();
        if (op[i].op == 2) {
            if (op[i].u > op[i].v) std::swap(op[i].u, op[i].v);
            E[getId(op[i].u, op[i].v, m)].mark = true;
        }
    }
    int off = n + 1;
    for (int i = 0; i < m; ++i)
        if (!E[i].mark)
            tryAdd(i, off);
    for (int i = q - 1; i >= 0; --i) {
        if (op[i].op == 1)
            ans[i] = T[query(op[i].u, op[i].v)].val;
        else
            tryAdd(getId(op[i].u, op[i].v, m), off);
    }
    for (int i = 0; i < q; ++i)
        if (op[i].op == 1)
            printf("%d\n", ans[i]);
    return 0;
}
