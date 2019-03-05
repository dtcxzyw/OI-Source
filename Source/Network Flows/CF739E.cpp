#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
const int size = 2015;
typedef double FT;
const FT eps = 1e-8, inf = 1e20;
struct Edge {
    int to, rev, f;
    FT w;
    Edge(int to, int rev, int f, FT w)
        : to(to), rev(rev), f(f), w(w) {}
};
std::vector<Edge> G[size];
void addEdge(int u, int v, int f, FT w) {
    int usiz = G[u].size(), vsiz = G[v].size();
    G[u].push_back(Edge(v, vsiz, f, w));
    G[v].push_back(Edge(u, usiz, 0, -w));
}
FT dis[size];
int q[size], S, T;
bool flag[size];
bool SPFA(int n) {
    for(int i = 1; i <= n; ++i)
        dis[i] = -inf;
    dis[T] = 0, flag[T] = true, q[0] = T;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(auto E : G[u]) {
            int v = E.to;
            FT dv = dis[u] - E.w;
            if(G[v][E.rev].f && dv > dis[v] + eps) {
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
    return dis[S] != -inf;
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
        if(E.f && !flag[v] &&
           fabs(dis[v] + E.w - dis[u]) < eps &&
           (k = DFS(v, std::min(f, E.f)))) {
            E.f -= k, G[v][E.rev].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    flag[u] = false;
    if(!res)
        dis[u] = -inf;
    return res;
}
FT MCMF(int n) {
    FT res = 0;
    while(SPFA(n)) {
        memset(now + 1, 0, sizeof(int) * n);
        int cf = 0, k;
        FT cd = dis[S];
        while((k = DFS(S, 1 << 30)))
            cf += k;
        res += cf * cd;
    }
    return res;
}
FT P[size];
int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    int SA = n + 1, SB = SA + 1;
    S = SB + 1;
    T = S + 1;
    addEdge(S, SA, a, 0);
    addEdge(S, SB, b, 0);
    for(int i = 1; i <= n; ++i)
        scanf("%lf", &P[i]);
    for(int i = 1; i <= n; ++i) {
        FT U;
        scanf("%lf", &U);
        addEdge(SA, i, 1, P[i]);
        addEdge(SB, i, 1, U);
        addEdge(i, T, 1, 0);
        addEdge(i, T, 1, -P[i] * U);
    }
    printf("%.8lf\n", MCMF(T));
    return 0;
}
