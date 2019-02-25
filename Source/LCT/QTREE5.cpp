#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
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
const int size = 100005, inf = 1 << 25;
struct RemoveableHeap {
    std::priority_queue<int, std::vector<int>,
                        std::greater<int> >
        A, B;
    void push(int x) {
        A.push(x);
    }
    void pop(int x) {
        B.push(x);
    }
    int top() {
        while(A.size() && B.size() &&
              A.top() == B.top())
            A.pop(), B.pop();
        return A.size() ? A.top() : inf;
    }
};
struct Node {
    RemoveableHeap ilen;
    Node *p, *c[2];
    int llen, rlen, siz;
    bool rev, col;
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
        std::swap(u->llen, u->rlen);
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
    u->siz =
        1 + (ls ? ls->siz : 0) + (rs ? rs->siz : 0);
    u->llen = std::min(
        (ls ? ls->llen : inf), (ls ? ls->siz : 0) +
            (u->col ?
                 0 :
                 1 + std::min((rs ? rs->llen : inf),
                              u->ilen.top())));
    u->rlen = std::min(
        (rs ? rs->rlen : inf), (rs ? rs->siz : 0) +
            (u->col ?
                 0 :
                 1 + std::min((ls ? ls->rlen : inf),
                              u->ilen.top())));
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
            u->ilen.push(rs->llen);
        }
        rs = v;
        if(rs)
            u->ilen.pop(rs->llen);
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
    v->ilen.push(u->llen);
    update(v);
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        T[i].llen = T[i].rlen = inf;
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
            int res = T[u].rlen;
            printf("%d\n", res >= inf ? -1 : res);
        } else {
            T[u].col ^= 1;
            update(T + u);
        }
    }
    return 0;
}
