#include <algorithm>
#include <cstdio>
namespace IO {
    char in[1 << 23];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 23], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 200005;
namespace LCT {
    struct Node {
        int c[2], p, w, mid;
        bool rev;
    } T[size * 2];
    int choose(int a, int b) {
        return T[a].w < T[b].w ? a : b;
    }
#define ls T[u].c[0]
#define rs T[u].c[1]
    void update(int u) {
        T[u].mid =
            choose(u, choose(T[ls].mid, T[rs].mid));
    }
    bool isRoot(int u) {
        int p = T[u].p;
        return T[p].c[0] != u && T[p].c[1] != u;
    }
    int getPos(int u) {
        int p = T[u].p;
        return T[p].c[1] == u;
    }
    void connect(int u, int p, int c) {
        T[u].p = p, T[p].c[c] = u;
    }
    void rotate(int u) {
        int ku = getPos(u);
        int p = T[u].p;
        int t = T[u].c[ku ^ 1];
        int pp = T[p].p;
        T[u].p = pp;
        if(!isRoot(p))
            T[pp].c[getPos(p)] = u;
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
        split(u, v);
        T[u].p = v;
    }
    void cut(int u, int v) {
        split(u, v);
        T[u].p = T[v].c[0] = 0;
    }
#undef ls
#undef rs
}
struct Edge {
    int u, v;
} E[size];
int fa[size], rk[size];
int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}
void merge(int u, int v) {
    if(rk[u] < rk[v])
        fa[u] = v;
    else {
        fa[v] = u;
        if(rk[u] == rk[v])
            ++rk[u];
    }
}
struct Node {
    int l, r, siz;
} T[size * 40];
int tcnt = 0;
int modify(int l, int r, int src, int p, int op) {
    int id = ++tcnt;
    T[id] = T[src];
    T[id].siz += op;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = modify(l, m, T[id].l, p, op);
        else
            T[id].r = modify(m + 1, r, T[id].r, p, op);
    }
    return id;
}
int query(int l, int r, int id, int nl) {
    if(T[id].siz == 0)
        return 0;
    if(nl <= l)
        return T[id].siz;
    int m = (l + r) >> 1, res = 0;
    if(nl <= m)
        res += query(l, m, T[id].l, nl);
    res += query(m + 1, r, T[id].r, nl);
    return res;
}
int root[size];
int main() {
    IO::init();
    LCT::T[0].w = 1 << 30;
    int n = read();
    int m = read();
    int q = read();
    int t = read();
    for(int i = 1; i <= n; ++i) {
        LCT::T[i].w = 1 << 29;
        LCT::T[i].mid = i;
    }
    for(int i = 1; i <= m; ++i) {
        root[i] = root[i - 1];
        int u = read();
        int v = read();
        if(u == v)
            continue;
        E[i].u = u, E[i].v = v;
        int fu = find(u), fv = find(v);
        int id = i + n;
        LCT::T[id].w = LCT::T[id].mid = id;
        if(fu == fv) {
            LCT::split(u, v);
            int pid = LCT::T[v].mid;
            int eid = pid - n;
            LCT::cut(pid, E[eid].u);
            LCT::cut(pid, E[eid].v);
            root[i] = modify(1, m, root[i], eid, -1);
        } else
            merge(fu, fv);
        LCT::link(u, id);
        LCT::link(v, id);
        root[i] = modify(1, m, root[i], i, 1);
    }
    int lastAns = 0;
    for(int i = 1; i <= q; ++i) {
        int l = read() ^ lastAns;
        int r = read() ^ lastAns;
        int res = n - query(1, m, root[r], l);
        write(res);
        IO::putc('\n');
        if(t)
            lastAns = res;
    }
    IO::uninit();
    return 0;
}
