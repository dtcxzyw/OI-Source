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
template <int maxv, int maxe>
struct G {
    struct Edge {
        int to, nxt;
    } E[maxe];
    int last[maxv], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
};
const int size = 100005, tsiz = size * 2;
G<size, 4 * size> g1;
G<tsiz, tsiz> g2;
int dfn[size], low[size], st[size], timeStamp = 0, top = 0, nsiz,
                                    w[tsiz], siz[tsiz];
void tarjan(int u) {
    dfn[u] = low[u] = ++timeStamp;
    st[++top] = u;
    siz[u] = 1;
    for(int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if(dfn[v])
            low[u] = std::min(low[u], dfn[v]);
        else {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
            if(dfn[u] <= low[v]) {
                int s = ++nsiz, p, old = top;
                g2.addEdge(u, s);
                do {
                    p = st[top--];
                    g2.addEdge(s, p);
                    siz[s] += siz[p];
                } while(p != v);
                w[s] = old - top + 1;
                siz[u] += siz[s];
            }
        }
    }
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
Int64 ans = 0;
int n, csiz;
Int64 DFS(int u) {
    Int64 mul = asInt64(csiz - siz[u]) * siz[u];
    Int64 cnt = mul;  // fa -> tree
    if(u <= n)
        cnt += csiz - 1;  // u begin
    for(int i = g2.last[u]; i; i = g2.E[i].nxt)
        cnt += DFS(g2.E[i].to);  // child -> fa
    ans += cnt * w[u];
    return mul;
}
int main() {
    n = read();
    nsiz = n;
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        g1.addEdge(u, v);
        g1.addEdge(v, u);
    }
    memset(w + 1, -1, sizeof(int) * n);
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) {
            tarjan(i);
            csiz = siz[i];
            DFS(i);
        }
    printf("%lld\n", ans);
    return 0;
}
