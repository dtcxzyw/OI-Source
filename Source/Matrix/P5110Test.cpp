#include <cstdio>
const int mod = 1000000007;
typedef long long Int64;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int main() {
    int x1 = -1, x2 = -1;
    for(Int64 i = 0; i < mod; ++i) {
        if(i * i % mod == (233 * i + 666) % mod) {
            if(x1 == -1)
                x1 = i;
            else {
                x2 = i;
                break;
            }
        }
        if(i % 1048576 == 0)
            printf("%lld %d %d\n", i, x1, x2);
    }
    printf("%d %d\n", x1, x2);
    Int64 delta = x1 - x2;
    if(delta < 0)
        delta += mod;
    Int64 a = powm(delta, mod - 2);
    Int64 b = mod - a;
    printf("%lld %lld\n", a, b);
    {
        Int64 cur = 1;
        for(int i = 1; i < mod; ++i) {
            cur = cur * x1 % mod;
            if(cur == 1) {
                printf("%d\n", i);
                break;
            }
        }
    }
    {
        Int64 cur = 1;
        for(int i = 1; i < mod; ++i) {
            cur = cur * x2 % mod;
            if(cur == 1) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
