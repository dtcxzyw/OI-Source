#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 1605, inf = 0x3f3f3f3f;
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
int dis[size], q[size], S, T;
bool flag[size];
bool SPFA(int n) {
    memset(dis + 1, 0x3f, sizeof(int) * n);
    dis[T] = 0, q[0] = T, flag[T] = true;
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
    return dis[S] != inf;
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
        if(E.f && !flag[v] && dis[v] + E.w == dis[u] &&
           (k = DFS(v, std::min(f, E.f)))) {
            E.f -= k, G[v][E.rev].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    flag[u] = false;
    if(res == 0)
        dis[u] = -1;
    return res;
}
int MCMF(int n) {
    int res = 0;
    while(SPFA(n)) {
        memset(now + 1, 0, sizeof(int) * n);
        int sf = 0, cf, cd = dis[S];
        while((cf = DFS(S, inf)))
            sf += cf;
        res += sf * cd;
    }
    return res;
}
int main() {
    int n = read();
    int m = read();
    S = 2 * n + 1;
    T = S + 1;
    for(int i = 1; i <= n; ++i) {
        int A = read();
        addEdge(S, i, 1, A);
        addEdge(i, T, 1, 0);
        addEdge(S, i + n, 1, 0);
    }
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        int w = read();
        if(u > v)
            std::swap(u, v);
        addEdge(u + n, v, 1, w);
    }
    printf("%d\n", MCMF(T));
    return 0;
}
