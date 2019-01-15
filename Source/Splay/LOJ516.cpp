#include <algorithm>
#include <cstdio>
#include <map>
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
int getRandom() {
    static int seed = 15455;
    return seed = seed * 48271LL % 2147483647;
}
const int size = 100005, inf = 2147483647;
struct Node {
    int c[2], p, siz, mind, maxv, minv;
} T[size];
#define ls (T[u].c[0])
#define rs (T[u].c[1])
void initNode(int u) {
    T[u].mind = inf;
    T[u].minv = T[u].maxv = u;
    T[u].siz = 1;
}
void update(int u) {
    T[u].siz = T[ls].siz + T[rs].siz + 1;
    T[u].mind =
        std::min(std::min(T[ls].mind, T[rs].mind),
                 std::min(ls ? u - T[ls].maxv : inf,
                          rs ? T[rs].minv - u : inf));
    T[u].maxv = (rs ? T[rs].maxv : u);
    T[u].minv = (ls ? T[ls].minv : u);
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
    int ku = getPos(u);
    int p = T[u].p;
    int kp = getPos(p);
    int pp = T[p].p;
    int t = T[u].c[ku ^ 1];
    connect(u, pp, kp);
    connect(p, u, ku ^ 1);
    connect(t, p, ku);
    update(p);
    update(u);
}
void splay(int u) {
    while(T[u].p) {
        int p = T[u].p;
        if(T[p].p)
            rotate(getPos(u) == getPos(p) ? p : u);
        rotate(u);
    }
}
int insert(int rt, int x) {
    while(true) {
        int& nxt = T[rt].c[x > rt];
        if(nxt)
            rt = nxt;
        else {
            nxt = x;
            T[x].p = rt;
            update(rt);
            break;
        }
    }
    splay(x);
    return x;
}
int dst;
void insertTree(int u) {
    if(u) {
        int lc = ls, rc = rs;
        insertTree(lc);
        ls = rs = 0;
        initNode(u);
        dst = insert(dst, u);
        insertTree(rc);
    }
}
int mergeTree(int u, int v) {
    if(T[u].siz > T[v].siz)
        std::swap(u, v);
    dst = v;
    insertTree(u);
    return dst;
}
std::map<int, int> rid;
typedef std::map<int, int>::iterator IterT;
std::pair<int, int> A[size];
int build(int l, int r) {
    if(l > r)
        return 0;
    if(l == r)
        return A[l].second;
    else {
        int m = (l + r) >> 1;
        int u = A[m].second;
        ls = build(l, m - 1);
        rs = build(m + 1, r);
        T[ls].p = T[rs].p = u;
        update(u);
        return u;
    }
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        A[i].first = read();
        A[i].second = i;
    }
    std::sort(A + 1, A + n + 1);
    T[0].mind = inf;
    for(int i = 1; i <= n; ++i)
        initNode(i);
    int l = 1, res = inf;
    for(int i = 1; i <= n; ++i) {
        if(A[i].first != A[i + 1].first) {
            int rt = build(l, i);
            rid[A[i].first] = rt;
            res = std::min(res, T[rt].mind);
            l = i + 1;
        }
    }
    while(m--) {
        int x = read();
        int y = read();
        if(res != 1 && x != y) {
            IterT rx = rid.find(x);
            if(rx != rid.end()) {
                int& ry = rid[y];
                if(ry) {
                    ry = mergeTree(ry, rx->second);
                    res = std::min(res, T[ry].mind);
                } else
                    ry = rx->second;
                rid.erase(rx);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
