#include <cstdio>
const int size = 1000005, mod = 1000000007;
long long f[size];
int main() {
    int n;
    scanf("%d", &n);
    f[1] = 1;
    for(int i = 2; i <= n; ++i)
        f[i] = (2 * f[i - 1] + f[i - 2]) % mod;
    printf("%lld\n", f[n]);
    return 0;
}
