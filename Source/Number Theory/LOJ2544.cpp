#include <cstdio>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 10000005, mod = 1000000007;
int l, r, p[700000], fac[size], inv[size], pcnt = 0,
                                           cnt = 0;
bool flag[size];
int main() {
    scanf("%d%d", &l, &r);
    Int64 res = 0;
    if(l == 1) {
        res = 1;
        for(int i = 2; i < r; ++i)
            res = res * i % mod;
        res = res *
            (((asInt64(r) * (r + 1)) >> 1) % mod) %
            mod;
    } else {
        int n = r - l + 1;
        for(int i = 2; i <= r; ++i) {
            if(!flag[i]) {
                p[++pcnt] = i;
                if(i >= l)
                    ++cnt;
            }
            for(int j = 1; j <= pcnt && p[j] * i <= r;
                ++j) {
                int val = p[j] * i;
                flag[val] = true;
                if(val >= l && i < l)
                    ++cnt;
                if(i % p[j] == 0)
                    break;
            }
        }
        int end = cnt;
        if(n - cnt > end)
            end = n - cnt;
        fac[0] = 1;
        for(int i = 1; i <= end; ++i)
            fac[i] = asInt64(fac[i - 1]) * i % mod;
        inv[1] = 1;
        end = n - cnt;
        for(int i = 2; i <= end; ++i)
            inv[i] = asInt64(mod - mod / i) *
                inv[mod % i] % mod;
        Int64 icnt =
            asInt64(fac[cnt]) * fac[n - cnt] % mod;
        for(int i = cnt; i <= n; ++i) {
            res = (res + i * icnt) % mod;
            icnt = icnt * i % mod * inv[i - cnt + 1] %
                mod;
        }
    }
    printf("%lld\n", res);
    return 0;
}
