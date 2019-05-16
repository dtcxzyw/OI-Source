#include <cstdio>
const int size = 10000005, mod = 1000000007;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int f[size], g[size], p[size], ffac[size], gfac[size],
    d[size], pk[size];
bool flag[size];
void pre(int n) {
    f[1] = g[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            f[i] = ffac[i] = 2;

            pk[i] = asInt64(i) * i % mod;
            g[i] = gfac[i] = (1 + pk[i]) % mod;
            d[i] = 1;
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j]) {
                ffac[val] = ffac[p[j]];
                f[val] = f[i] * ffac[val];

                d[val] = i;
                pk[val] = pk[p[j]];
                gfac[val] = gfac[p[j]];
                g[val] =
                    asInt64(g[i]) * gfac[val] % mod;
            } else {
                ffac[val] = ffac[i] + 1;
                f[val] = f[i] / ffac[i] * ffac[val];

                d[val] = d[i];
                pk[val] =
                    asInt64(pk[i]) * pk[p[j]] % mod;
                gfac[val] = (gfac[i] + pk[val]) % mod;
                g[val] = asInt64(g[d[val]]) *
                    gfac[val] % mod;
                break;
            }
        }
    }
}
int main() {
    int q, x, a, b, c;
    scanf("%d%d%d%d%d", &q, &x, &a, &b, &c);
    pre(c);
    Int64 A = 0, B = 0;
    for(int k = 1; k <= q; ++k) {
        if(x & 1)
            ++A, B += 4;
        A += f[x], B += g[x];
        x = (asInt64(x) * a + b) % c + 1;
    }
    printf("%lld\n%lld\n", A % mod, B % mod);
    return 0;
}
