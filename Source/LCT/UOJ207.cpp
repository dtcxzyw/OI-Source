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
int genRandom() {
    static int seed = 562436;
    return seed = seed * 48271LL % 2147483647;
}
const int size = 100005;
struct Node {
    int c[2], p, xorv, ixor;
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
void connect(int u, int p, int c) {
    T[u].p = p;
    T[p].c[c] = u;
}
void update(int u) {
    T[u].xorv = T[u].ixor ^ T[ls].xorv ^ T[rs].xorv;
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
        T[u].ixor ^= T[rs].xorv ^ T[v].xorv;
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
    T[v].ixor ^= T[u].xorv;
    update(v);
}
void cut(int u, int v) {
    split(u, v);
    T[u].p = T[v].c[0] = 0;
    update(v);
}
void color(int u, int w) {
    access(u);
    splay(u);
    T[u].ixor ^= w;
    T[u].xorv ^= w;
}
struct Pair {
    int u, v, w;
} A[size * 3];
int main() {
    int id = read();
    int n = read();
    int m = read();
    for(int i = 1; i < n; ++i)
        link(read(), read());
    int pid = 0, sxor = 0;
    while(m--)
        switch(read()) {
            case 1: {
                cut(read(), read());
                link(read(), read());
            } break;
            case 2: {
                ++pid;
                A[pid].u = read();
                A[pid].v = read();
                A[pid].w = genRandom();
                color(A[pid].u, A[pid].w);
                color(A[pid].v, A[pid].w);
                sxor ^= A[pid].w;
            } break;
            case 3: {
                int id = read();
                color(A[id].u, A[id].w);
                color(A[id].v, A[id].w);
                sxor ^= A[id].w;
            } break;
            case 4: {
                int u = read();
                int v = read();
                split(u, v);
                puts(sxor == T[u].xorv ? "YES" : "NO");
            } break;
        }
    return 0;
}
