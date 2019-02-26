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
struct Node {
    int p, c[2], rsiz, icnt;
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
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
void update(int u) {
    T[u].rsiz =
        T[ls].rsiz + T[rs].rsiz + 1 + T[u].icnt;
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
        if(rs)
            T[u].icnt += T[rs].rsiz;
        rs = v;
        if(rs)
            T[u].icnt -= T[rs].rsiz;
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
    T[v].icnt += T[u].rsiz;
    update(v);
}
int fa[size], rk[size], rt[size];
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
int DFSCmp(int u) {
    int tot = T[u].rsiz, half = tot / 2, lsiz = 0,
        rsiz = 0, crt = 1 << 30;
    while(u && lsiz <= half && rsiz <= half) {
        pushDown(u);
        int cl = lsiz + T[ls].rsiz,
            cr = rsiz + T[rs].rsiz;
        if(cl <= half && cr <= half) {
            if(tot & 1) {
                crt = u;
                break;
            } else
                crt = std::min(crt, u);
        }
        if(cl < cr) {
            lsiz += T[ls].rsiz + T[u].icnt + 1;
            u = rs;
        } else {
            rsiz += T[rs].rsiz + T[u].icnt + 1;
            u = ls;
        }
    }
    splay(crt);
    return crt;
}
int main() {
    int n = read();
    int m = read();
    int xorv = 0;
    for(int i = 1; i <= n; ++i) {
        T[i].rsiz = 1;
        rt[i] = i;
        xorv ^= i;
    }
    for(int i = 1; i <= m; ++i) {
        switch(getOp()) {
            case 'A': {
                int u = read();
                int v = read();
                int fu = find(u), fv = find(v);
                xorv ^= rt[fu] ^ rt[fv];
                link(u, v);
                split(rt[fu], rt[fv]);
                int cur = merge(fu, fv);
                rt[cur] = DFSCmp(rt[fv]);
                xorv ^= rt[cur];
            } break;
            case 'Q':
                printf("%d\n", rt[find(read())]);
                break;
            case 'X':
                printf("%d\n", xorv);
                break;
        }
    }
    return 0;
}
