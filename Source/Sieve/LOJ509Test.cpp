#include <cmath>
#include <cstdio>
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int cnt = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            long long mul = 1LL * i * j;
            long long val = sqrt(mul);
            if(val * val == mul)
                ++cnt;
        }
        if(i % 100 == 0)
            printf("%d\n", i);
    }
    printf("%d\n", cnt);
    return 0;
}
