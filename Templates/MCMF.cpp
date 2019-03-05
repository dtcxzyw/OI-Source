#include <cstdio>
#include <cstring>
#include <vector>
const int size = 405, inf = 2147483647;
struct Edge {
    int v, rev, f, w;
    Edge(int v, int rev, int f, int w)
        : v(v), rev(rev), f(f), w(w) {}
};
std::vector<Edge> G[size];
void addEdge(int u, int v, int f, int w) {
    int urev = G[u].size(), vrev = G[v].size();
    G[u].emplace_back(v, vrev, f, w);
    G[v].emplace_back(u, urev, 0, -w);
}
int dis[size], q[size], n;
bool flag[size];
bool SPFA() {
    memset(dis + 1, 0x3f, sizeof(int) * n);
    dis[n] = 0;
    int b = 0, e = 1;
    q[0] = n, flag[n] = true;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(auto& E : G[u]) {
            int v = E.v, cd = dis[u] - E.w;
            if(G[v][E.rev].f && cd < dis[v]) {
                dis[v] = cd;
                if(!flag[v]) {
                    flag[v] = true;
                    if(b == e ||
                       dis[q[b]] + 30 <= dis[v]) {
                        q[e++] = v;
                        if(e == size)
                            e = 0;
                    } else {
                        --b;
                        if(b == -1)
                            b = size - 1;
                        q[b] = v;
                    }
                }
            }
        }
    }
    return dis[1] != 0x3f3f3f3f;
}
int now[size];
int mini(int a, int b) {
    return a < b ? a : b;
}
int DFS(int u, int f) {
    if(u == n || f == 0)
        return f;
    flag[u] = true;
    int res = 0, k;
    for(int& i = now[u]; i < G[u].size(); ++i) {
        Edge& E = G[u][i];
        int v = E.v;
        if(E.f && !flag[v] && dis[v] + E.w == dis[u] &&
           (k = DFS(v, mini(f, E.f)))) {
            E.f -= k, G[v][E.rev].f += k;
            f -= k, res += k;
            if(f == 0)
                break;
        }
    }
    flag[u] = false;
    if(!res)
        dis[u] = -1;
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
    int maxF = 0, minW = 0;
    while(SPFA()) {
        memset(now + 1, 0, sizeof(int) * n);
        int f, sf = 0, cd = dis[1];
        while((f = DFS(1, inf)))
            sf += f;
        maxF += sf, minW += sf * cd;
    }
    printf("%d %d\n", maxF, minW);
    return 0;
}
