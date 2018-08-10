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
const int size = 300005;
struct Node {
    int sum, val, p, c[2];
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
void pushDown(int u) {
    if (T[u].rev) {
        std::swap(ls, rs);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
void update(int u) {
    T[u].sum = T[ls].sum ^ T[rs].sum ^ T[u].val;
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
int find(int u) {
    access(u);
    splay(u);
    pushDown(u);
    while (ls) {
        u = ls;
        pushDown(u);
    }
    return u;
}
void link(int u, int v) {
    makeRoot(u);
    if (find(v) != u)
        T[u].p = v;
}
void cut(int u, int v) {
    makeRoot(u);
    if (find(v) == u && T[u].p == v && T[v].c[0] == u && T[u].c[1] == 0) {
        T[u].p = T[v].c[0] = 0;
        update(v);
    }
}
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i <= n; ++i)
        T[i].sum = T[i].val = read();
    while (m--) {
        int op = read();
        int u = read();
        int v = read();
        switch (op) {
            case 0: {
                makeRoot(u);
                access(v);
                splay(v);
                printf("%d\n", T[v].sum);
                break;
            }
            case 1: {
                link(u, v);
                break;
            }
            case 2: {
                cut(u, v);
                break;
            }
            case 3: {
                splay(u);
                T[u].val = v;
                break;
            }
        }
    }
    return 0;
}
