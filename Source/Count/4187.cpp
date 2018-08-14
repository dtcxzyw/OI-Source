#include <cstdio>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 1000005, mod = 1000000007;
int powm(Int64 a, int k) {
    Int64 res = 1;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int dp[size];
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    dp[0] = 1;
    int cur = 0;
    for (int i = 1; i < k; ++i) {
        dp[i] = asInt64(dp[i - 1]) * m % mod;
        cur = add(cur, dp[i]);
    }
    Int64 fac = m - 1;
    int off = k - 1;
    for (int i = k; i <= n; ++i) {
        dp[i] = cur * fac % mod;
        cur = sub(add(cur, dp[i]), dp[i - off]);
    }
    printf("%d\n", sub(powm(m, n), dp[n]));
    return 0;
}
