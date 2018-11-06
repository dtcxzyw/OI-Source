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
const int size = 505;
namespace NetworkFlow {
    struct Edge {
        int to, nxt, f;
    } E[3005];
    int last[size], cnt = 1;
    void addEdge(int u, int v, int f) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u],
        E[cnt].f = f;
        last[u] = cnt;
    }
    int S, T, q[size], d[size], siz;
    bool BFS() {
        memset(d + 1, -1, sizeof(int) * siz);
        int b = 0, e = 1;
        q[b] = S, d[S] = 0;
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
    int DFS(int u, int mf) {
        if(mf == 0 || u == T)
            return mf;
        int res = 0, k;
        for(int& i = now[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(d[v] == d[u] + 1 &&
               (k = DFS(v, std::min(mf, E[i].f)))) {
                E[i].f -= k, E[i ^ 1].f += k;
                mf -= k, res += k;
                if(mf == 0)
                    break;
            }
        }
        if(res == 0)
            d[u] = -1;
        return res;
    }
    int dinic(int s, int t) {
        for(int i = 2; i <= cnt; i += 2) {
            int tot = E[i].f + E[i ^ 1].f;
            E[i].f = E[i ^ 1].f = tot >> 1;
        }
        S = s, T = t;
        int res = 0;
        while(BFS()) {
            memcpy(now + 1, last + 1,
                   sizeof(int) * siz);
            res += DFS(S, 1 << 30);
        }
        return res;
    }
    bool query(int u) {
        return d[u] == -1;
    }
}
namespace GHT {
    struct Edge {
        int to, nxt, w;
    } E[size * 2];
    int last[size], cnt = 0;
    void addEdge(int u, int v, int w) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u],
        E[cnt].w = w;
        last[u] = cnt;
    }
    int p[size][8], d[size], k[size][8];
    void DFS(int u) {
        for(int i = 1; i < 8; ++i) {
            int pp = p[u][i - 1];
            p[u][i] = p[pp][i - 1];
            k[u][i] =
                std::min(k[u][i - 1], k[pp][i - 1]);
        }
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(p[u][0] != v) {
                p[v][0] = u;
                k[v][0] = E[i].w;
                d[v] = d[u] + 1;
                DFS(v);
            }
        }
    }
    int query(int u, int v) {
        int res = 1 << 30;
        if(d[u] < d[v])
            std::swap(u, v);
        int delta = d[u] - d[v];
        for(int i = 0; i < 8; ++i)
            if(delta & (1 << i)) {
                res = std::min(res, k[u][i]);
                u = p[u][i];
            }
        if(u == v)
            return res;
        for(int i = 7; i >= 0; --i)
            if(p[u][i] != p[v][i]) {
                res = std::min(
                    res, std::min(k[u][i], k[v][i]));
                u = p[u][i], v = p[v][i];
            }
        return std::min(res,
                        std::min(k[u][0], k[v][0]));
    }
}
int A[size];
void buildGHTImpl(int l, int r) {
    if(l == r)
        return;
    int s = A[l], t = A[r];
    int w = NetworkFlow::dinic(s, t);
    int wp = l;
    for(int i = l; i <= r; ++i)
        if(NetworkFlow::query(A[i]))
            std::swap(A[wp++], A[i]);
    GHT::addEdge(s, t, w);
    GHT::addEdge(t, s, w);
    buildGHTImpl(l, wp - 1);
    buildGHTImpl(wp, r);
}
void buildGHT(int n) {
    NetworkFlow::siz = n;
    for(int i = 1; i <= n; ++i)
        A[i] = i;
    buildGHTImpl(1, n);
    srand(19260817);
    GHT::DFS(rand() % n + 1);
}
int main() {
    int n = read();
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        NetworkFlow::addEdge(u, v, w);
        NetworkFlow::addEdge(v, u, w);
    }
    buildGHT(n);
    int q = read();
    while(q--)
        printf("%d\n", GHT::query(read(), read()));
    return 0;
}
