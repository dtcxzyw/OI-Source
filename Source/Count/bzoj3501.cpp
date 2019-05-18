#include <cstdio>
typedef long long Int64;
Int64 powm(Int64 a, int k, int mod) {
    a %= mod;
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
const int size = 7285, mod = 999999599, phi = mod - 1;
int dp[2][size], b[size];
int add(int a, int b) {
    a += b;
    return a >= phi ? a - phi : a;
}
void pre() {
    dp[0][1] = b[0] = 1;
    for(int i = 1, o = 0, c = 1; i <= 7283;
        ++i, o ^= 1, c ^= 1) {
        b[i] = dp[c][1] = dp[o][i];
        for(int j = 1; j <= i; ++j)
            dp[c][j + 1] = add(dp[c][j], dp[o][j]);
    }
}
int c[size], bit[70];
int solveImpl(Int64 n, int k) {
    int bsiz = 0;
    while(n) {
        bit[bsiz++] = n % k;
        n /= k;
    }
    for(int i = 0; i <= k; ++i)
        c[i] = b[i] % k;
    for(int i = 1; i < bsiz; ++i) {
        for(int j = 1; j <= bit[i]; ++j) {
            for(int x = 0; x < k; ++x)
                c[x] = (i * c[x] + c[x + 1]) % k;
            c[k] = (c[0] + c[1]) % k;
        }
    }
    return c[bit[0]];
}
const int fac[4] = { 2, 13, 5281, 7283 };
int solve(Int64 n) {
    Int64 res = 0;
    for(int i = 0; i < 4; ++i) {
        int k = fac[i];
        Int64 v = solveImpl(n, k);
        Int64 u = phi / k;
        res = (res + powm(u, k - 2, k) * u % phi * v) %
            phi;
    }
    return res;
}
int main() {
    Int64 n, m;
    scanf("%lld%lld", &n, &m);
    pre();
    printf("%lld\n", powm(m, solve(n), mod));
    return 0;
}
