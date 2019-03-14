#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 4005;
int A[size][size], B[size][size], dp[2][size], *F, *G;
void solve(int l, int r, int b, int e) {
    if(l > r)
        return;
    int m = (l + r) >> 1, end = std::min(e, m - 1);
    int dpv = 1 << 30, tp;
    for(int i = b; i <= end; ++i) {
        int cv = F[i] + B[i + 1][m];
        if(cv < dpv)
            dpv = cv, tp = i;
    }
    G[m] = dpv;
    solve(l, m - 1, b, tp);
    solve(m + 1, r, tp, e);
}
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &A[i][j]);
            A[i][j] += A[i][j - 1];
        }
    for(int i = 1; i <= n; ++i) {
        for(int j = i; j <= n; ++j)
            B[i][j] =
                B[i][j - 1] + A[j][j] - A[j][i - 1];
    }
    memset(dp, 0x3f, sizeof(dp));
    F = dp[0], G = dp[1];
    G[0] = 0;
    for(int i = 1; i <= k; ++i) {
        std::swap(F, G);
        solve(1, n, 0, n);
    }
    printf("%d\n", G[n]);
    return 0;
}
