#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <queue>
typedef double FT;
const FT inf = 1e20, eps = 1e-8;
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
FT readFT() {
    int c;
    do
        c = getchar();
    while(!isgraph(c));
    char str[32];
    int pos = 0;
    while(isgraph(c)) {
        str[pos++] = c;
        c = getchar();
    }
    str[pos] = '\0';
    return strtod(str, 0);
}
bool equalZero(FT x) {
    return fabs(x) < eps;
}
const int size = 5005;
struct G {
    struct Edge {
        int to, nxt;
        FT w;
    } E[200005];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v, FT w) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u],
        E[cnt].w = w;
        last[u] = cnt;
    }
} g1, g2;
bool flag[size];
int q[size];
FT dis[size];
void SPFA(int n) {
    for(int i = 1; i < n; ++i)
        dis[i] = inf;
    dis[n] = 0.0, q[0] = n, flag[n] = true;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
            int v = g1.E[i].to;
            FT cd = dis[u] + g1.E[i].w;
            if(cd < dis[v]) {
                dis[v] = cd;
                if(!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if(e == size)
                        e = 0;
                }
            }
        }
    }
}
struct Node {
    int ls, rs, dis, p;
    FT val;
} T[size * 900];
int root[size], icnt = 0;
bool enableClone = true;
int cloneNode(int src) {
    if(enableClone) {
        int id = ++icnt;
        T[id] = T[src];
        return id;
    }
    return src;
}
int merge(int u, int v) {
    if(u && v) {
        if(T[u].val > T[v].val)
            std::swap(u, v);
        int w = cloneNode(u);
        T[w].rs = merge(T[w].rs, v);
        if(T[T[w].ls].dis < T[T[w].rs].dis)
            std::swap(T[w].ls, T[w].rs);
        T[w].dis = T[T[w].rs].dis + 1;
        return w;
    }
    return u | v;
}
int insert(int src, FT val, int p) {
    int id = ++icnt;
    T[id].val = val;
    T[id].p = p;
    return merge(src, id);
}
int n, fa[size];
void DFS(int u) {
    if(u != n) {
        bool haveEdge = false;
        enableClone = false;
        for(int i = g2.last[u]; i; i = g2.E[i].nxt) {
            int v = g2.E[i].to;
            FT delta = dis[v] + g2.E[i].w - dis[u];
            if(v == fa[u] && equalZero(delta) &&
               !haveEdge)
                haveEdge = true;
            else
                root[u] = insert(root[u], delta, v);
        }
        enableClone = true;
        root[u] = merge(root[u], root[fa[u]]);
    }
    for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        FT delta = dis[u] + g1.E[i].w - dis[v];
        if(!fa[v] && equalZero(delta)) {
            fa[v] = u;
            DFS(v);
        }
    }
}
struct Info {
    FT dis;
    int id;
    Info(int id, FT dis) : dis(dis), id(id) {}
    bool operator<(const Info& rhs) const {
        return dis > rhs.dis;
    }
};
int main() {
    n = read();
    int m = read();
    FT e = readFT();
    while(m--) {
        int u = read();
        int v = read();
        FT w = readFT();
        g1.addEdge(v, u, w);
        g2.addEdge(u, v, w);
    }
    SPFA(n);
    fa[n] = n;
    DFS(n);
    int res = 0;
    if(e >= dis[1]) {
        e -= dis[1], ++res;
        std::priority_queue<Info> heap;
        heap.push(
            Info(root[1], dis[1] + T[root[1]].val));
        while(heap.size() && e >= heap.top().dis) {
            int u = heap.top().id;
            int v = root[T[u].p];
            FT d = heap.top().dis;
            heap.pop();
            e -= d;
            ++res;
            if(v)
                heap.push(Info(v, d + T[v].val));
            FT base = d - T[u].val;
            if(T[u].ls)
                heap.push(Info(T[u].ls,
                               base + T[T[u].ls].val));
            if(T[u].rs)
                heap.push(Info(T[u].rs,
                               base + T[T[u].rs].val));
        }
    }
    printf("%d\n", res);
    return 0;
}
