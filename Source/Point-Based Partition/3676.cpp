#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 200005;
struct Edge {
    int to, next;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u];
    last[u] = cnt;
}
int st[size << 1][19], id[size], depth[size], scnt = 0, w[size], wsum = 0;
Int64 base = 0;
int DFS(int u, int p, int d) {
    int sw = w[u];
    st[++scnt][0] = depth[u] = d;
    id[u] = scnt;
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (p != v) {
            sw += DFS(v, u, d + 1);
            st[++scnt][0] = d;
        }
    }
    base += sw * asInt64(wsum - sw);
    return sw;
}
int lg[size << 1];
void buildST() {
    DFS(1, 0, 0);
    lg[1] = 0;
    for (int i = 2; i <= scnt; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= 18; ++i) {
        int end = scnt - (1 << i) + 1, off = 1 << (i - 1);
        for (int j = 1; j <= end; ++j)
            st[j][i] = std::min(st[j][i - 1], st[j + off][i - 1]);
    }
}
int dis(int u, int v) {
    int l = id[u], r = id[v];
    if (l > r) std::swap(l, r);
    int k = lg[r - l + 1];
    return depth[u] + depth[v] - (std::min(st[l][k], st[r - (1 << k) + 1][k]) << 1);
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
int fa[size];
void divide(int u) {
    vis[u] = true;
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v]) {
            tot = siz[v], csiz = 1 << 30;
            getRoot(v, 0);
            fa[crt] = u;
            divide(crt);
        }
    }
}
Int64 diss[size] = {}, disf[size] = {};
int sum[size] = {};
void add(int u, int delta) {
    sum[u] += delta;
    int src = u;
    while (fa[u]) {
        Int64 d = dis(src, fa[u]);
        Int64 val = d * delta;
        diss[fa[u]] += val;
        disf[u] += val;
        sum[fa[u]] += delta;
        u = fa[u];
    }
}
Int64 calc(int u) {
    Int64 res = diss[u];
    int src = u;
    while (fa[u]) {
        Int64 d = dis(src, fa[u]);
        res += (diss[fa[u]] - disf[u]) + d * (sum[fa[u]] - sum[u]);
        u = fa[u];
    }
    return res;
}
int main() {
    int n = read();
    int q = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= n; ++i) {
        w[i] = read();
        wsum += w[i];
    }
    tot = n, csiz = 1 << 30;
    getRoot(1, 0);
    divide(crt);
    buildST();
    for (int i = 1; i <= n; ++i)
        add(i, w[i]);
    while (q--) {
        int op = read();
        if (op == 1) {
            int u = read();
            int v = read();
            int delta = v - w[u];
            w[u] = v;
            base += delta * calc(u);
            wsum += delta;
            add(u, delta);
        } else
            printf("%lld\n", wsum * (calc(read()) + wsum) - base);
    }
    return 0;
}
