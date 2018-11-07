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
const int size = 855;
namespace NetworkFlow {
    struct Edge {
        int to, nxt, f;
    } E[17005];
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
int A[size], c[size], ccnt = 0;
void buildGHTImpl(int l, int r) {
    if(l == r)
        return;
    int s = A[l], t = A[r];
    c[ccnt++] = NetworkFlow::dinic(s, t);
    int wp = l;
    for(int i = l; i <= r; ++i)
        if(NetworkFlow::query(A[i]))
            std::swap(A[wp++], A[i]);
    buildGHTImpl(l, wp - 1);
    buildGHTImpl(wp, r);
}
void buildGHT(int n) {
    NetworkFlow::siz = n;
    for(int i = 1; i <= n; ++i)
        A[i] = i;
    buildGHTImpl(1, n);
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
    std::sort(c, c + ccnt);
    ccnt = std::unique(c, c + ccnt) - c;
    printf("%d\n", ccnt);
    return 0;
}
