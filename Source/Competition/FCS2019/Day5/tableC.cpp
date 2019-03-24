#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 205;
int S, T;
struct Edge {
    int to, nxt, f;
} E[size * size * 2];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
int q[size], d[size], gap[size];
void BFS() {
    q[0] = T, d[T] = 1, gap[1] = 1;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(!d[v]) {
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
    for(int i = last[u]; i; i = E[i].nxt) {
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
        d[T] = T + 10;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP() {
    BFS();
    memcpy(now, last, sizeof(last));
    int res = 0;
    while(d[T] <= T)
        res += DFS(S, 1 << 30);
    return res;
}
int X[size], Y[size];
bool flag[size][size];
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &X[i]);
    for(int i = 1; i <= m; ++i)
        scanf("%d", &Y[i]);
    for(int i = 1; i <= k; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        flag[x][y] = true;
        ++X[x], ++Y[y];
        if(X[x] > m || Y[y] > n) {
            puts("IIllIIll1£¡");
            return 0;
        }
    }
    S = n + m + 1, T = S + 1;
    for(int i = 1; i <= n; ++i)
        addEdge(S, i, m - X[i]);
    for(int i = 1; i <= m; ++i)
        addEdge(n + i, T, n - Y[i]);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            if(!flag[i][j])
                addEdge(i, n + j, 1);
    printf("%d\n", n * m - k - ISAP());
    return 0;
}
