#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int size = 125, inf = 0x3f3f3f3f;
struct Edge {
    int to, rev, f, w;
    Edge(int to, int rev, int f, int w)
        : to(to), rev(rev), f(f), w(w) {}
};
std::vector<Edge> G[size];
void addEdge(int u, int v, int f, int w) {
    int usiz = G[u].size(), vsiz = G[v].size();
    G[u].push_back(Edge(v, vsiz, f, w));
    G[v].push_back(Edge(u, usiz, 0, -w));
}
int dis[size], q[size], S, T;
bool flag[size];
bool SPFA() {
    memset(dis, 0xc0, sizeof(dis));
    dis[T] = 0, flag[T] = true, q[0] = T;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(auto E : G[u]) {
            int v = E.to;
            int dv = dis[u] - E.w;
            if(G[v][E.rev].f && dv > dis[v]) {
                dis[v] = dv;
                if(!flag[v]) {
                    flag[v] = true;
                    if(b == e || dis[q[b]] >= dis[v]) {
                        q[e++] = v;
                        if(e == size)
                            e = 0;
                    } else {
                        if(--b == -1)
                            b = size - 1;
                        q[b] = v;
                    }
                }
            }
        }
    }
    return dis[S] != 0xc0c0c0c0;
}
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    flag[u] = true;
    int res = 0, k;
    for(int& i = now[u]; i < G[u].size(); ++i) {
        Edge& E = G[u][i];
        int v = E.to;
        if(E.f && !flag[v] && dis[u] == dis[v] + E.w &&
           (k = DFS(v, std::min(f, E.f)))) {
            E.f -= k, G[v][E.rev].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    flag[u] = false;
    if(!res)
        dis[u] = 0xc0c0c0c0;
    return res;
}
int ceilDiv(int a, int b) {
    return (a + b - 1) / b;
}
int MCMF(int w) {
    int sf = 0, sc = 0, ans = 0;
    while(SPFA()) {
        memset(now, 0, sizeof(now));
        int k, cd = dis[S];
        while((k = DFS(S, inf))) {
            if(k == inf)
                break;
            sf += k;
            sc += k * cd;
            ans = std::max(ans, ceilDiv(sc - w, sf));
        }
    }
    return ans;
}
int t[size];
int main() {
    int n, m, w;
    scanf("%d%d%d", &n, &m, &w);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &t[i]);
    S = 2 * n + 1;
    T = S + 1;
    for(int i = 1; i <= n; ++i) {
        int c;
        scanf("%d", &c);
        addEdge(S, i, inf, 0);
        addEdge(i, i + n, inf, 0);
        addEdge(i, i + n, c, t[i]);
        addEdge(i + n, T, inf, 0);
    }
    for(int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u + n, v, inf, 0);
    }
    printf("%d\n", MCMF(w));
    return 0;
}
