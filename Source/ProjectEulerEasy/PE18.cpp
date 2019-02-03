#include <algorithm>
#include <cstdio>
int A[40][40], B[40][40];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            scanf("%d", &A[i][j]);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= i; ++j) {
            B[i][j] = std::max(B[i - 1][j - 1],
                               B[i - 1][j]) +
                A[i][j];
        }
    }
    int res = 0;
    for(int i = 1; i <= n; ++i)
        res = std::max(res, B[n][i]);
    printf("%d\n", res);
    return 0;
}
