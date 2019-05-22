#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 2005;
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int n, k, nk;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 dp[size][size];
void CAS(Int64& a, Int64 b) {
    a = std::max(a, b);
}
int DFS(int u, int p) {
    int siz = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p)
            continue;
        int vsiz = DFS(v, u);
        siz += vsiz;
        int vend = std::min(vsiz, k);
        for(int j = 0; j <= vend; ++j) {
            int wc = vsiz - j;
            dp[v][j] += asInt64(E[i].w) *
                (j * (k - j) + wc * (nk - wc));
        }
        int end = std::min(siz, k),
            oend = std::min(siz - vsiz, k);
        for(int j = end; j >= 0; --j) {
            int fbeg = std::max(0, j - vend),
                fend = std::min(oend, j);
            for(int l = fend; l >= fbeg; --l)
                CAS(dp[u][j], dp[u][l] + dp[v][j - l]);
        }
    }
    return siz;
}
int main() {
    scanf("%d%d", &n, &k);
    nk = n - k;
    for(int i = 1; i < n; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    DFS(1, 0);
    printf("%lld\n", dp[1][k]);
    return 0;
}
