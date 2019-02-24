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
const int size = 70005;
typedef long long Int64;
struct Node {
    int p, c[2], maxp, w;
    bool rev;
} T[size];
#define ls T[u].c[0]
#define rs T[u].c[1]
bool isRoot(int u) {
    int p = T[u].p;
    return T[p].c[0] != u && T[p].c[1] != u;
}
int getPos(int u) {
    int p = T[u].p;
    return T[p].c[1] == u;
}
void connect(int u, int p, int c) {
    T[u].p = p;
    T[p].c[c] = u;
}
int choose(int u, int v) {
    return T[u].w > T[v].w ? u : v;
}
void update(int u) {
    T[u].maxp =
        choose(u, choose(T[ls].maxp, T[rs].maxp));
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
void pushDown(int u) {
    if(T[u].rev) {
        std::swap(ls, rs);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
void push(int u) {
    if(!isRoot(u))
        push(T[u].p);
    pushDown(u);
}
void splay(int u) {
    push(u);
    while(!isRoot(u)) {
        int p = T[u].p;
        if(!isRoot(p))
            rotate(getPos(u) == getPos(p) ? p : u);
        rotate(u);
    }
}
void access(int u) {
    int v = 0;
    do {
        splay(u);
        rs = v;
        update(u);
        v = u;
        u = T[u].p;
    } while(u);
}
void makeRoot(int u) {
    access(u);
    splay(u);
    T[u].rev ^= 1;
    pushDown(u);
}
void split(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
}
void link(int u, int v) {
    split(u, v);
    T[u].p = v;
}
void cut(int u, int v) {
    split(u, v);
    T[u].p = T[v].c[0] = 0;
    update(v);
}
struct Edge {
    int u, v, w;
    bool use;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
} E[size];
int fa[size], id[size];
int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}
bool cmp(int u, int v) {
    return E[u].w < E[v].w;
}
int main() {
    int n = read();
    int m = read();
    int q = read();
    for(int i = 1; i <= m; ++i) {
        E[i].u = read();
        E[i].v = read();
        E[i].w = read();
        id[i] = i;
        T[i + n].maxp = i + n;
        T[i + n].w = E[i].w;
    }
    std::sort(id + 1, id + m + 1, cmp);
    Int64 res = 0;
    for(int i = 1; i <= m; ++i) {
        int eid = id[i];
        Edge& e = E[eid];
        int fu = find(e.u), fv = find(e.v);
        if(fu != fv) {
            link(eid + n, e.u);
            link(eid + n, e.v);
            fa[fu] = fv;
            res += e.w;
        }
    }
    for(int i = 1; i <= q; ++i) {
    }
    return 0;
}
