#include <algorithm>
#include <cstdio>
#include <vector>
const int maxn = 55, maxm = 4005;
struct Info {
    int a, b, c;
} A[maxm];
int dp[maxn][maxn][maxm], trans[maxn][maxn][maxm][2],
    B[maxm], siz, C[maxn][maxm], D[maxn];
int find(int x) {
    return std::lower_bound(B + 1, B + siz + 1, x) - B;
}
void DFS(int l, int r, int k) {
    if(l <= r) {
        int w = trans[l][r][k][1];
        int p = trans[l][r][w][0];
        D[p] = B[w];
        DFS(l, p - 1, w);
        DFS(p + 1, r, w);
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &A[i].a, &A[i].b, &A[i].c);
        B[i] = A[i].c;
    }
    std::sort(B + 1, B + m + 1);
    siz = std::unique(B + 1, B + m + 1) - (B + 1);
    for(int i = 1; i <= m; ++i)
        A[i].c = find(A[i].c);
    for(int l = n; l >= 1; --l)
        for(int r = l; r <= n; ++r) {
            for(int i = l; i <= r; ++i)
                for(int j = 1; j <= m; ++j)
                    C[i][j] = 0;
            int mid = 0;
            for(int i = 1; i <= m; ++i)
                if(l <= A[i].a && A[i].b <= r) {
                    int id = A[i].c;
                    mid = std::max(mid, id);
                    for(int j = A[i].a; j <= A[i].b;
                        ++j)
                        ++C[j][id];
                }
            for(int i = l; i <= r; ++i)
                for(int j = mid; j >= 1; --j)
                    C[i][j] += C[i][j + 1];
            for(int k = siz; k > mid; --k)
                trans[l][r][k][0] = l,
                trans[l][r][k][1] = k;
            for(int k = mid; k >= 1; --k) {
                int maxv = 0;
                for(int i = l; i <= r; ++i) {
                    int cur = dp[l][i - 1][k] +
                        dp[i + 1][r][k] +
                        B[k] * C[i][k];
                    if(cur >= maxv)
                        maxv = cur,
                        trans[l][r][k][0] = i;
                }
                if(maxv >= dp[l][r][k + 1])
                    dp[l][r][k] = maxv,
                    trans[l][r][k][1] = k;
                else
                    dp[l][r][k] = dp[l][r][k + 1],
                    trans[l][r][k][1] =
                        trans[l][r][k + 1][1];
            }
        }
    DFS(1, n, 1);
    printf("%d\n", dp[1][n][1]);
    for(int i = 1; i <= n; ++i)
        printf("%d ", D[i]);
    return 0;
}
