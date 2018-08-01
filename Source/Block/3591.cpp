#include <algorithm>
#include <cmath>
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
const int size = 50005;
struct Edge {
    int to, next;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u];
    last[u] = cnt;
}
int bsiz, p[size][16], w[size][230], d[size], A[size];
int DFSD(int u, int p, int d) {
    int res = d;
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (v != p) res = std::max(res, DFSD(v, u, d + 1));
    }
    return res;
}
void DFS(int u) {
    for (int i = 1; i < 16; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    int pu = u;
    for (int i = 1; i <= bsiz; ++i) {
        pu = p[pu][0];
        w[u][i] = w[pu][i] + A[u];
    }
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (v != p[u][0]) {
            p[v][0] = u;
            d[v] = d[u] + 1;
            DFS(v);
        }
    }
}
int jump(int u, int k) {
    for (int i = 0; i < 16; ++i)
        if (k & (1 << i)) u = p[u][i];
    return u;
}
int lca(int u, int v) {
    if (d[u] < d[v]) std::swap(u, v);
    u = jump(u, d[u] - d[v]);
    for (int i = 15; i >= 0; --i)
        if (p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    return u == v ? u : p[u][0];
}
int queryK(int u, int k) {
    if (k <= bsiz)
        return w[u][k];
    else {
        int res = 0;
        while (u) {
            res += A[u];
            u = jump(u, k);
        }
        return res;
    }
}
int queryKL(int u, int k, int dlimit) {
    int delta = d[u] - dlimit;
    if (delta < 0) return 0;
    int x = jump(u, k * (delta / k + 1));
    return queryK(u, k) - queryK(x, k);
}
int query(int u, int v, int k) {
    int fa = lca(u, v);
    if (fa == v)
        return queryKL(u, k, d[v]);
    else {
        int dis = d[u] + d[v] - (d[fa] << 1);
        int res = A[v];
        int last = dis % k;
        if (last == 0) last = k;
        v = jump(v, last);
        if (fa == u)
            res += queryKL(v, k, d[u]);
        else {
            res += queryKL(u, k, d[fa]) + queryKL(v, k, d[fa]);
            if ((d[u] - d[fa]) % k == 0) res -= A[fa];
        }
        return res;
    }
}
int B[size];
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i) A[i] = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    int maxd = DFSD(1, 0, 0);
    bsiz = sqrt(maxd + 1);
    d[0] = -1;
    DFS(1);
    for (int i = 0; i < n; ++i) B[i] = read();
    for (int i = 1; i < n; ++i) printf("%d\n", query(B[i - 1], B[i], read()));
    return 0;
}
