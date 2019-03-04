#include <algorithm>
#include <cstdio>
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
const int size = 70000;
template <int esiz>
struct G {
    struct Edge {
        int to, nxt;
    } E[esiz];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
};
G<size * 2> A;
G<size> B;
int in[size], q[size], d[size], p[size][16], siz[size];
void DFS(int u) {
    siz[u] = 1;
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        if(v != p[u][0]) {
            DFS(v);
            siz[u] += siz[v];
        }
    }
}
int getLCA(int u, int v) {
    if(u == 0 || v == 0)
        return u | v;
    if(d[u] < d[v])
        std::swap(u, v);
    int delta = d[u] - d[v];
    for(int i = 0; i < 16; ++i)
        if(delta & (1 << i))
            u = p[u][i];
    if(u == v)
        return u;
    for(int i = 15; i >= 0; --i)
        if(p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    return p[u][0];
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i) {
        int k = read();
        while(k) {
            ++in[i];
            A.addEdge(k, i);
            k = read();
        }
    }
    int qcnt = 0, rt = n + 1;
    for(int i = 1; i <= n; ++i)
        if(!in[i]) {
            B.addEdge(rt, i);
            p[i][0] = rt;
            q[++qcnt] = i;
            d[i] = 1;
        }
    for(int i = 1; i <= qcnt; ++i) {
        int u = q[i];
        for(int j = A.last[u]; j; j = A.E[j].nxt) {
            int v = A.E[j].to;
            p[v][0] = getLCA(p[v][0], u);
            if(--in[v] == 0) {
                B.addEdge(p[v][0], v);
                d[v] = d[p[v][0]] + 1;
                for(int k = 1; k < 16; ++k)
                    p[v][k] = p[p[v][k - 1]][k - 1];
                q[++qcnt] = v;
            }
        }
    }
    DFS(rt);
    for(int i = 1; i <= n; ++i)
        printf("%d\n", siz[i] - 1);
    return 0;
}
