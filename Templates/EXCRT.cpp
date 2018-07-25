//P4777
#include <cstdio>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
Int64 add(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a < mod ? a : a - mod;
}
#ifdef ONLINE_JUDGE
typedef __int128 Int128;
Int64 mulm(Int128 a, Int128 b, Int128 mod) {
    return a * b % mod;
}
#else
Int64 mulm(Int64 a, Int64 b, Int64 mod) {
    a %= mod, b %= mod;
    if (a < 0) a += mod;
    if (b < 0) b += mod;
    Int64 res = 0;
    while (b) {
        if (b & 1) res = add(res, a, mod);
        b >>= 1, a = add(a, a, mod);
    }
    return res;
}
#endif
void exgcd(Int64 a, Int64 b, Int64 &x, Int64 &y, Int64 &d) {
    if (b) {
        exgcd(b, a % b, y, x, d);
        y -= a / b * x;
    } else
        x = 1, y = 0, d = a;
}
int main() {
    int n = read();
    Int64 ca = 1, cb = 0;
    while (n--) {
        Int64 a = read();
        Int64 b = read();
        Int64 x, y, d;
        exgcd(ca, a, x, y, d);
        Int64 lcm = ca / d * a;
        Int64 k = (cb - b) / d;
        cb = (cb - mulm(mulm(x, k, a), ca, lcm)) % lcm;
        ca = lcm;
    }
    printf("%lld\n", (cb % ca + ca) % ca);
    return 0;
}
