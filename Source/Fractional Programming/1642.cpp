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
typedef double FT;
const int size = 105;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int A[size], B[size], m;
FT k, dp[size][size];
int DFS(int u, int p) {
    dp[u][1] = A[u] - B[u] * k;
    for(int i = 2; i <= m; ++i)
        dp[u][i] = -1e10;
    int csiz = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            int vsiz = DFS(v, u);
            for(int j = csiz; j >= 1; --j) {
                int end = std::min(vsiz, m - j);
                for(int k = 1; k <= end; ++k)
                    dp[u][j + k] =
                        std::max(dp[u][j + k],
                                 dp[u][j] + dp[v][k]);
            }
            csiz = std::min(m, csiz + vsiz);
        }
    }
    return csiz;
}
int main() {
    int n = read();
    m = n - read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i)
        B[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    FT l = 0.0, r = 1e4;
    while(r - l >= 1e-3) {
        k = (l + r) * 0.5;
        DFS(1, 0);
        bool flag = false;
        for(int i = 1; i <= n; ++i)
            if(dp[i][m] > -1e-10) {
                flag = true;
                break;
            }
        (flag ? l : r) = k;
    }
    printf("%.1lf\n", l);
    return 0;
}
