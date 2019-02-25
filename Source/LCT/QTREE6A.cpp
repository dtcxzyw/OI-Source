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
struct Node {
    Node *p, *c[2];
    int lcnt, rcnt, mixc, icnt[2];
    bool rev, col, lcol, rcol;
} T[size];
typedef Node* Ptr;
#define ls (u->c[0])
#define rs (u->c[1])
bool isRoot(Ptr u) {
    Ptr p = u->p;
    return !p || (p->c[0] != u && p->c[1] != u);
}
int getPos(Ptr u) {
    Ptr p = u->p;
    return p->c[1] == u;
}
void connect(Ptr u, Ptr p, int c) {
    if(u)
        u->p = p;
    p->c[c] = u;
}
void pushDown(Ptr u) {
    if(u->rev) {
        std::swap(u->lcnt, u->rcnt);
        std::swap(u->lcol, u->rcol);
        std::swap(ls, rs);
        if(ls)
            ls->rev ^= 1;
        if(rs)
            rs->rev ^= 1;
        u->rev = false;
    }
}
void update(Ptr u) {
    if(ls)
        pushDown(ls);
    if(rs)
        pushDown(rs);
    u->lcol = (ls ? ls->lcol : u->col);
    u->rcol = (rs ? rs->rcol : u->col);
    u->mixc = u->col;
    if(ls && (ls->mixc != u->col))
        u->mixc = 2;
    if(rs && (rs->mixc != u->col))
        u->mixc = 2;
    u->lcnt = (ls ? ls->lcnt : 0) +
        ((ls ? ls->mixc == u->col : true) ?
             1 + u->icnt[u->col] +
                 (rs && rs->lcol == u->col ? rs->lcnt :
                                             0) :
             0);
    u->rcnt = (rs ? rs->rcnt : 0) +
        ((rs ? rs->mixc == u->col : true) ?
             1 + u->icnt[u->col] +
                 (ls && ls->rcol == u->col ? ls->rcnt :
                                             0) :
             0);
}
void rotate(Ptr u) {
    int ku = getPos(u);
    Ptr p = u->p;
    Ptr pp = p->p;
    Ptr t = u->c[ku ^ 1];
    u->p = pp;
    if(!isRoot(p))
        pp->c[getPos(p)] = u;
    connect(p, u, ku ^ 1);
    connect(t, p, ku);
    update(p);
    update(u);
}
void push(Ptr u) {
    if(!isRoot(u))
        push(u->p);
    pushDown(u);
}
void splay(Ptr u) {
    push(u);
    while(!isRoot(u)) {
        Ptr p = u->p;
        if(!isRoot(p))
            rotate(getPos(p) == getPos(u) ? p : u);
        rotate(u);
    }
}
void access(Ptr u) {
    Ptr v = 0;
    do {
        splay(u);
        if(rs) {
            pushDown(rs);
            u->icnt[rs->lcol] += rs->lcnt;
        }
        rs = v;
        if(rs)
            u->icnt[rs->lcol] -= rs->lcnt;
        update(u);
        v = u;
        u = u->p;
    } while(u);
}
void makeRoot(Ptr u) {
    access(u);
    splay(u);
    u->rev ^= 1;
    pushDown(u);
}
void link(Ptr u, Ptr v) {
    makeRoot(u);
    access(v);
    splay(v);
    u->p = v;
    v->icnt[u->lcol] += u->lcnt;
    update(v);
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        T[i].lcnt = T[i].rcnt = 1;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        link(T + u, T + v);
    }
    int q = read();
    for(int i = 0; i < q; ++i) {
        int op = read();
        int u = read();
        access(T + u);
        splay(T + u);
        if(op) {
            T[u].col ^= 1;
            update(T + u);
        } else {
            int res = T[u].rcnt;
            printf("%d\n", res);
        }
    }
    return 0;
}
