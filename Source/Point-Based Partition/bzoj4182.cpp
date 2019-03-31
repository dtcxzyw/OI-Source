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
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int siz[size], msiz, tsiz, nrt;
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int cmsiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p || vis[v])
            continue;
        getRootImpl(v, u);
        siz[u] += siz[v];
        cmsiz = std::max(cmsiz, siz[v]);
    }
    cmsiz = std::max(cmsiz, tsiz - cmsiz);
    if(cmsiz < msiz)
        msiz = cmsiz, nrt = u;
}
int getRoot(int u, int usiz) {
    msiz = 1 << 30, tsiz = usiz;
    getRootImpl(u, 0);
    return nrt;
}
int W[size], C[size], D[size], dp[size][4005];
void update(int u, int k, int m) {
    int cw = W[u] * k, cv = C[u] * k;
    for(int i = m; i >= cv; --i)
        dp[u][i] =
            std::max(dp[u][i], dp[u][i - cv] + cw);
}
void DFS(int u, int p, int m) {
    if(m <= 0)
        return;
    for(int i = D[u], j = 1;; j <<= 1)
        if(j < i) {
            update(u, j, m);
            i -= j;
        } else {
            update(u, i, m);
            break;
        }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p || vis[v])
            continue;
        int end = m - C[v];
        for(int j = 0; j <= end; ++j)
            dp[v][j] = dp[u][j] + W[v];
        DFS(v, u, end);
        for(int j = C[v]; j <= m; ++j)
            dp[u][j] =
                std::max(dp[u][j], dp[v][j - C[v]]);
    }
}
int m, ans;
void solve(int u) {
    int end = m - C[u];
    for(int i = 0; i <= end; ++i)
        dp[u][i] = W[u];
    DFS(u, 0, m - C[u]);
    for(int i = 0; i <= end; ++i)
        ans = std::max(ans, dp[u][i]);
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(vis[v])
            continue;
        int crt = getRoot(v, siz[v]);
        divide(crt);
    }
}
int foo() {
    memset(last, 0, sizeof(last));
    memset(vis, 0, sizeof(vis));
    cnt = ans = 0;
    int n = read();
    m = read();
    for(int i = 1; i <= n; ++i)
        W[i] = read();
    for(int i = 1; i <= n; ++i)
        C[i] = read();
    for(int i = 1; i <= n; ++i)
        D[i] = read() - 1;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    divide(getRoot(1, n));
    return ans;
}
int main() {
    int t = read();
    for(int i = 1; i <= t; ++i)
        printf("%d\n", foo());
    return 0;
}
