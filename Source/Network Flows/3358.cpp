#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 505, size = 2 * maxn, inf = 1 << 30, S = 0;
int T;
struct Edge {
    int to, nxt, f, w;
} E[2 * maxn * maxn];
int last[size] = {}, cnt = 1;
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
struct Range {
    int l, r;
    bool operator<(const Range &rhs) const {
        return l < rhs.l;
    }
} A[maxn];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &A[i].l, &A[i].r);
    std::sort(A + 1, A + n + 1);
    int S2 = 2 * n + 1;
    T = S2 + 1;
    addEdge(S, S2, k, 0);
    for (int i = 1; i <= n; ++i) {
        addEdge(S2, i, 1, 0);
        addEdge(i + n, T, 1, 0);
        addEdge(i, i + n, 1, A[i].r - A[i].l);
        for (int j = i + 1; j <= n; ++j)
            if (A[j].l >= A[i].r)
                addEdge(i + n, j, 1, 0);
    }
    printf("%d\n", MCMF(T + 1));
    return 0;
}
