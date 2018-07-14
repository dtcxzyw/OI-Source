#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 200005;
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
int k, res = 1 << 30, icnt, tag[size], tcnt;
std::pair<int, int> info[size];
void DFS(int u, int p, int base, int deep) {
    if (base <= k && deep < res) {
        info[++icnt] = std::make_pair(base, deep);
        for (int i = last[u]; i; i = E[i].next) {
            int v = E[i].to;
            if (!vis[v] && v != p)
                DFS(v, u, base + E[i].w, deep + 1);
        }
        if (deep == 1) tag[++tcnt] = icnt;
    }
}
const int maxk = 1000005;
int mind[maxk];
void solve(int u) {
    icnt = 0, tcnt = 1;
    DFS(u, -1, 0, 0);
    for (int i = 1; i <= tcnt; ++i) {
        int b = tag[i - 1], e = tag[i];
        for (int j = b + 1; j <= e; ++j) {
            int len = info[j].first, d = info[j].second;
            res = std::min(res, d + mind[k - len]);
        }
        for (int j = b + 1; j <= e; ++j) {
            int len = info[j].first, d = info[j].second;
            mind[len] = std::min(mind[len], d);
        }
    }
    for (int i = 1; i <= icnt; ++i)
        mind[info[i].first] = 0x3f3f3f3f;
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v]) {
            tot = siz[v], csiz = 1 << 30;
            getRoot(v, 0);
            divide(crt);
        }
    }
}
int main() {
    int n = read();
    k = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    memset(mind, 0x3f, sizeof(mind));
    tag[0] = 0;
    tag[1] = 1;
    tot = n, csiz = 1 << 30;
    getRoot(1, -1);
    divide(crt);
    if (res < n)
        printf("%d\n", res);
    else
        puts("-1");
    return 0;
}
