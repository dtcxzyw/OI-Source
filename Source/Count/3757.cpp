#include <cstdio>
#include <cstring>
const int size = 105, mod = 1000000007;
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
typedef long long Int64;
Int64 C[size][size], dp[size][size], tmp[size];
char buf[size];
void move(int u, int& su, int v, int sv) {
    int tot = su + sv, beg, end;
    memset(tmp + 1, 0, sizeof(Int64) * tot);
    for(int i = 1; i <= su; ++i)
        for(int j = 1; j <= sv; ++j) {
            if(buf[v] == '<')
                beg = 0, end = j;
            else
                beg = j, end = sv + 1;
            Int64 A = dp[u][i] * dp[v][j] % mod;
            for(int k = beg; k < end; ++k) {
                int nrk = i + k;
                Int64 B = C[nrk - 1][k] *
                    C[tot - nrk][sv - k] % mod;
                tmp[nrk] = (tmp[nrk] + A * B) % mod;
            }
        }
    memcpy(dp[u] + 1, tmp + 1, sizeof(Int64) * tot);
    su += sv;
}
int DFS(int u) {
    int siz = 1;
    dp[u][1] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        int sv = DFS(v);
        move(u, siz, v, sv);
    }
    return siz;
}
int main() {
    int n;
    scanf("%d%s", &n, buf + 2);
    C[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            C[i][j] =
                (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for(int i = 2; i <= n; ++i)
        addEdge(i >> 1, i);
    DFS(1);
    int res = 0;
    for(int i = 1; i <= n; ++i)
        res = (res + dp[1][i]) % mod;
    printf("%d\n", res);
    return 0;
}
