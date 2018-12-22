#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int maxn = 200005, maxk = 500005;
template <int maxv, int maxe>
struct Graph {
    struct Edge {
        int to, nxt;
    } E[maxe];
    int last[maxv], cnt;
    Graph() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
};
Graph<maxn * 2, maxn * 2> T;
Graph<maxn, maxk * 2> Q;
int fa[maxn * 2];
int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}
struct Query {
    int u, v, d, xorv;
} A[maxk];
int n, d[maxn * 2];
void DFS(int u) {
    for(int i = T.last[u]; i; i = T.E[i].nxt) {
        int v = T.E[i].to;
        d[v] = d[u] + 1;
        DFS(v);
        fa[v] = u;
    }
    if(u <= n)
        for(int i = Q.last[u]; i; i = Q.E[i].nxt) {
            int qid = Q.E[i].to;
            if(A[qid].d)
                A[qid].d = d[find(A[qid].xorv ^ u)];
            else
                A[qid].d = -1;
        }
}
int g[maxn], id[maxk];
bool cmp(int a, int b) {
    return A[a].d > A[b].d;
}
int main() {
    n = read();
    int m = read();
    int k = read();
    for(int i = 1; i <= n; ++i)
        g[i] = read();
    for(int i = 1; i <= m; ++i) {
        int u = find(read()), v = find(read());
        int id = n + i;
        T.addEdge(id, u);
        T.addEdge(id, v);
        fa[u] = fa[v] = id;
    }
    for(int i = 1; i <= k; ++i) {
        A[i].u = read();
        A[i].v = read();
        if(find(A[i].u) != find(A[i].v)) {
            --i, --k;
            continue;
        }
        A[i].xorv = A[i].u ^ A[i].v;
        id[i] = i;
        Q.addEdge(A[i].u, i);
        Q.addEdge(A[i].v, i);
    }
    memset(fa + 1, 0, sizeof(int) * (n + m));
    for(int i = n + m; i; --i)
        if(!d[i]) {
            d[i] = 1;
            DFS(i);
        }
    std::stable_sort(id + 1, id + k + 1, cmp);
    long long ans = 0;
    for(int i = 1; i <= k; ++i) {
        int qid = id[i];
        int u = A[qid].u, v = A[qid].v;
        int delta = std::min(g[u], g[v]);
        ans += delta;
        g[u] -= delta, g[v] -= delta;
    }
    printf("%lld\n", ans << 1);
    return 0;
}
