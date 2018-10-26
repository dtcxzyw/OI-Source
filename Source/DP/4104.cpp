#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 10005;
int p;
int add(int a, int b) {
    a += b;
    return a < p ? a : a - p;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + p;
}
int dp[11][size * 10];
int foo() {
    int n, k;
    scanf("%d%d%d", &n, &k, &p);
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i = 1; i <= k; ++i) {
        int end = n * i;
        for(int j = i; j <= end; ++j) {
            dp[i][j] =
                add(dp[i][j - i], dp[i - 1][j - i]);
            if(j > n)
                dp[i][j] = sub(dp[i][j],
                               dp[i - 1][j - n - 1]);
        }
    }
    int res = 0;
    for(int t = 1; t <= 2; ++t, --k) {
        for(int i = 0; i * 2 <= k; ++i) {
            long long cur = 0;
            for(int j = 0; j <= i * n; ++j)
                cur += dp[i][j] * dp[k - i][j];
            cur %= p;
            if(i * 2 != k)
                cur = add(cur, cur);
            res = add(res, cur);
        }
    }
    return res;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--)
        printf("%d\n", foo());
    return 0;
}
