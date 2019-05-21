#include <cstdio>
#include <cstring>
int iabs(int x) {
    return x >= 0 ? x : -x;
}
int mini(int a, int b) {
    return a < b ? a : b;
}
const int size = 105, vsiz = size * 2;
struct Edge {
    int to, nxt, w;
} E[size * size * 2];
int last[vsiz], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
bool vis[vsiz], flag[vsiz], used[size * size * 2];
int dis[vsiz], hc = 0;
void DFS(int u) {
    vis[u] = true;
    flag[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        int nd = dis[u] + E[i].w;
        if(nd < dis[v]) {
            if(flag[v]) {
                used[i] = true;
                hc = v;
                return;
            } else {
                used[i] = true;
                dis[v] = nd;
                DFS(v);
                if(hc) {
                    if(E[i].to == hc)
                        hc = -1;
                    if(hc == -1)
                        used[i] = false;
                    return;
                }
                used[i] = false;
            }
        }
    }
    flag[u] = false;
}
struct Point {
    int x, y, z;
    void read() {
        scanf("%d%d%d", &x, &y, &z);
    }
} A[size], B[size];
int f[size][size], cl[size], cr[size];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        A[i].read();
    for(int i = 1; i <= m; ++i)
        B[i].read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &f[i][j]);
            int w = iabs(A[i].x - B[j].x) +
                iabs(A[i].y - B[j].y) + 1;
            if(f[i][j])
                addEdge(n + j, i, -w);
            if(f[i][j] != mini(A[i].z, B[j].z))
                addEdge(i, n + j, w);
            cl[i] += f[i][j];
            cr[j] += f[i][j];
        }
    int S = n + m + 1, T = S + 1;
    for(int i = 1; i <= n; ++i) {
        if(cl[i])
            addEdge(i, S, 0);
        if(cl[i] != A[i].z)
            addEdge(S, i, 0);
    }
    for(int i = 1; i <= m; ++i) {
        if(cr[i])
            addEdge(T, i + n, 0);
        if(cr[i] != B[i].z)
            addEdge(i + n, T, 0);
    }
    for(int i = 1; i <= T; ++i)
        if(!vis[i]) {
            memset(dis, 0, sizeof(dis));
            DFS(i);
            if(hc)
                break;
        }
    if(hc) {
        puts("SUBOPTIMAL");
        for(int u = 1; u <= n; ++u)
            for(int i = last[u]; i; i = E[i].nxt)
                if(used[i])
                    ++f[u][E[i].to - n];
        for(int u = 1; u <= m; ++u)
            for(int i = last[u + n]; i; i = E[i].nxt)
                if(used[i])
                    --f[E[i].to][u];
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j)
                printf("%d ", f[i][j]);
            puts("");
        }
    } else
        puts("OPTIMAL");
    return 0;
}
