#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
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
const int maxm = 25, size = maxm * 100, S = 0;
int T;
struct Edge {
    int to, nxt, f;
} E[4 * size];
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
        memcpy(now, last, sizeof(now));
        res += DFS(S, inf);
    }
    return res;
}
std::vector<int> to[maxm];
int cur[maxm], h[maxm], n, fa[maxm];
int getId(int u, int t) {
    return u + (n + 2) * t;
}
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) fa[u] = v;
}
int main() {
    n = read();
    int m = read();
    int k = read();
    T = n + 1;
    for (int i = 1; i <= T; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        h[i] = read();
        int r = read();
        to[i].resize(r);
        cur[i] = 0;
        for (int j = 0; j < r; ++j) {
            int x = read();
            to[i][j] = (x >= 0 ? x : T);
        }
        for (int j = 1; j < r; ++j)
            merge(to[i][j - 1], to[i][j]);
    }
    if (find(0) == find(T)) {
        int t = 1;
        while (true) {
            for (int i = 0; i <= n; ++i)
                addEdge(getId(i, t - 1), getId(i, t), inf);
            addEdge(getId(T, t), getId(T, t - 1), inf);
            for (int i = 1; i <= m; ++i) {
                int nxt = (cur[i] + 1) % to[i].size();
                addEdge(getId(to[i][cur[i]], t - 1), getId(to[i][nxt], t), h[i]);
                cur[i] = nxt;
            }
            if ((k -= dinic()) <= 0) {
                printf("%d\n", t);
                break;
            }
            ++t;
        }
    } else
        puts("0");
    return 0;
}
