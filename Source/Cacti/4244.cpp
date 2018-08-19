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
const int size = 50005;
struct Edge {
    int to, nxt;
} E[size << 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
const int hsiz = size + (size >> 1);
int dp[size], q[hsiz], rf[hsiz], d[size], p[size], ans = 0;
void solveRing(int u, int v) {
    int cnt = d[v] - d[u] + 1;
    int pos = cnt;
    for(int i = v; i != u; i = p[i])
        rf[pos--] = dp[i];
    rf[1] = dp[u];
    int hl = cnt >> 1;
    int end = cnt + hl;
    for(int i = 1; i <= hl; ++i)
        rf[i + cnt] = rf[i];
    int b = 1, e = 1;
    q[b] = 1;
    for(int i = 2; i <= end; ++i) {
        if(i - q[b] > hl)
            ++b;
        ans = std::max(ans, rf[i] + rf[q[b]] + i - q[b]);
        while(b <= e && rf[i] - i >= rf[q[e]] - q[e])
            --e;
        q[++e] = i;
    }
    for(int i = 2; i <= cnt; ++i)
        dp[u] = std::max(dp[u], rf[i] + std::min(i - 1, cnt - i + 1));
}
int dfn[size], low[size], icnt = 0;
void DFS(int u) {
    dfn[u] = low[u] = ++icnt;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p[u])
            continue;
        if(!dfn[v]) {
            p[v] = u;
            d[v] = d[u] + 1;
            DFS(v);
        }
        low[u] = std::min(low[u], low[v]);
        if(low[v] > dfn[u]) {
            ans = std::max(ans, dp[u] + dp[v] + 1);
            dp[u] = std::max(dp[u], dp[v] + 1);
        }
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(p[v] != u && dfn[u] < dfn[v])
            solveRing(u, v);
    }
}
int main() {
    int n = read();
    int m = read();
    while(m--) {
        int k = read();
        int u = read();
        while(--k) {
            int v = read();
            addEdge(u, v);
            addEdge(v, u);
            u = v;
        }
    }
    DFS(1);
    printf("%d\n", ans);
    return 0;
}
