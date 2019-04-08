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
typedef long long Int64;
const int size = 100005;
Int64 sum[size], dp[size];
void solve(int l, int r, int b, int e) {
    if(l > r)
        return;
    int m = (l + r) >> 1, end = std::min(e, m - 1),
        tp = 0;
    Int64 dpv = -(1LL << 62);
    for(int i = b; i <= end; ++i) {
        Int64 cv = dp[i] + (sum[m] - sum[i]) * sum[i];
        if(cv > dpv)
            dpv = cv, tp = i;
    }
    solve(m + 1, r, tp, e);
    solve(l, m - 1, b, tp);
    dp[m] = dpv;
}
int main() {
    int n = read();
    int k = read() + 1;
    for(int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + read();
    memset(dp, 0xc0, sizeof(Int64) * (n + 1));
    dp[0] = 0;
    for(int i = 1; i <= k; ++i)
        solve(1, n, 0, n);
    printf("%lld\n", dp[n]);
    return 0;
}
