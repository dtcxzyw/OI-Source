#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int size = 2005, inf = 0x3f3f3f3f;
struct Edge {
    int to, rev, f, w;
    Edge(int to, int rev, int f, int w)
        : to(to), rev(rev), f(f), w(w) {}
};
std::vector<Edge> G[size];
void addEdge(int u, int v, int f, int w) {
    int urev = G[u].size(), vrev = G[v].size();
    G[u].push_back(Edge(v, vrev, f, w));
    G[v].push_back(Edge(u, urev, 0, -w));
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
int dis[size], q[size], SS, TT;
bool flag[size];
bool SPFA(int n) {
    memset(dis + 1, 0x3f, sizeof(int) * n);
    dis[TT] = 0, q[0] = TT, flag[TT] = true;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(auto E : G[u]) {
            int v = E.to;
            int dv = dis[u] - E.w;
            if(G[v][E.rev].f && dv < dis[v]) {
                dis[v] = dv;
                if(!flag[v]) {
                    flag[v] = true;
                    if(b == e || dis[q[b]] <= dis[v]) {
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
    return dis[SS] != inf;
}
int now[size];
int DFS(int u, int f) {
    if(u == TT || f == 0)
        return f;
    flag[u] = true;
    int res = 0, k;
    for(int& i = now[u]; i < G[u].size(); ++i) {
        Edge& E = G[u][i];
        int v = E.to;
        if(E.f && !flag[v] && dis[v] + E.w == dis[u] &&
           (k = DFS(v, std::min(f, E.f)))) {
            E.f -= k, G[v][E.rev].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    flag[u] = false;
    if(!res)
        dis[u] = -1;
    return res;
}
Int64 MCMF(int n) {
    Int64 res = 0;
    while(SPFA(n)) {
        memset(now + 1, 0, sizeof(int) * n);
        int sf = 0, cf, cd = dis[SS];
        while((cf = DFS(SS, inf)))
            sf += cf;
        res += asInt64(sf) * cd;
    }
    return res;
}
int main() {
    int n, P, M, F, N, S, R;
    scanf("%d%d%d%d%d%d", &n, &P, &M, &F, &N, &S);
    SS = n * 2 + 1;
    TT = SS + 1;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &R);
        addEdge(SS, i, inf, P);
        addEdge(i, TT, R, 0);
        int ri = i + n;
        addEdge(SS, ri, R, 0);
        if(i + M <= n)
            addEdge(ri, i + M, inf, F);
        if(i + N <= n)
            addEdge(ri, i + N, inf, S);
        if(i + 1 <= n)
            addEdge(ri, ri + 1, inf, 0);
    }
    printf("%lld\n", MCMF(TT));
    return 0;
}
