// P1044
#include <cstdio>
int main() {
    int n;
    long long cur = 1;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        cur = cur * (4 * i - 2) / (i + 1);
    printf("%lld\n", cur);
    return 0;
}
