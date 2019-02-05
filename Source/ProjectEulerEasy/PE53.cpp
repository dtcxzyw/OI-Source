#include <algorithm>
#include <cstdio>
int C[105][105];
int main() {
    int n, res = 0;
    scanf("%d", &n);
    C[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j) {
            C[i][j] =
                std::min(1 << 20, C[i - 1][j - 1] +
                             C[i - 1][j]);
            res += C[i][j] > 1000000;
        }
    }
    printf("%d\n", res);
    return 0;
}
