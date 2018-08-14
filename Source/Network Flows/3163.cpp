#include <algorithm>
#include <cstdio>
#include <cstring>
int getState() {
    int c;
    do
        c = getchar();
    while (c < 'A' || c > 'Z');
    return c;
}
const int size = 55, S = size - 1, T = size - 2;
struct Edge {
    int to, nxt, f;
} E[2 * size * size];
int last[size], cnt;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
const int inf = 1 << 29;
int d[size], q[size];
bool BFS() {
    memset(d, 0, sizeof(d));
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
int dinic() {
    int res = 0;
    while (BFS()) {
        memcpy(now, last, sizeof(last));
        res += DFS(S, inf);
    }
    return res;
}
int n, s1, t1, c1, c2;
char map[size][size];
int solve(int s2, int t2) {
    memset(last, 0, sizeof(last));
    cnt = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int s = map[i][j];
            if (s == 'X') continue;
            addEdge(i, j, s == 'O' ? 2 : inf);
        }
    addEdge(S, s1, c1);
    addEdge(S, s2, c2);
    addEdge(t1, T, c1);
    addEdge(t2, T, c2);
    return dinic();
}
int main() {
    int s2, t2;
    while (scanf("%d%d%d%d%d%d%d", &n, &s1, &t1, &c1, &s2, &t2, &c2) != EOF) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                map[i][j] = getState();
        c1 *= 2, c2 *= 2;
        int lim = c1 + c2;
        puts(solve(s2, t2) == lim && solve(t2, s2) == lim ? "Yes" : "No");
    }
    return 0;
}
