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
const int size = 100005;
typedef long long Int64;
const Int64 inf = 1LL << 60;
int cnt[size], A[size];
Int64 cur, dp[2][size], *f, *g;
void solve(int l, int r, int b, int e) {
    if(l > r)
        return;
    int m = (l + r) >> 1, end = std::min(e, m), tp;
    for(int i = l; i <= m; ++i)
        cur += cnt[A[i]]++;
    Int64 minv = inf;
    for(int i = b; i <= end; ++i) {
        Int64 val = cur + f[i - 1];
        if(val < minv)
            minv = val, tp = i;
        cur -= --cnt[A[i]];
    }
    g[m] = minv;
    for(int i = b; i <= end; ++i)
        cur += cnt[A[i]]++;
    for(int i = l; i <= m; ++i)
        cur -= --cnt[A[i]];
    solve(l, m - 1, b, tp);
    int sa = m - l + 1 + tp - b,
        sb = l - b + m - tp + 1;
    if(sa < sb) {
        for(int i = l; i <= m; ++i)
            cur += cnt[A[i]]++;
        for(int i = b; i < tp; ++i)
            cur -= --cnt[A[i]];
    } else {
        for(int i = b; i < l; ++i)
            --cnt[A[i]];
        cur = 0;
        for(int i = tp; i <= m; ++i)
            cur += cnt[A[i]]++;
    }
    solve(m + 1, r, tp, e);
    if(sa < sb) {
        for(int i = b; i < tp; ++i)
            cur += cnt[A[i]]++;
        for(int i = l; i <= m; ++i)
            cur -= --cnt[A[i]];
    } else {
        for(int i = tp; i <= m; ++i)
            --cnt[A[i]];
        cur = 0;
        for(int i = b; i < l; ++i)
            cur += cnt[A[i]]++;
    }
}
int main() {
    int n = read();
    int k = read();
    f = dp[0], g = dp[1], cur = 0;
    for(int i = 1; i <= n; ++i) {
        A[i] = read();
        cur += cnt[A[i]]++;
        f[i] = cur;
    }
    cur = 0;
    memset(cnt + 1, 0, sizeof(int) * n);
    for(int j = 2; j < k; ++j) {
        solve(1, n, 1, n);
        std::swap(f, g);
    }
    Int64 res = inf;
    for(int i = n; i >= 1; --i) {
        cur += cnt[A[i]]++;
        res = std::min(res, f[i - 1] + cur);
    }
    printf("%lld\n", res);
    return 0;
}
