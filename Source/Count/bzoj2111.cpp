#include <algorithm>
#include <cstdio>
const int size = 1000005;
typedef long long Int64;
Int64 fac[size], invFac[size];
int mod;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
Int64 C(int n, int m) {
    return fac[n] * invFac[n - m] % mod * invFac[m] %
        mod;
}
Int64 lucas(int n, int m) {
    Int64 res = 1;
    while(n || m) {
        int cn = n % mod, cm = m % mod;
        if(cn < cm)
            return 0;
        res = res * C(cn, cm) % mod;
        n /= mod, m /= mod;
    }
    return res;
}
int F[size], lsiz[size];
int main() {
    int n;
    scanf("%d%d", &n, &mod);
    int siz = std::min(n, mod - 1);
    fac[0] = invFac[0] = 1;
    for(int i = 1; i <= siz; ++i)
        fac[i] = fac[i - 1] * i % mod;
    invFac[siz] = powm(fac[siz], mod - 2);
    for(int i = siz; i >= 1; --i)
        invFac[i - 1] = invFac[i] * i % mod;
    for(int i = 2; i <= 20; ++i) {
        int end = std::min(n + 1, 1 << i),
            half = 1 << (i - 1), delta = 1 << (i - 2);
        for(int j = half; j < end; ++j)
            lsiz[j] = std::min(j - delta, half - 1);
    }
    F[0] = 1;
    for(int i = 0; i < n; ++i) {
        int ls = lsiz[i + 1];
        F[i + 1] = lucas(i, ls) * F[ls] % mod *
            F[i - ls] % mod;
    }
    printf("%d\n", F[n]);
    return 0;
}
