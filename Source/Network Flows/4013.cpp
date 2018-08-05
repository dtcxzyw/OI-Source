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
const int maxs = 25, size = 4 * maxs * maxs, inf = 1 << 30;
int S, T;
struct Edge {
    int to, nxt, f, w;
} E[6 * size];
int last[size], cnt;
void clear() {
    memset(last, 0, sizeof(last));
    cnt = 1;
}
void addEdgeImpl(int u, int v, int f, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f, E[cnt].w = w;
    last[u] = cnt;
}
void addEdge(int u, int v, int f, int w) {
    addEdgeImpl(u, v, f, w);
    addEdgeImpl(v, u, 0, -w);
}
int dis[size], eid[size], q[size];
bool flag[size] = {};
bool SPFA(int siz) {
    memset(dis, 0xc0, sizeof(int) * siz);
    q[0] = S, dis[S] = 0, flag[S] = true;
    int b = 0, e = 1;
    while (b != e) {
        int u = q[b++];
        flag[u] = false;
        if (b == size) b = 0;
        for (int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            int cd = dis[u] + E[i].w;
            if (E[i].f && dis[v] < cd) {
                dis[v] = cd;
                eid[v] = i;
                if (!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if (e == size) e = 0;
                }
            }
        }
    }
    return dis[T] != 0xc0c0c0c0;
}
int MCMF(int siz) {
    int res = 0;
    while (SPFA(siz)) {
        int p = T, mf = inf;
        while (p != S) {
            int e = eid[p];
            mf = std::min(mf, E[e].f);
            p = E[e ^ 1].to;
        }
        p = T;
        while (p != S) {
            int e = eid[p];
            E[e].f -= mf, E[e ^ 1].f += mf;
            p = E[e ^ 1].to;
        }
        res += mf * dis[T];
    }
    return res;
}
int k;
int getId(int x, int y, int s) {
    return (x * k + y) << 1 | s;
}
int A[maxs][2 * maxs];
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i <= m; ++i) {
        int end = i + n;
        for (int j = 1; j < end; ++j)
            A[i][j] = read();
    }
    k = n + m;
    T = getId(m, k, 1) + 1;
    for (int t = 1; t <= 3; ++t) {
        clear();
        for (int i = 1; i <= n; ++i)
            addEdge(S, getId(1, i, 0), 1, 0);
        for (int i = 1; i < k; ++i)
            addEdge(getId(m, i, 1), T, inf, 0);
        int elimit = t == 3 ? inf : 1;
        for (int i = 1; i <= m; ++i) {
            int end = i + n;
            for (int j = 1; j < end; ++j) {
                addEdge(getId(i, j, 0), getId(i, j, 1), t == 1 ? 1 : inf, A[i][j]);
                if (i < m) {
                    addEdge(getId(i, j, 1), getId(i + 1, j, 0), elimit, 0);
                    addEdge(getId(i, j, 1), getId(i + 1, j + 1, 0), elimit, 0);
                }
            }
        }
        printf("%d\n", MCMF(T + 1));
    }
    return 0;
}
