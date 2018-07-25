//P4781
#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 2005, mod = 998244353;
Int64 inv(Int64 a) {
    Int64 res = 1;
    int k = mod - 2;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int X[size], Y[size], PD[size], SD[size];
int main() {
    int n = read();
    int k = read();
    for (int i = 1; i <= n; ++i) {
        int x = X[i] = read();
        Y[i] = read();
        PD[i] = SD[i] = k - x;
    }
    PD[0] = SD[n + 1] = 1;
    for (int i = 2; i <= n; ++i) PD[i] = asInt64(PD[i - 1]) * PD[i] % mod;
    for (int i = n - 1; i >= 1; --i) SD[i] = asInt64(SD[i + 1]) * SD[i] % mod;
    Int64 res = 0;
    for (int i = 1; i <= n; ++i) {
        Int64 a = asInt64(PD[i - 1]) * SD[i + 1] % mod;
        Int64 x = X[i], b = 1;
        for (int j = 1; j < i; ++j) b = b * (x - X[j]) % mod;
        for (int j = i + 1; j <= n; ++j) b = b * (x - X[j]) % mod;
        res = (res + a * inv(b) % mod * Y[i]) % mod;
    }
    int ans = (res + mod) % mod;
    printf("%d\n", ans);
    return 0;
}
