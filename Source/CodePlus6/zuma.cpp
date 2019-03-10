#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 105;
int A[size], dp[size][size][size];
void CAS(int& a, int b) {
    a = std::max(a, b);
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &A[i]);
    int minl, maxl;
    scanf("%d%d", &minl, &maxl);
    memset(dp, 0xc0, sizeof(dp));
    dp[0][0][0] = 0;
    for(int i = 1; i <= n; ++i) {
        int c = A[i];
        for(int j = 0; j <= n; ++j) {
            if(j == c) {
                for(int k = 0; k < i; ++k)
                    CAS(dp[i][c][k + 1],
                        dp[i - 1][c][k]);
            } else {
                for(int k = 0; k <= i; ++k)
                    CAS(dp[i][c][1], dp[i - 1][j][k]);
            }
        }
        for(int j = 1; j <= i && j <= maxl; ++j) {
            if(A[i - j + 1] != c)
                break;
            if(j >= minl) {
                int src = i - j;
                for(int k = 1; k <= n; ++k)
                    for(int l = 1; l < i; ++l)
                        CAS(dp[i][k][l],
                            dp[src][k][l] + j * j);
            }
        }
    }
    int res = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            CAS(res, dp[n][i][j]);
    printf("%d\n", res);
    return 0;
}
