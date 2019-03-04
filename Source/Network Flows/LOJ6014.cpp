#include <algorithm>
#include <cstdio>
#include <vector>
const int size = 1010;
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
int dis[size], S, T;
void BFS(int n) {}
bool flag[size];
void DFS(int u, int f) {}
int MCMF(int n) {}
int L[size], R[size], P[size];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int pcnt = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", &L[i], &R[i]);
        if(L[i] > R[i])
            std::swap(L[i], R[i]);
        P[++pcnt] = L[i];
        P[++pcnt] = R[i];
    }
    std::sort(P + 1, P + pcnt + 1);
    pcnt = std::unique(P + 1, P + pcnt + 1) - (P + 1);

    return 0;
}
