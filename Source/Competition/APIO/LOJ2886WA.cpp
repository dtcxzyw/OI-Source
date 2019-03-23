#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 2005;
typedef long long Int64;
Int64 Y[size], S[size], dp[size][size];
Int64 solve(int n, int A, int B) {
    for(int i = 1; i <= n; ++i)
        S[i] = S[i - 1] + Y[i];
    memset(dp, 0x7f, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= B; ++j)
            for(int k = i - 1;
                k >= 0 && (S[i] - S[k]) < dp[i][j];
                --k)
                dp[i][j] =
                    std::min(dp[i][j], dp[k][j - 1] |
                                 (S[i] - S[k]));
    Int64 res = 1LL << 62;
    for(int i = A; i <= B; ++i)
        res = std::min(res, dp[n][i]);
    return res;
}
int main() {
    int n, A, B;
    scanf("%d%d%d", &n, &A, &B);
    for(int i = 1; i <= n; ++i)
        scanf("%lld", &Y[i]);
    Int64 resA = solve(n, A, B);
    std::reverse(Y + 1, Y + n + 1);
    Int64 resB = solve(n, A, B);
    printf("%lld\n", std::min(resA, resB));
    return 0;
}
