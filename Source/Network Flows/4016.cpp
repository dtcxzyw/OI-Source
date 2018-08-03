#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 105, S = 0, inf = 0x3f3f3f3f;
int T;
struct Edge {
    int to, nxt, f, w;
} E[8 * size];
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
    memset(dis, 0x3f, sizeof(int) * siz);
    q[0] = S, dis[S] = 0, flag[S] = true;
    int b = 0, e = 1;
    while (b != e) {
        int u = q[b++];
        flag[u] = false;
        if (b == size) b = 0;
        for (int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            int cd = dis[u] + E[i].w;
            if (E[i].f && dis[v] > cd) {
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
    return dis[T] != inf;
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
int A[size];
int main() {
    int n;
    scanf("%d", &n);
    T = n + 1;
    int dst = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &A[i]);
        dst += A[i];
    }
    dst /= n;
    for (int i = 1; i <= n; ++i) {
        addEdge(S, i, A[i], 0);
        addEdge(i, T, dst, 0);
        int lp = (i > 1 ? i - 1 : n), rp = (i < n ? i + 1 : 1);
        addEdge(i, lp, inf, 1);
        addEdge(i, rp, inf, 1);
    }
    printf("%d\n", MCMF(T + 1));
    return 0;
}
