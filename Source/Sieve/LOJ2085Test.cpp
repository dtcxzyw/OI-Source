#include <cstdio>
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    long long res = 0;
    for(int y = 1; y <= m; ++y) {
        if((y & 127) == 0)
            printf("%d\n", y);
        if(gcd(y, k) != 1)
            continue;
        for(int x = 1; x <= n; ++x)
            res += (gcd(x, y) == 1);
    }
    printf("%lld\n", res);
    return 0;
}
