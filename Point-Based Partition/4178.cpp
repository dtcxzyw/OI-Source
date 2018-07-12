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
const int size = 40005;
struct Edge {
    int to, next, w;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int tot, csiz, crt, siz[size];
bool vis[size] = {};
int getRoot(int u, int p) {
    int maxs = 0;
    siz[u] = 1;
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v] && v != p) {
            getRoot(v, u);
            siz[u] += siz[v];
            maxs = std::max(maxs, siz[v]);
        }
    }
    maxs = std::max(maxs, tot - siz[u]);
    if (csiz > maxs) {
        csiz = maxs;
        crt = u;
    }
}
int dis[size], dcnt;
void DFS(int u, int p, int base) {
    dis[++dcnt] = base;
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v] && v != p)
            DFS(v, u, base + E[i].w);
    }
}
int k;
int solve(int u, int base) {
    dcnt = 0;
    DFS(u, 0, base);
    std::sort(dis + 1, dis + dcnt + 1);
    int l = 1, r = dcnt, res = 0;
    while (l < r) {
        if (dis[l] + dis[r] <= k) {
            res += r - l;
            ++l;
        } else
            --r;
    }
    return res;
}
long long res = 0;
void divide(int u) {
    vis[u] = true;
    res += solve(u, 0);
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v]) {
            tot = siz[v], csiz = 1 << 30;
            res -= solve(v, E[i].w);
            getRoot(v, 0);
            divide(crt);
        }
    }
}
int main() {
    int n = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    k = read();
    tot = n, csiz = 1 << 30;
    getRoot(1, 0);
    divide(crt);
    printf("%lld\n", res);
    return 0;
}
