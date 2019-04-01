#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int size = 1005;
struct Edge {
    int to, nxt, w;
} E[size * 6];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int q[size], b = 0, e = 0;
bool flag[size];
void push(int u) {
    q[e++] = u;
    flag[u] = true;
    if(e == size)
        e = 0;
}
void SSSP(int* S) {
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            int dv = S[u] + E[i].w;
            if(dv < S[v]) {
                S[v] = dv;
                if(!flag[v])
                    push(v);
            }
        }
    }
}
const int inf = 0x3f3f3f3f;
int dp[1 << 10][size], F[1 << 10], G[1 << 10], C[10];
int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    for(int i = 1; i <= m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    int end = 1 << p;
    memset(dp, 0x3f, sizeof(dp));
    for(int i = 0; i < p; ++i) {
        int d;
        scanf("%d%d", &C[i], &d);
        dp[1 << i][d] = 0;
    }
    for(int s = 0; s < end; ++s) {
        for(int t = s & (s - 1); t; t = s & (t - 1))
            for(int i = 1; i <= n; ++i)
                dp[s][i] = std::min(
                    dp[s][i], dp[s ^ t][i] + dp[t][i]);
        for(int i = 1; i <= n; ++i)
            if(dp[s][i] != inf)
                push(i);
        SSSP(dp[s]);
    }
    memset(F, 0x3f, sizeof(F));
    for(int s = 0; s < end; ++s) {
        int res = inf;
        for(int i = 1; i <= n; ++i)
            res = std::min(res, dp[s][i]);
        for(int t = s; t; t = s & (t - 1))
            F[t] = std::min(F[t], res);
    }
    F[0] = 0;
    for(int i = 0; i < end; ++i) {
        int mask = 0;
        for(int j = 0; j < p; ++j)
            if(i & (1 << (C[j] - 1)))
                mask |= 1 << j;
        G[i] = F[mask];
        for(int j = i & (i - 1); j; j = i & (j - 1))
            G[i] = std::min(G[i], G[j] + G[i ^ j]);
    }
    printf("%d\n", G[end - 1]);
    return 0;
}
