// ERROR
#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 125, maxe = 2005, inf = 1 << 30;
struct Edge {
    int to, nxt, f;
} E[maxe];
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
int d[size], q[size], S, T;
bool BFS() {
    memset(d, -1, sizeof(d));
    d[S] = 0, q[0] = S;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f && d[v] == -1) {
                d[v] = d[u] + 1;
                if(v == T)
                    return true;
                q[e++] = v;
            }
        }
    }
    return false;
}
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] == d[u] + 1 &&
           (k = DFS(v, std::min(f, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            f -= k, res += k;
            if(f == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
int X[size];
bool dinic(int end, int& t, int& w) {
    int res = 0;
    while(BFS()) {
        memcpy(now, last, sizeof(now));
        int val = DFS(S, inf);
        if(val == inf)
            return false;
        res += val;
        if(res > w)
            return false;
    }
    int minv = w / res, qcnt = 0;
    for(int i = 2; i <= end; i += 2) {
        int u = E[i ^ 1].to;
        int v = E[i].to;
        if(d[u] != -1 && d[v] == -1) {
            minv = std::min(minv, X[u]);
            q[++qcnt] = i;
        }
    }
    t -= minv, w -= minv * res;
    for(int i = 1; i <= qcnt; ++i) {
        int e = q[i];
        int u = E[e ^ 1].to;
        X[u] -= minv;
        if(X[u] == 0)
            E[e ^ 1].f = inf;
    }
    for(int i = 2; i <= cnt; i += 2) {
        int sum = E[i].f + E[i ^ 1].f;
        E[i].f = sum, E[i ^ 1].f = 0;
    }
    return true;
}
int in[size], out[size];
int main() {
    int n, m, w;
    scanf("%d%d%d", &n, &m, &w);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &X[i]);
    for(int i = 1; i <= n; ++i) {
        int C;
        scanf("%d", &C);
        addEdge(i, i + n, C);
    }
    int end = cnt;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        ++in[v], ++out[u];
        addEdge(u + n, v, inf);
    }
    S = 2 * n + 1;
    T = S + 1;
    for(int i = 1; i <= n; ++i) {
        if(in[i] == 0)
            addEdge(S, i, inf);
        if(out[i] == 0)
            addEdge(i + n, T, inf);
    }
    int t = 6;
    while(dinic(end, t, w))
        ;
    printf("%d\n", t);
    return 0;
}
