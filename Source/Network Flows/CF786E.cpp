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
const int size = 20005, maxv = size * 20, inf = 1
    << 30;
int S, T;
namespace NetworkFlow {
    struct Edge {
        int to, nxt, f;
    } E[maxv * 4];
    int last[maxv], cnt = 1;
    void addEdgeImpl(int u, int v, int f) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u],
        E[cnt].f = f;
        last[u] = cnt;
    }
    void addEdge(int u, int v, int f) {
        addEdgeImpl(u, v, f);
        addEdgeImpl(v, u, 0);
    }
    int d[maxv], q[maxv], gap[maxv];
    void BFS() {
        int b = 0, e = 1;
        d[T] = 1, q[0] = T, gap[1] = 1;
        while(b != e) {
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
    int now[maxv];
    int aug(int u, int f) {
        if(u == T || f == 0)
            return f;
        int res = 0, k;
        for(int& i = now[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(d[v] + 1 == d[u] &&
               (k = aug(v, std::min(f, E[i].f)))) {
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
            res += aug(S, inf);
        return res;
    }
    bool col[maxv];
    void color() {
        int b = 0, e = 1;
        q[b] = S, col[S] = true;
        while(b != e) {
            int u = q[b++];
            for(int i = last[u]; i; i = E[i].nxt) {
                int v = E[i].to;
                if(E[i].f && !col[v]) {
                    col[v] = true;
                    q[e++] = v;
                }
            }
        }
    }
}
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 1;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int p[size][15], d[size], eid[size][15], tid[size],
    pcnt;
void DFS(int u) {
    for(int i = 1; i < 15; ++i) {
        p[u][i] = p[p[u][i - 1]][i - 1];
        eid[u][i] = ++pcnt;
        NetworkFlow::addEdge(eid[u][i], eid[u][i - 1],
                             inf);
        NetworkFlow::addEdge(
            eid[u][i], eid[p[u][i - 1]][i - 1], inf);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u][0]) {
            p[v][0] = u, d[v] = d[u] + 1;
            tid[v] = i;
            eid[v][0] = ++pcnt;
            DFS(v);
        }
    }
}
int getLCA(int u, int v) {
    if(d[u] < d[v])
        std::swap(u, v);
    int delta = d[u] - d[v];
    for(int i = 0; i < 15; ++i)
        if(delta & (1 << i))
            u = p[u][i];
    if(u == v)
        return u;
    for(int i = 14; i >= 0; --i)
        if(p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    return p[u][0];
}
void link(int u, int v, int x) {
    for(int i = 14; i >= 0; --i)
        if(d[p[u][i]] >= d[v]) {
            NetworkFlow::addEdge(x, eid[u][i], inf);
            u = p[u][i];
        }
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    pcnt = m;
    d[1] = 1;
    DFS(1);
    S = ++pcnt;
    T = ++pcnt;
    for(int i = 2; i <= n; ++i)
        NetworkFlow::addEdge(eid[i][0], T, 1);
    for(int i = 1; i <= m; ++i) {
        NetworkFlow::addEdge(S, i, 1);
        int u = read();
        int v = read();
        int lca = getLCA(u, v);
        link(u, lca, i);
        link(v, lca, i);
    }
    int res = NetworkFlow::ISAP();
    printf("%d\n", res);
    NetworkFlow::color();
    std::vector<int> L;
    for(int i = 1; i <= m; ++i)
        if(!NetworkFlow::col[i])
            L.push_back(i);
    printf("%d ", static_cast<int>(L.size()));
    for(int i = 0; i < L.size(); ++i)
        printf("%d ", L[i]);
    puts("");
    std::vector<int> R;
    for(int i = 2; i <= n; ++i)
        if(NetworkFlow::col[eid[i][0]])
            R.push_back(tid[i] >> 1);
    printf("%d ", static_cast<int>(R.size()));
    for(int i = 0; i < R.size(); ++i)
        printf("%d ", R[i]);
    puts("");
    return 0;
}
