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
const int maxn = 50005, maxm = 100005;
struct Node {
    int c[2], p, mid, val;
    bool rev;
} T[maxn + maxm];
#define ls T[u].c[0]
#define rs T[u].c[1]
bool isRoot(int u) {
    int p = T[u].p;
    return T[p].c[0] != u && T[p].c[1] != u;
}
int getPos(int u) {
    int p = T[u].p;
    return u == T[p].c[1];
}
int choose(int u, int v) {
    return T[u].val > T[v].val ? u : v;
}
void update(int u) {
    T[u].mid = choose(u, choose(T[ls].mid, T[rs].mid));
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
    if(!isRoot(p))
        T[pp].c[kp] = u;
    connect(t, p, ku);
    connect(p, u, ku ^ 1);
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
            rotate(getPos(p) == getPos(u) ? p : u);
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
    makeRoot(u);
    T[u].p = v;
}
void cut(int u, int v) {
    split(u, v);
    T[u].p = T[v].c[0] = 0;
    update(v);
}
int fa[maxn];
int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}
struct Edge {
    int u, v, a, b;
    bool operator<(const Edge& rhs) const {
        return a == rhs.a ? b < rhs.b : a < rhs.a;
    }
} E[maxm];
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= m; ++i) {
        E[i].u = read();
        E[i].v = read();
        E[i].a = read();
        E[i].b = read();
        if(E[i].u == E[i].v)
            --i, --m;
    }
    std::sort(E + 1, E + m + 1);
    int res = 1 << 30;
    bool updated = false;
    for(int i = 1; i <= m; ++i) {
        if(E[i].a + E[i].b >= res) {
            if(E[i].a != E[i + 1].a && updated) {
                split(1, n);
                res = std::min(res, E[i].a +
                                   T[T[n].mid].val);
                updated = false;
            }
            continue;
        }
        int u = E[i].u, v = E[i].v, fu = find(u),
            fv = find(v);
        bool doLink = false;
        if(fu != fv) {
            doLink = true;
            fa[fu] = fv;
        } else {
            split(u, v);
            if(T[T[v].mid].val > E[i].b) {
                int old = T[v].mid, eid = old - n;
                cut(E[eid].u, old);
                cut(E[eid].v, old);
                doLink = true;
            }
        }
        if(doLink) {
            int id = n + i;
            T[id].mid = id, T[id].val = E[i].b;
            link(u, id);
            link(v, id);
            updated = true;
        }
        if(find(1) == find(n) &&
           E[i].a != E[i + 1].a && updated) {
            split(1, n);
            res = std::min(res,
                           E[i].a + T[T[n].mid].val);
            updated = false;
        }
    }
    if(res == 1 << 30)
        puts("-1");
    else
        printf("%d\n", res);
    return 0;
}
