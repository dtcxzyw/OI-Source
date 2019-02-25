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
int getOp() {
    int c;
    do
        c = getchar();
    while(c < 'A' || c > 'Z');
    return c;
}
const int size = 100005;
typedef long long Int64;
#define asInt64 static_cast<Int64>
struct Node {
    int p, c[2], siz, rsiz, icnt;
    Int64 lsum, rsum, isum;
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
void pushDown(int u) {
    if(T[u].rev) {
        std::swap(ls, rs);
        std::swap(T[u].lsum, T[u].rsum);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
void update(int u) {
    pushDown(ls);
    pushDown(rs);
    T[u].siz = T[ls].siz + T[rs].siz + 1;
    T[u].rsiz =
        T[ls].rsiz + T[rs].rsiz + 1 + T[u].icnt;
    T[u].lsum = T[u].isum + T[ls].lsum + T[rs].lsum +
        (T[ls].siz + 1) *
            asInt64(T[u].icnt + T[rs].rsiz) +
        T[ls].siz;
    T[u].rsum = T[u].isum + T[ls].rsum + T[rs].rsum +
        (T[rs].siz + 1) *
            asInt64(T[u].icnt + T[ls].rsiz) +
        T[rs].siz;
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
        if(rs) {
            pushDown(rs);
            T[u].icnt += T[rs].rsiz;
            T[u].isum += T[rs].lsum;
        }
        rs = v;
        if(rs) {
            T[u].icnt -= T[rs].rsiz;
            T[u].isum -= T[rs].lsum;
        }
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
void link(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
    T[u].p = v;
    T[v].icnt += T[u].rsiz;
    T[v].isum += T[u].lsum;
    update(v);
}
Int64 query(int u) {
    access(u);
    splay(u);
    return T[u].rsum;
}
struct G {
    struct Edge {
        int to, nxt;
    } E[size * 2];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} g1, g2;
int p[size], son[size], d[size];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if(v != p[u]) {
            d[v] = d[u] + 1;
            p[v] = u;
            int vsiz = buildTree(v);
            siz += vsiz;
            if(vsiz > msiz)
                son[u] = v, msiz = vsiz;
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
    for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
int lca(int u, int v) {
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]])
            std::swap(u, v);
        u = p[top[u]];
    }
    return d[u] < d[v] ? u : v;
}
int jump(int u, int lca) {
    int res = -1;
    while(top[u] != top[lca]) {
        res = top[u];
        u = p[top[u]];
    }
    return u == lca ? res : son[lca];
}
int nxt(int u, int v) {
    if(lca(u, v) == u)
        return jump(v, u);
    else
        return p[u];
}
int crt, nrt, dst;
void clear(int u) {
    T[u].p = ls = rs = T[u].icnt = T[u].isum =
        T[u].lsum = T[u].rsum = T[u].rev = 0;
    T[u].siz = T[u].rsiz = 1;
}
void DFSAdd(int u, int p) {
    clear(u);
    link(u, p);
    if(dst != -1) {
        Int64 vo = query(crt), vc = query(nrt);
        if(vo > vc || (vo == vc && nrt < crt)) {
            crt = nrt;
            if(crt == dst)
                dst = -1;
            else
                nrt = nxt(crt, dst);
        }
    }
    for(int i = g2.last[u]; i; i = g2.E[i].nxt) {
        int v = g2.E[i].to;
        if(v != p)
            DFSAdd(v, u);
    }
}
struct Op {
    int op, u, v;
} A[size * 2];
int fa[size], rk[size], siz[size], rt[size];
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
int merge(int u, int v) {
    if(rk[u] < rk[v]) {
        fa[u] = v;
        return v;
    } else {
        fa[v] = u;
        if(rk[u] == rk[v])
            ++rk[u];
        return u;
    }
}
int main() {
    int n = read();
    int m = read();
    int xorv = 0;
    for(int i = 1; i <= n; ++i) {
        clear(i);
        siz[i] = 1;
        rt[i] = i;
        xorv ^= i;
    }
    for(int i = 1; i <= m; ++i) {
        A[i].op = getOp();
        switch(A[i].op) {
            case 'A': {
                A[i].u = read();
                A[i].v = read();
                g1.addEdge(A[i].u, A[i].v);
                g1.addEdge(A[i].v, A[i].u);
            } break;
            case 'Q': {
                A[i].u = read();
            } break;
        }
    }
    for(int i = 1; i <= n; ++i) {
        if(!p[i]) {
            buildTree(i);
            top[i] = i;
            buildChain(i);
        }
    }
    for(int i = 1; i <= m; ++i) {
        switch(A[i].op) {
            case 'A': {
                int fu = find(A[i].u),
                    fv = find(A[i].v);
                xorv ^= rt[fu] ^ rt[fv];
                if(siz[fu] < siz[fv]) {
                    std::swap(A[i].u, A[i].v);
                    std::swap(fu, fv);
                }
                crt = rt[fu], nrt = nxt(crt, A[i].v),
                dst = A[i].v;
                g2.addEdge(A[i].u, A[i].v);
                g2.addEdge(A[i].v, A[i].u);
                DFSAdd(A[i].v, A[i].u);
                int cur = merge(fu, fv);
                siz[cur] = siz[fu] + siz[fv];
                rt[cur] = crt;
                xorv ^= crt;
            } break;
            case 'Q':
                printf("%d\n", rt[find(A[i].u)]);
                break;
            case 'X':
                printf("%d\n", xorv);
                break;
        }
    }
    return 0;
}
