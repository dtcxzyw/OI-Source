#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 20005;
struct Edge {
    int to, nxt, f;
} E[size * 11 * 2 * 2];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
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
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[u] == d[v] + 1 &&
           (k = DFS(v, std::min(f, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f == 0)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = T + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP() {
    BFS();
    memcpy(now + 1, last + 1, sizeof(int) * T);
    int res = 0;
    while(d[S] <= T)
        res += DFS(S, 1 << 30);
    return res;
}
int main() {
    int n = read();
    int m = read();
    S = n + 1, T = S + 1;
    for(int i = 1; i <= n; ++i) {
        addEdge(S, i, read());
        addEdge(i, T, read());
    }
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    printf("%d\n", ISAP());
    return 0;
}
