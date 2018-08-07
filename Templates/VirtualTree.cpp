//P4103
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
const int size = 1000005;
template <int maxe>
struct G {
    struct Edge {
        int to, nxt;
    } E[maxe];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
};
G<size> g2;
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int inf = 1 << 29;
struct Result {
    Int64 ans1, sd;
    int ans2, ans3, minl, maxl, siz;
    Result() : ans1(0), sd(0), ans2(inf), ans3(-inf), minl(inf), maxl(-inf), siz(0) {}
    void initRoot() {
        minl = maxl = 0;
        siz = 1;
    }
    void update(const Result &rhs, int d) {
        Int64 csd = rhs.sd + asInt64(rhs.siz) * d;
        ans1 += rhs.ans1 + sd * rhs.siz + csd * siz;
        sd += csd;
        siz += rhs.siz;
        ans2 = std::min(ans2, std::min(rhs.ans2, minl + rhs.minl + d));
        ans3 = std::max(ans3, std::max(rhs.ans3, maxl + rhs.maxl + d));
        minl = std::min(minl, rhs.minl + d);
        maxl = std::max(maxl, rhs.maxl + d);
    }
    void print() const {
        printf("%lld %d %d\n", ans1, ans2, ans3);
    }
};
bool flag[size] = {};
int d[size];
Result DFSB(int u) {
    Result res;
    if (flag[u]) {
        res.initRoot();
        flag[u] = false;
    }
    for (int i = g2.last[u]; i; i = g2.E[i].nxt) {
        int v = g2.E[i].to;
        res.update(DFSB(v), d[v] - d[u]);
    }
    g2.last[u] = 0;
    return res;
}
G<size * 2> g1;
int dfn[size] = {}, icnt = 0, p[size][20];
void DFSA(int u) {
    for (int i = 1; i < 20; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    dfn[u] = ++icnt;
    for (int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if (!dfn[v]) {
            p[v][0] = u;
            d[v] = d[u] + 1;
            DFSA(v);
        }
    }
}
int getLca(int u, int v) {
    if (d[u] < d[v]) std::swap(u, v);
    int delta = d[u] - d[v];
    for (int i = 0; i < 20; ++i)
        if (delta & (1 << i))
            u = p[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; --i)
        if (p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    return p[u][0];
}
int id[size], st[size];
bool cmp(int a, int b) {
    return dfn[a] < dfn[b];
}
int buildTree(int k) {
    g2.cnt = 0;
    int top = 1;
    std::sort(id + 1, id + k + 1, cmp);
    st[1] = id[1];
    for (int i = 2; i <= k; ++i) {
        int u = id[i];
        int lca = getLca(u, st[top]);
        while (top > 1 && d[lca] < d[st[top - 1]]) {
            g2.addEdge(st[top - 1], st[top]);
            --top;
        }
        if (d[lca] < d[st[top]]) {
            g2.addEdge(lca, st[top]);
            --top;
        }
        if (top == 0 || d[st[top]] < d[lca]) st[++top] = lca;
        st[++top] = u;
    }
    while (top > 1) {
        g2.addEdge(st[top - 1], st[top]);
        --top;
    }
    return st[1];
}
int main() {
    int n = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        g1.addEdge(u, v);
        g1.addEdge(v, u);
    }
    DFSA(1);
    int q = read();
    while (q--) {
        int k = read();
        for (int i = 1; i <= k; ++i) {
            int u = read();
            id[i] = u;
            flag[u] = true;
        }
        int rt = buildTree(k);
        DFSB(rt).print();
    }
    return 0;
}
