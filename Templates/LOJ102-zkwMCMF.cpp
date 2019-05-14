#include <cstdio>
int mini(int a, int b) {
    return a < b ? a : b;
}
const int size = 405, inf = 2147483647;
struct Edge {
    int to, nxt, f, w;
} E[30005];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f,
    E[cnt].w = w;
    last[u] = cnt;
}
void addEdge(int u, int v, int f, int w) {
    addEdgeImpl(u, v, f, w);
    addEdgeImpl(v, u, 0, -w);
}
int n, dis[size], maxF = 0, minW = 0, vis[size],
                  ts = 0;
bool update() {
    int mdel = inf;
    for(int u = 1; u <= n; ++u) {
        if(vis[u] != ts)
            continue;
        for(int i = last[u]; i; i = E[i].nxt)
            if(E[i].f && vis[E[i].to] != ts)
                mdel = mini(mdel, dis[E[i].to] +
                                E[i].w - dis[u]);
    }
    if(mdel == inf)
        return false;
    for(int u = 1; u <= n; ++u)
        if(vis[u] == ts)
            dis[u] += mdel;
    return true;
}
int aug(int u, int f) {
    if(u == n || f == 0) {
        maxF += f, minW += f * dis[1];
        return f;
    }
    int res = 0;
    vis[u] = ts;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(vis[v] != ts && E[i].f &&
           dis[v] == dis[u] - E[i].w) {
            int k = aug(v, mini(f, E[i].f));
            E[i].f -= k, E[i ^ 1].f += k;
            f -= k, res += k;
            if(f == 0)
                break;
        }
    }
    return res;
}
int main() {
    int m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        int u, v, f, w;
        scanf("%d%d%d%d", &u, &v, &f, &w);
        addEdge(u, v, f, w);
    }
    do {
        do
            ++ts;
        while(aug(1, inf));
    } while(update());
    printf("%d %d\n", maxF, minW);
    return 0;
}
