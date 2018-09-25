#include <cstdio>
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
const int size = 500005;
struct G {
    struct Edge {
        int to, nxt;
    } E[size * 2];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} g, qe;
struct Query {
    int ans, xorv;
} q[size];
int fa[size];
int find(int u) {
    return fa[u] == u ? u : fa[u] = find(fa[u]);
}
void DFS(int u, int p) {
    for(int i = g.last[u]; i; i = g.E[i].nxt) {
        int v = g.E[i].to;
        if(v != p) {
            DFS(v, u);
            fa[v] = u;
        }
    }
    for(int i = qe.last[u]; i; i = qe.E[i].nxt) {
        int id = qe.E[i].to;
        if(q[id].ans == 0x3f3f3f3f) {
            q[id].ans = find(q[id].xorv ^ u);
        } else
            q[id].ans = 0x3f3f3f3f;
    }
}
int main() {
    int n = read();
    int m = read();
    int s = read();
    for(int i = 1; i <= n; ++i)
        fa[i] = i;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
    for(int i = 0; i < m; ++i) {
        int u = read();
        int v = read();
        qe.addEdge(u, i);
        qe.addEdge(v, i);
        q[i].xorv = u ^ v;
    }
    DFS(s, 0);
    for(int i = 0; i < m; ++i)
        printf("%d\n", q[i].ans);
    return 0;
}
