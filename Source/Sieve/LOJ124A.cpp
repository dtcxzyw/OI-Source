#include <cstdio>
const int size = 10000005, mod = 1000000007;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int p[size], fv[size], base[size], fac[size], pw[size];
bool flag[size];
int main() {
    int n, k, pcnt = 0;
    scanf("%d%d", &n, &k);
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            pw[i] = powm(i, k);
            fv[i] = add(1, pw[i]);
            base[i] = 1;
            fac[i] = fv[i];
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j]) {
                fv[val] =
                    asInt64(fv[p[j]]) * fv[i] % mod;
                pw[val] = pw[p[j]];
                base[val] = fv[i];
                fac[val] = fv[p[j]];
            } else {
                pw[val] =
                    asInt64(pw[i]) * pw[p[j]] % mod;
                base[val] = base[i];
                fac[val] = add(fac[i], pw[val]);
                fv[val] = asInt64(base[val]) *
                    fac[val] % mod;
                break;
            }
        }
    }
    int sum = 1;
    for(int i = 2; i <= n; ++i)
        sum = add(sum, fv[i]);
    printf("%d\n", sum);
    return 0;
}
