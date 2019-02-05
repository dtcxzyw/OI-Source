#include <cstdio>
int A[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };
int dp[205];
int main() {
    dp[0] = 1;
    for(int i = 0; i < 8; ++i)
        for(int j = A[i]; j <= 200; ++j)
            dp[j] += dp[j - A[i]];
    printf("%d\n", dp[200]);
    return 0;
}
