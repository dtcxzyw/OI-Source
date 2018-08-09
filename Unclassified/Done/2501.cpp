#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
int iabs(int x) {
    return x >= 0 ? x : -x;
}
typedef long long Int64;
const int size = 35005;
int A[size], dp[size], f[size];
Int64 g[size];
struct Edge {
    int to, nxt;
} E[size];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i)
        A[i] = read() - i;
    A[++n] = 1 << 30;
    int len = 0;
    f[0] = 0;
    A[0] = dp[0] = -(1 << 30);
    for (int i = 1; i <= n; ++i) {
        int pos = std::upper_bound(dp, dp + len + 1, A[i]) - dp;
        dp[pos] = A[i];
        f[i] = pos;
        if (pos > len) len = pos;
    }
    printf("%d\n", n - len);
    for (int i = n; i >= 0; --i)
        addEdge(f[i], i);
    g[0] = 0;
    for (int i = 1; i <= n; ++i) {
        Int64 res = 1LL << 60;
        for (int j = last[f[i] - 1]; j; j = E[j].nxt) {
            int s = E[j].to;
            if (s > i) break;
            if (A[s] > A[i]) continue;
            Int64 sri = 0, minv = 1LL << 60, cur = 0;
            for (int k = s; k <= i; ++k) {
                int dl = iabs(A[k] - A[s]);
                int dr = iabs(A[k] - A[i]);
                sri += dr;
                cur += dl - dr;
                minv = std::min(minv, cur);
            }
            res = std::min(res, g[s] + sri + minv);
        }
        g[i] = res;
    }
    printf("%lld\n", g[n]);
    return 0;
}
