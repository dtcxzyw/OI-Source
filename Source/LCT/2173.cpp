#include <algorithm>
#include <cstdio>
#include <vector>
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
const int size = 10005;
int A[size];
struct Node {
    int maxv, id, p, c[2];
    bool rev;
} T[size * 10];
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
    T[u].maxv = std::max(std::max(T[ls].maxv, T[rs].maxv), A[T[u].id]);
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
typedef std::vector<std::pair<int, int> > GT;
typedef GT::iterator IterT;
GT G[size];
bool cmp(std::pair<int, int> a, std::pair<int, int> b) {
    return a.first < b.first;
}
int n;
int getId(int u, int c) {
    return c * n + u;
}
void link(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
    T[u].p = v;
}
void cut(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
    T[u].p = T[v].c[0] = 0;
    update(v);
}
int cnt[size][10] = {};
const char *color(int u, int v, int w) {
    if (u > v) std::swap(u, v);
    IterT it = std::lower_bound(G[u].begin(), G[u].end(), std::make_pair(v, 0), cmp);
    if (it == G[u].end() || it->first != v) return "No such edge.";
    int ow = it->second;
    if (w != ow) {
        if (cnt[u][w] > 1 || cnt[v][w] > 1) return "Error 1.";
        if (find(getId(u, w)) == find(getId(v, w))) return "Error 2.";
        cut(getId(u, ow), getId(v, ow));
        link(getId(u, w), getId(v, w));
        it->second = w;
        --cnt[u][ow], --cnt[v][ow];
        ++cnt[u][w], ++cnt[v][w];
    }
    return "Success.";
}
int main() {
    n = read();
    int m = read();
    int c = read();
    int k = read();
    int end = n * c;
    for (int i = 1; i <= n; ++i) {
        int val = read();
        A[i] = val;
        for (int j = i; j <= end; j += n) {
            T[j].id = i;
            T[j].maxv = val;
        }
    }
    while (m--) {
        int u = read();
        int v = read();
        int w = read();
        if (u > v) std::swap(u, v);
        G[u].push_back(std::make_pair(v, w));
        int cu = getId(u, w), cv = getId(v, w);
        link(cu, cv);
        ++cnt[u][w];
        ++cnt[v][w];
    }
    for (int i = 1; i <= n; ++i)
        std::sort(G[i].begin(), G[i].end(), cmp);
    while (k--) {
        switch (read()) {
            case 0: {
                int u = read();
                for (int i = u; i <= end; i += n)
                    splay(i);
                A[u] = read();
                break;
            }
            case 1: {
                int u = read();
                int v = read();
                int w = read();
                puts(color(u, v, w));
                break;
            }
            case 2: {
                int w = read();
                int cu = getId(read(), w), cv = getId(read(), w);
                makeRoot(cu);
                if (find(cv) == cu)
                    printf("%d\n", T[cv].maxv);
                else
                    puts("-1");
                break;
            }
        }
    }
    return 0;
}
