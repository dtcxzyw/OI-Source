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
const int maxn = 505, size = 2 * maxn, S = 0;
int T;
struct Edge {
    int to, nxt, f;
} E[2 * (3 * maxn + maxn * maxn / 2)];
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
int A[maxn], dp[maxn];
int main() {
    int n = read();
    T = 2 * n + 1;
    A[0] = dp[0] = 0;
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        A[i] = read();
        for (int j = 0; j < i; ++j)
            if (A[j] <= A[i])
                dp[i] = std::max(dp[i], dp[j] + 1);
        res = std::max(res, dp[i]);
    }
    printf("%d\n", res);
    for (int i = 1; i <= n; ++i) {
        if (dp[i] == 1) addEdge(S, i, inf);
        if (dp[i] == res) addEdge(i + n, T, inf);
        addEdge(i, i + n, 1);
        for (int j = 1; j < i; ++j)
            if (A[j] <= A[i] && dp[i] == dp[j] + 1)
                addEdge(j + n, i, 1);
    }
    int ans1 = dinic(T + 1);
    printf("%d\n", ans1);
    if (res > 1) {
        addEdge(1, 1 + n, inf);
        addEdge(n, n + n, inf);
    }
    int ans2 = ans1 + dinic(T + 1);
    printf("%d\n", ans2);
    return 0;
}
