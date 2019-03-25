#include <algorithm>
#include <cstdio>
typedef long long Int64;
const int size = 1000005;
int A[size], dp[size], flag[size];
Int64 S[size];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i)
        scanf("%d", &A[i]);
    int minv = 1 << 30;
    for(int i = m - 1; i >= 0; --i)
        minv = std::min(minv + 1, A[i]);
    for(int i = m - 1; i >= 0; --i) {
        minv = std::min(minv + 1, A[i]);
        dp[i] = minv;
    }
    int p = 0, cnt = 0;
    while(!flag[p]) {
        flag[p] = ++cnt;
        S[cnt] = S[cnt - 1] + dp[p];
        p = (p + dp[p]) % m;
    }
    Int64 res = 0;
    if(n < flag[p])
        res = S[n];
    else {
        res = S[flag[p] - 1];
        Int64 rlen = S[cnt] - S[flag[p] - 1],
              rcnt = cnt - (flag[p] - 1);
        n -= flag[p] - 1;
        res += rlen * (n / rcnt) +
            S[flag[p] - 1 + n % rcnt] - S[flag[p] - 1];
    }
    printf("%lld\n", res);
    return 0;
}
