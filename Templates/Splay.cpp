// P2234
#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 35000;
struct Node {
    int c[2], p, val;
} T[size];
int newNode(int val) {
    static int cnt = 0;
    int id = ++cnt;
    T[id].val = val;
    return id;
}
int getPos(int u) {
    int p = T[u].p;
    return T[p].c[1] == u;
}
void connect(int u, int p, int c) {
    T[u].p = p;
    T[p].c[c] = u;
}
void rotate(int u) {
    int p = T[u].p;
    int ku = getPos(u);
    int pp = T[p].p;
    int kp = getPos(p);
    int t = T[u].c[ku ^ 1];
    connect(u, pp, kp);
    connect(p, u, ku ^ 1);
    connect(t, p, ku);
}
void splay(int u) {
    while(T[u].p) {
        int p = T[u].p;
        if(T[p].p)
            rotate(getPos(p) == getPos(u) ? p : u);
        rotate(u);
    }
}
bool insert(int& u, int p, int val) {
    if(u) {
        if(T[u].val != val)
            return insert(T[u].c[T[u].val < val], u,
                          val);
    } else {
        u = newNode(val);
        T[u].p = p;
        splay(u);
        return true;
    }
    splay(u);
    return false;
}
const int inf = 1 << 25;
int pre(int u) {
    u = T[u].c[0];
    if(u == 0)
        return -inf;
    while(T[u].c[1])
        u = T[u].c[1];
    return T[u].val;
}
int nxt(int u) {
    u = T[u].c[1];
    if(u == 0)
        return inf;
    while(T[u].c[0])
        u = T[u].c[0];
    return T[u].val;
}
#define root T[0].c[0]
int main() {
    int n = read();
    int res = read();
    root = newNode(res);
    while(--n) {
        int v = read();
        if(insert(root, 0, v))
            res +=
                std::min(v - pre(root), nxt(root) - v);
    }
    printf("%d\n", res);
    return 0;
}
