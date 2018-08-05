#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
const int size = 105, S = 0;
int T;
struct Edge {
    int to, nxt, f;
} E[2 * 55 * 55];
int last[size] = {}, cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
const int inf = 1 << 30;
int d[size], q[size];
bool BFS(int siz) {
    memset(d, 0, sizeof(int) * siz);
    int b = 0, e = 1;
    q[0] = S;
    d[S] = 1;
    while (b != e) {
        int u = q[b++];
        for (int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if (E[i].f && d[v] == 0) {
                d[v] = d[u] + 1;
                q[e++] = v;
            }
        }
    }
    return d[T];
}
int now[size];
int DFS(int u, int f) {
    if (u == T || f == 0) return f;
    int res = 0, k;
    for (int &i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if (d[v] == d[u] + 1 && (k = DFS(v, std::min(E[i].f, f)))) {
            E[i].f -= k;
            E[i ^ 1].f += k;
            f -= k;
            res += k;
            if (f == 0) break;
        }
    }
    if (res == 0) d[u] = -1;
    return res;
}
int dinic(int siz) {
    int res = 0;
    while (BFS(siz)) {
        memcpy(now, last, sizeof(int) * siz);
        res += DFS(S, inf);
    }
    return res;
}
char buf[10000];
int main() {
    int n, m;
    std::cin >> n >> m;
    T = n + m + 1;
    int tot = 0;
    for (int i = 1; i <= n; ++i) {
        int w;
        std::cin >> w;
        tot += w;
        addEdge(S, i, w);
        //Thanks
        std::cin.getline(buf, 10000);
        int ulen = 0, tool;
        while (sscanf(buf + ulen, "%d", &tool) == 1) {
            addEdge(i, tool + n, inf);
            while (tool) {
                tool /= 10;
                ulen++;
            }
            ulen++;
        }
    }
    for (int i = 1; i <= m; ++i) {
        int w;
        std::cin >> w;
        addEdge(i + n, T, w);
    }
    int res = tot - dinic(T + 1);
    for (int i = 1; i <= n; ++i)
        if (d[i] > 0)
            std::cout << i << ' ';
    std::cout << std::endl;
    for (int i = 1; i <= m; ++i)
        if (d[i + n] > 0)
            std::cout << i << ' ';
    std::cout << std::endl;
    std::cout << res << std::endl;
    return 0;
}
