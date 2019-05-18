#include <cstdio>
const int mod = 998244353, size = 10000005;
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
#define asInt64 static_cast<Int64>
int invFac[size];
struct pack {
    int powv, mulv;
} X[size];
int main() {
    int n;
    scanf("%d", &n);
    Int64 A[4], B[4];
    {
        Int64 base = powm(3, (mod - 1) / 4);
        B[0] = 1;
        for(int i = 1; i < 4; ++i)
            B[i] = B[i - 1] * base % mod;
        for(int i = 0; i < 4; ++i) {
            --B[i];
            if(B[i] < 0)
                B[i] += mod;
            A[i] = 1;
        }
    }
    invFac[0] = 1;
    for(int i = 1; i <= n; ++i)
        invFac[i] = asInt64(invFac[i - 1]) * i % mod;
    Int64 nfac = invFac[n];
    invFac[n] = powm(invFac[n], mod - 2);
    for(int i = n; i >= 1; --i)
        invFac[i - 1] = asInt64(invFac[i]) * i % mod;
    X[n].powv = 2;
    for(int i = n; i >= 1; --i) {
        X[i - 1].powv =
            asInt64(X[i].powv) * X[i].powv % mod;
        X[i].mulv =
            asInt64(invFac[i]) * invFac[n - i] % mod;
    }
    X[0].mulv = asInt64(invFac[0]) * invFac[n] % mod;
    Int64 res = 0;
    for(int i = 0; i <= n; ++i) {
        Int64 sum = i == 0;
        for(int j = 1; j < 4; ++j) {
            sum += A[j];
            A[j] = A[j] * B[j] % mod;
        }
        res =
            (res +
             sum * X[i].mulv % mod * (X[i].powv - 1)) %
            mod;
    }
    res = (1 +
           res * nfac % mod * (mod - (mod - 1) / 4)) %
        mod;
    if(res < 0)
        res += mod;
    printf("%lld\n", res);
    return 0;
}
