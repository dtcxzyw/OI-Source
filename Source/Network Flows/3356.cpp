#include <algorithm>
#include <cstdio>
#include <cstring>
int getState() {
    int c;
    do
        c = getchar();
    while (c < '0' || c > '2');
    return c;
}
const int size = 2 * 40 * 40, S = 0, inf = 0x3f3f3f3f;
int T;
struct Edge {
    int to, nxt, f, w;
} E[4 * size];
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
        res += mf;
    }
    return res;
}
int map[40][40], p;
int getId(int x, int y, int st) {
    return (x + y * p) << 1 | st;
}
void tryLink(int x1, int y1, int x2, int y2) {
    int src = getId(x1, y1, 1);
    int dst = getId(x2, y2, 0);
    int ds = map[x2][y2];
    if (ds == '0' || ds == '2')
        addEdge(src, dst, inf, 0);
}
int cid;
void DFS(int u) {
    for (int i = last[u]; i; i = E[i].nxt)
        if ((i & 1) == 0 && E[i ^ 1].f > 0) {
            int v = E[i].to;
            --E[i ^ 1].f;
            int ui = u >> 1, vi = v >> 1;
            if (ui != vi)
                printf("%d %d\n", cid, vi == ui + 1 ? 1 : 0);
            DFS(v);
            return;
        }
}
int main() {
    int n, q;
    scanf("%d%d%d", &n, &p, &q);
    addEdge(S, getId(1, 1, 0), n, 0);
    for (int i = 1; i <= q; ++i)
        for (int j = 1; j <= p; ++j)
            map[j][i] = getState();
    for (int i = 1; i <= p; ++i)
        for (int j = 1; j <= q; ++j) {
            if (map[i][j] == '2')
                addEdge(getId(i, j, 0), getId(i, j, 1), 1, 1);
            if (map[i][j] != '1') {
                addEdge(getId(i, j, 0), getId(i, j, 1), inf, 0);
                tryLink(i, j, i + 1, j);
                tryLink(i, j, i, j + 1);
            }
        }
    T = getId(p, q, 1);
    int res = MCMF(T + 1);
    for (cid = 1; cid <= res; ++cid)
        DFS(getId(1, 1, 0));
    return 0;
}
