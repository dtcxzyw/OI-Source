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
const int maxn = 205, size = maxn * maxn, S = 0;
int T;
struct Edge {
    int to, nxt, f;
} E[18 * size];
int last[size] = {}, cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
const int inf = 1 << 30;
int d[size], q[size];
bool BFS(int siz) {
    memset(d, 0, sizeof(int) * siz);
    int b = 0, e = 1;
    q[0] = S;
    d[S] = 1;
    while (b != e) {
        int u = q[b++];
        for (int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if (E[i].f && d[v] == 0) {
                d[v] = d[u] + 1;
                q[e++] = v;
            }
        }
    }
    return d[T];
}
int now[size];
int DFS(int u, int f) {
    if (u == T || f == 0) return f;
    int res = 0, k;
    for (int &i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if (d[v] == d[u] + 1 && (k = DFS(v, std::min(E[i].f, f)))) {
            E[i].f -= k;
            E[i ^ 1].f += k;
            f -= k;
            res += k;
            if (f == 0) break;
        }
    }
    if (res == 0) d[u] = -1;
    return res;
}
int dinic(int siz) {
    int res = 0;
    while (BFS(siz)) {
        memcpy(now, last, sizeof(int) * siz);
        res += DFS(S, inf);
    }
    return res;
}
bool map[maxn][maxn] = {};
int n;
int getId(int x, int y) {
    return x + y * n;
}
const int off[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
int main() {
    n = read();
    int m = read();
    T = getId(n, n) + 1;
    for (int i = 0; i < m; ++i) {
        int x = read();
        int y = read();
        map[x][y] = true;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (!map[i][j]) {
                if ((i + j) & 1) {
                    addEdge(S, getId(i, j), 1);
                    int src = getId(i, j);
                    for (int k = 0; k < 8; ++k) {
                        int x = i + off[k][0], y = j + off[k][1];
                        if (1 <= x && x <= n && 1 <= y && y <= n && !map[x][y])
                            addEdge(src, getId(x, y), inf);
                    }
                } else
                    addEdge(getId(i, j), T, 1);
            }
    printf("%d\n", n * n - m - dinic(T + 1));
    return 0;
}
