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
Int64 sum[size], A[size], B[size];
int L[size];
std::pair<Int64, int> solve(int n, Int64 C) {
    int b = 0, e = 0;
    for(int i = 1; i <= n; ++i) {
        while(b + 1 <= e &&
              A[b] - A[b + 1] >=
                  2LL * sum[i] * (B[b] - B[b + 1]))
            ++b;
        Int64 dpv = A[b] - 2LL * sum[i] * B[b] +
            sum[i] * sum[i] + C;
        int cnt = L[b] + 1;
        if(i == n)
            return std::make_pair(dpv, cnt);
        Int64 base = dpv + sum[i] * sum[i];
        while(
            b + 1 <= e &&
            static_cast<long double>(A[e - 1] - A[e]) *
                    (B[e] - sum[i]) >=
                static_cast<long double>(A[e] - base) *
                    (B[e - 1] - B[e]))
            --e;
        ++e;
        A[e] = base, B[e] = sum[i], L[e] = cnt;
    }
    return std::make_pair(0LL, 0);
}
int main() {
    int n = read();
    int k = read() + 1;
    for(int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + read();
    const Int64 inf = 1LL << 60;
    Int64 l = 0, r = inf, ans = 0;
    while(l <= r) {
        Int64 m = (l + r) >> 1;
        std::pair<Int64, int> res = solve(n, m);
        if(res.second == k) {
            ans = res.first - m * k;
            break;
        }
        if(res.second < k)
            r = m - 1;
        else
            l = m + 1, ans = res.first - m * k;
    }
    printf("%lld\n", (sum[n] * sum[n] - ans) / 2);
    return 0;
}
