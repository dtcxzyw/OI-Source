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
int getOp() {
    int c;
    do
        c = getchar();
    while (c < '*' || c > '/');
    return c;
}
const int size = 100005;
typedef unsigned int U32;
const U32 mod = 51061;
U32 add(U32 a, U32 b) {
    a += b;
    return a < mod ? a : a - mod;
}
struct Node {
    U32 sum, val, k, b;
    int p, c[2], siz;
    bool rev;
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
void colorMul(int u, U32 v) {
    if (u) {
        T[u].sum = T[u].sum * v % mod;
        T[u].val = T[u].val * v % mod;
        T[u].k = T[u].k * v % mod;
        T[u].b = T[u].b * v % mod;
    }
}
void colorAdd(int u, U32 v) {
    if (u) {
        T[u].sum = (T[u].sum + v * T[u].siz) % mod;
        T[u].val = add(T[u].val, v);
        T[u].b = add(T[u].b, v);
    }
}
void pushDown(int u) {
    if (T[u].rev) {
        std::swap(ls, rs);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
    if (T[u].k != 1) {
        colorMul(ls, T[u].k);
        colorMul(rs, T[u].k);
        T[u].k = 1;
    }
    if (T[u].b) {
        colorAdd(ls, T[u].b);
        colorAdd(rs, T[u].b);
        T[u].b = 0;
    }
}
void update(int u) {
    T[u].siz = T[ls].siz + T[rs].siz + 1;
    T[u].sum = add(add(T[ls].sum, T[rs].sum), T[u].val);
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
void push(int u) {
    if (!isRoot(u)) push(T[u].p);
    pushDown(u);
}
void splay(int u) {
    push(u);
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
        rs = v;
        update(u);
        v = u;
        u = T[u].p;
    }
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
int main() {
    int n = read();
    int q = read();
    for (int i = 1; i <= n; ++i)
        T[i].sum = T[i].val = T[i].k = T[i].siz = 1;
    while (--n)
        link(read(), read());
    while (q--) {
        switch (getOp()) {
            case '+': {
                int u = read();
                int v = read();
                split(u, v);
                colorAdd(v, read());
                break;
            }
            case '-': {
                cut(read(), read());
                link(read(), read());
                break;
            }
            case '*': {
                int u = read();
                int v = read();
                split(u, v);
                colorMul(v, read());
                break;
            }
            case '/': {
                int u = read();
                int v = read();
                split(u, v);
                printf("%u\n", T[v].sum);
                break;
            }
        }
    }
    return 0;
}
