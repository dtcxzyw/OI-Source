#include <cstdio>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int mod = 998244353;
Int64 sum1(Int64 x) {
    return ((x * (x + 1)) >> 1);
}
const Int64 inv3 = (mod + 1) / 3;
Int64 sum2(Int64 x) {
    return x * (x + 1) % mod * (2 * x + 1);
}
int main() {
    int n;
    scanf("%d", &n);
    Int64 res0 = 0, res1 = 0, res2 = 0, ls1 = 0,
          ls2 = 0;
    for(int i = 1; i <= n;) {
        int div = n / i, j = n / div;
        Int64 delta0 = j - i + 1;
        res0 = (res0 + delta0 * div) % mod;

        Int64 cs1 = sum1(j);
        Int64 delta1 = cs1 - ls1;
        ls1 = cs1;
        res1 = (res1 + delta1 * div) % mod;

        Int64 cs2 = sum2(j);
        Int64 delta2 = (cs2 - ls2) % mod;
        ls2 = cs2;
        res2 = (res2 + delta2 * div) % mod;

        i = j + 1;
    }
    Int64 res =
        (res0 * 5 + res1 * 3 + res2 * inv3) % mod;
    if(res < 0)
        res += mod;
    printf("%lld\n", res);
    return 0;
}
