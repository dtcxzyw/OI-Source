#include <cstdio>
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        int m, k;
        scanf("%d%d", &m, &k);
        printf("Case #%d: %.8lf\n", i,
               1.0 / (m * k + 1 + k));
    }
    return 0;
}
