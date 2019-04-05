#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 2505;
struct Edge {
    int to, nxt, f;
} E[10 * size];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int w) {
    addEdgeImpl(u, v, w);
    addEdgeImpl(v, u, 0);
}
void addEdgeBid(int u, int v, int w) {
    addEdge(u, v, w);
    addEdge(v, u, w);
}
int S, T, d[size], q[size], gap[size];
void BFS() {
    int b = 0, e = 1;
    q[0] = T, d[T] = 1, ++gap[1];
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i ^ 1].f && !d[v]) {
                d[v] = d[u] + 1;
                ++gap[d[v]];
                q[e++] = v;
            }
        }
    }
}
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[u] == d[v] + 1 &&
           (k = DFS(v, std::min(f, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f == 0)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = T + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP() {
    BFS();
    memcpy(now + 1, last + 1, sizeof(int) * T);
    int res = 0;
    while(d[S] <= T)
        res += DFS(S, 1 << 30);
    return res;
}
char buf[55][55];
int pid[55][55];
int main() {
    int n, m, a, b;
    scanf("%d%d%d%d", &n, &m, &a, &b);
    S = n * m + 1, T = S + 1;
    for(int i = 1, id = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j, ++id)
            pid[i][j] = id;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", buf[i] + 1);
        for(int j = 1; j <= m; ++j)
            if(buf[i][j] == '.')
                addEdge(S, pid[i][j], b);
            else
                addEdge(pid[i][j], T, b);
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            if(i < n)
                addEdgeBid(pid[i][j], pid[i + 1][j],
                           a);
            if(j < m)
                addEdgeBid(pid[i][j], pid[i][j + 1],
                           a);
        }
    printf("%d\n", ISAP());
    return 0;
}
