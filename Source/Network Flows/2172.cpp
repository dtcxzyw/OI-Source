#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 55, size = 2 * maxn * maxn, S = 0;
int T;
struct Edge {
    int to, nxt, f;
} E[12 * size];
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
int m;
int getId(int x, int y, int s) {
    return (x * m + y) << 1 | s;
}
char map[maxn][maxn];
const int fac[2] = {1, -1};
int off[4][2];
int main() {
    int n, r, c;
    scanf("%d%d%d%d", &n, &m, &r, &c);
    T = getId(n, m, 1) + 1;
    int end = r == c ? 2 : 4;
    for (int i = 0; i < 2; ++i) {
        off[i][0] = r;
        off[i][1] = fac[i] * c;
    }
    if (r != c) {
        for (int i = 0; i < 2; ++i) {
            off[i + 2][0] = c;
            off[i + 2][1] = fac[i] * r;
        }
    }
    for (int i = 1; i <= n; ++i)
        scanf("%s", map[i] + 1);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            if (map[i][j] != 'x') {
                addEdge(S, getId(i, j, 0), 1);
                addEdge(getId(i, j, 1), T, 1);
                for (int k = 0; k < end; ++k) {
                    int cx = i + off[k][0], cy = j + off[k][1];
                    if (1 <= cx && cx <= n && 1 <= cy && cy <= m && map[cx][cy] != 'x')
                        addEdge(getId(i, j, 0), getId(cx, cy, 1), inf);
                }
            } else
                ++cnt;
    }
    printf("%d\n", n * m - cnt - dinic(T + 1));
    return 0;
}
