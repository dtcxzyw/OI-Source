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
const int size = 100005, maxv = size * 2;
struct G {
    struct Edge {
        int to, nxt;
    } E[size * 4];
    int last[maxv], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} A, B;
int dfn[size], low[size], st[size], w[maxv],
    top = 0, icnt = 0, nsiz;
void DFS(int u) {
    dfn[u] = low[u] = ++icnt;
    w[u] = -1;
    st[++top] = u;
    for(int i = A.last[u]; i; i = A.E[i].nxt) {
        int v = A.E[i].to;
        if(dfn[v])
            low[u] = std::min(low[u], dfn[v]);
        else {
            DFS(v);
            low[u] = std::min(low[u], low[v]);
            if(dfn[u] <= low[v]) {
                int id = ++nsiz, p, csiz = 1;
                B.addEdge(u, id);
                do {
                    p = st[top--];
                    B.addEdge(id, p);
                    ++csiz;
                } while(p != v);
                w[id] = csiz;
            }
        }
    }
}
int n, tot;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 res = 0;
int calc(int u) {
    int siz = 0;
    Int64 base = w[u];
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        int vsiz = calc(v);
        res += base * vsiz * siz;
        siz += vsiz;
    }
    res += base * siz * (tot - (u <= n) - siz);
    return siz + (u <= n);
}
int main() {
    n = read();
    int m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        A.addEdge(u, v);
        A.addEdge(v, u);
    }
    nsiz = n;
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) {
            int base = icnt;
            DFS(i);
            tot = icnt - base;
            calc(i);
            res -= asInt64(tot) * (tot - 1);
        }
    printf("%lld\n", res * 2);
    return 0;
}
