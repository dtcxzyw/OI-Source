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
int fa[size], w[size], sum[size];
Int64 sum2[size] = {};
void divide(int u) {
    vis[u] = true;
    sum[u] = w[u];
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v]) {
            tot = siz[v], csiz = 1 << 30;
            getRoot(v, 0);
            fa[crt] = u;
            divide(crt);
            sum[u] += sum[crt];
            sum2[u] += sum2[crt] + asInt64(sum[crt]) * sum[crt];
        }
    }
}
void add(int u, int delta) {
    Int64 sumd = (2LL * sum[u] + delta) * delta;
    sum[u] += delta;
    while (fa[u]) {
        sum2[fa[u]] += sumd;
        sumd += (2LL * sum[fa[u]] + delta) * delta;
        sum[fa[u]] += delta;
        u = fa[u];
    }
}
Int64 wsum = 0;
Int64 query(int u) {
    Int64 res = sum2[u];
    while (fa[u]) {
        res += sum2[fa[u]] - (sum2[u] + asInt64(sum[u]) * sum[u]);
        Int64 psiz = wsum - sum[u];
        res += psiz * psiz;
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
    while (q--) {
        int op = read();
        if (op == 1) {
            int u = read();
            int val = read();
            int delta = val - w[u];
            wsum += delta;
            add(u, delta);
            w[u] = val;
        } else {
            printf("%lld\n", wsum * wsum + query(read()));
        }
    }
    return 0;
}
