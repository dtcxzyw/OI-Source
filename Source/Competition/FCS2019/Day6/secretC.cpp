#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
typedef long double FT;
const int size = 505;
struct Edge {
    int to, nxt;
    FT f;
} E[size * 2 * 2 * 2];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, FT f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, FT f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
int S, T, d[size], gap[size], q[size];
void BFS() {
    q[0] = T, d[T] = 1, gap[1] = 1;
    int b = 0, e = 1;
    while(b < e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(!d[v]) {
                d[v] = d[u] + 1;
                ++gap[d[v]];
                q[e++] = v;
            }
        }
    }
}
const FT eps = 1e-10l;
int now[size];
FT DFS(int u, FT f) {
    if(u == T || f <= eps)
        return f;
    FT res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[u] == d[v] + 1 &&
           (k = DFS(v, std::min(f, E[i].f))) > eps) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f <= eps)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = T + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
FT ISAP() {
    BFS();
    memcpy(now + 1, last + 1, sizeof(int) * T);
    FT res = 0;
    while(d[S] <= T)
        res += DFS(S, 1e20);
    return res;
}
FT F[15];
int pid[55][15];
int main() {
    int n, m;
    std::cin >> n >> m;
    S = n * 10 + 1, T = S + 1;
    for(int i = 1; i <= 10; ++i) {
        int x;
        std::cin >> x >> F[i];
        F[i] = logl(F[i]);
    }
    for(int i = 1, cid = 0; i <= n; ++i)
        for(int j = 1; j <= 10; ++j)
            pid[i][j] = ++cid;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= 10; ++j) {
            FT x;
            std::cin >> x;
            addEdge(S, pid[i][j], logl(x));
        }
        for(int j = 1; j <= 10; ++j) {
            FT x;
            std::cin >> x;
            addEdge(pid[i][j], T, logl(x));
        }
    }
    for(int i = 1; i <= m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        int u = pid[a][c], v = pid[b][c];
        addEdge(u, v, F[c]);
        addEdge(v, u, F[c]);
    }
    std::cout.precision(5);
    std::cout << std::fixed << expl(ISAP())
              << std::endl;
    return 0;
}
