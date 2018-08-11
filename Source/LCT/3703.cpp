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
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int L[size], R[size], icnt = 0, d[size], pid[size], p[size][17];
void DFS(int u) {
    L[u] = ++icnt;
    pid[icnt] = u;
    for (int i = 1; i < 17; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if (v != p[u][0]) {
            d[v] = d[u] + 1;
            p[v][0] = u;
            DFS(v);
        }
    }
    R[u] = icnt;
}
int lca(int u, int v) {
    if (d[u] < d[v]) std::swap(u, v);
    int delta = d[u] - d[v];
    for (int i = 0; i < 17; ++i)
        if (delta & (1 << i))
            u = p[u][i];
    if (u == v) return u;
    for (int i = 16; i >= 0; --i)
        if (p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    return p[u][0];
}
namespace Seg {
    struct Node {
        int off, maxv;
    } T[size << 2];
    void color(int id, int val) {
        T[id].off += val;
        T[id].maxv += val;
    }
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
    void update(int id) {
        T[id].maxv = std::max(T[id << 1].maxv, T[id << 1 | 1].maxv);
    }
    void build(int l, int r, int id) {
        if (l == r)
            T[id].maxv = d[pid[l]];
        else {
            int m = (l + r) >> 1;
            build(ls);
            build(rs);
            update(id);
        }
    }
    void push(int id) {
        if (T[id].off) {
            color(id << 1, T[id].off);
            color(id << 1 | 1, T[id].off);
            T[id].off = 0;
        }
    }
    void modify(int l, int r, int id, int nl, int nr, int val) {
        if (nl <= l && r <= nr)
            color(id, val);
        else {
            push(id);
            int m = (l + r) >> 1;
            if (nl <= m) modify(ls, nl, nr, val);
            if (m < nr) modify(rs, nl, nr, val);
            update(id);
        }
    }
    int query(int l, int r, int id, int nl, int nr) {
        if (nl <= l && r <= nr)
            return T[id].maxv;
        else {
            push(id);
            int m = (l + r) >> 1, res = 0;
            if (nl <= m) res = std::max(res, query(ls, nl, nr));
            if (m < nr) res = std::max(res, query(rs, nl, nr));
            return res;
        }
    }
#undef ls
#undef rs
}
namespace LCT {
    struct Node {
        int rt, p, c[2];
    } T[size];
    int getPos(int u) {
        return u == T[T[u].p].c[1];
    }
    bool isRoot(int u) {
        int p = T[u].p;
        return T[p].c[0] != u && T[p].c[1] != u;
    }
#define ls T[u].c[0]
#define rs T[u].c[1]
    void update(int u) {
        T[u].rt = (ls ? T[ls].rt : u);
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
    void splay(int u) {
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
            if (rs) {
                int rt = T[rs].rt;
                Seg::modify(1, icnt, 1, L[rt], R[rt], 1);
            }
            rs = v;
            if (v) {
                int rt = T[v].rt;
                Seg::modify(1, icnt, 1, L[rt], R[rt], -1);
            }
            update(u);
            v = u;
            u = T[u].p;
        }
    }
    void build(int n) {
        for (int i = 1; i <= n; ++i) {
            T[i].rt = i;
            T[i].p = p[i][0];
        }
    }
    int jump(int u) {
        int res = 0;
        while (u) {
            splay(u);
            u = T[u].p;
            ++res;
        }
        return res;
    }
#undef ls
#undef rs
}
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    d[1] = 1;
    DFS(1);
    Seg::build(1, n, 1);
    LCT::build(n);
    while (m--) {
        int op = read();
        int u = read();
        switch (op) {
            case 1: {
                LCT::access(u);
                break;
            }
            case 2: {
                int v = read();
                int w = lca(u, v);
                printf("%d\n", LCT::jump(u) + LCT::jump(v) - 2 * LCT::jump(w) + 1);
                break;
            }
            case 3: {
                printf("%d\n", Seg::query(1, n, 1, L[u], R[u]));
                break;
            }
        }
    }
    return 0;
}
