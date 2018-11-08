#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 100005, inf = 1 << 30;
namespace KruskalTree {
    const int siz2 = size * 2;
    struct Edge {
        int to, nxt;
    } E[siz2];
    int last[siz2], cnt = 0;
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
    int p[siz2][18], d[siz2];
    void DFS(int u) {
        for(int i = 1; i < 18; ++i)
            p[u][i] = p[p[u][i - 1]][i - 1];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            d[v] = d[u] + 1;
            p[v][0] = u;
            DFS(v);
        }
    }
    struct E {
        int u, v, w;
        bool operator<(const E& rhs) const {
            return w > rhs.w;
        }
    } A[siz2];
    int w[siz2], fa[siz2];
    int find(int u) {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }
    void read(int n, int m, int q) {
        for(int i = 0; i < m; ++i) {
            A[i].u = ::read();
            A[i].v = ::read();
            A[i].w = ::read();
        }
        for(int i = 1; i <= n; ++i)
            fa[i] = i;
        std::sort(A, A + m);
        int ecnt = n - 1, vcnt = n;
        if(q) {
            ecnt -= q - 1;
            int id = ++vcnt;
            fa[id] = id;
            w[id] = inf;
            while(q--) {
                int u = ::read();
                fa[u] = id;
                addEdge(id, u);
            }
        }
        for(int i = 0; i < m && ecnt; ++i) {
            int fu = find(A[i].u), fv = find(A[i].v);
            if(fu != fv) {
                int id = ++vcnt;
                fa[fu] = fa[fv] = fa[id] = id;
                w[id] = A[i].w;
                addEdge(id, fu);
                addEdge(id, fv);
                --ecnt;
            }
        }
        DFS(vcnt);
    }
    int getLCA(int u, int v) {
        if(d[u] < d[v])
            std::swap(u, v);
        int delta = d[u] - d[v];
        for(int i = 0; i < 18; ++i)
            if(delta & (1 << i))
                u = p[u][i];
        if(u == v)
            return u;
        for(int i = 17; i >= 0; --i)
            if(p[u][i] != p[v][i])
                u = p[u][i], v = p[v][i];
        return p[u][0];
    }
    int getLimit(int u, int v) {
        return w[getLCA(u, v)];
    }
}
int S, T;
namespace NetworkFlow {
    struct Edge {
        int to, nxt, f;
    } E[4 * size];
    int last[size], cnt = 1;
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
    const int inf = 1 << 30;
    int d[size], q[size];
    bool BFS(int siz) {
        memset(d, 0, sizeof(int) * siz);
        int b = 0, e = 1;
        q[0] = S;
        d[S] = 1;
        while(b != e) {
            int u = q[b++];
            for(int i = last[u]; i; i = E[i].nxt) {
                int v = E[i].to;
                if(E[i].f && d[v] == 0) {
                    d[v] = d[u] + 1;
                    q[e++] = v;
                }
            }
        }
        return d[T];
    }
    int now[size];
    int DFS(int u, int f) {
        if(u == T || f == 0)
            return f;
        int res = 0, k;
        for(int& i = now[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(d[v] == d[u] + 1 &&
               (k = DFS(v, std::min(E[i].f, f)))) {
                E[i].f -= k;
                E[i ^ 1].f += k;
                f -= k;
                res += k;
                if(f == 0)
                    break;
            }
        }
        if(res == 0)
            d[u] = -1;
        return res;
    }
    void dinic(int siz) {
        while(BFS(siz)) {
            memcpy(now, last, sizeof(int) * siz);
            DFS(S, inf);
        }
    }
    int getFlow(int u) {
        return E[last[u] ^ 1].f;
    }
}
int id[size], b[size];
int main() {
    int n = read();
    int m = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        id[i] = read();
    for(int i = 1; i <= n; ++i)
        b[i] = read();
    KruskalTree::read(n, m, q);
    S = 0, T = n + 1;
    for(int i = 2; i <= n; ++i) {
        NetworkFlow::addEdge(
            id[i - 1], id[i],
            KruskalTree::getLimit(id[i - 1], id[i]));
    }
    for(int i = 1; i <= n; ++i) {
        int u = id[i];
        if(b[u] > 0)
            NetworkFlow::addEdge(S, u, b[u]);
        else
            NetworkFlow::addEdge(u, T, -b[u]);
    }
    NetworkFlow::dinic(T + 1);
    for(int i = 1; i <= n; ++i) {
        int u = id[i];
        if(b[u] < 0)
            printf("%d\n", NetworkFlow::getFlow(u));
    }
    return 0;
}
