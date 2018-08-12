//TODO:4121
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
bool getState() {
    int c;
    do
        c = getchar();
    while (c != '0' && c != '1');
    return c == '1';
}
const int maxn = 205, size = maxn * maxn;
struct Node {
    int p, c[2];
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
    if (u == 0) throw;
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
void cut(int u, int v) {
    split(u, v);
    T[u].p = T[v].c[0] = 0;
    update(v);
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
bool map[size][size];
int n;
int getId(int i, int j) {
    return n * i + j;
}
void link(int x1, int y1, int x2, int y2, int &cntW, int &cntB) {
    if (map[x1][y1] == map[x2][y2]) {
        int idu = getId(x1, y1), idv = getId(x2, y2);
        makeRoot(idu);
        if (find(idv) != idu) {
            T[idu].p = idv;
            --(map[x1][y1] ? cntB : cntW);
        }
    }
}
int main() {
    n = read();
    int cntW, cntB = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            map[i][j] = getState();
            cntB += map[i][j];
        }
    cntW = n * n - cntB;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (i != n) link(i, j, i + 1, j, cntW, cntB);
            if (j != n) link(i, j, i, j + 1, cntW, cntB);
        }
    int m = read();
    while (m--) {
        int x = read();
        int y = read();
        map[x][y] ^= 1;
    }
    return 0;
}
