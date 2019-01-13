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
    while(c != 'A' && c != 'Q');
    return c;
}
const int size = 100005;
struct Node {
    int c[2], p, siz, isiz;
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
    return u == T[p].c[1];
}
void update(int u) {
    T[u].siz = T[u].isiz + 1 + T[ls].siz + T[rs].siz;
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
            rotate(getPos(u) == getPos(p) ? p : u);
        rotate(u);
    }
}
void access(int u) {
    int v = 0;
    do {
        splay(u);
        T[u].isiz += T[rs].siz - T[v].siz;
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
void link(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
    T[u].p = v;
    T[v].isiz += T[u].siz;
    update(v);
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        T[i].siz = 1;
    int q = read();
    while(q--) {
        int op = getOp();
        int u = read();
        int v = read();
        if(op == 'A')
            link(u, v);
        else {
            makeRoot(u);
            access(v);
            splay(v);
            long long su = T[u].siz,
                      sv = T[v].siz - su;
            printf("%lld\n", su * sv);
        }
    }
    return 0;
}
