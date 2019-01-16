#include <cmath>
#include <cstdio>
const int size = 3200000, mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int p[230000], mu[size];
bool flag[size];
void pre(int n) {
    mu[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i])
            p[++pcnt] = i, mu[i] = -1;
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j])
                mu[val] = -mu[i];
            else
                break;
        }
    }
}
int main() {
    Int64 n, m;
    scanf("%lld%lld", &n, &m);
    int end = sqrt(n < m ? n : m);
    pre(end);
    Int64 res = 0;
    for(int i = 1; i <= end; ++i)
        if(mu[i]) {
            Int64 s = asInt64(i) * i;
            res = (res +
                   mu[i] * (n / s % mod) *
                       (m / s % mod)) %
                mod;
        }
    if(res < 0)
        res += mod;
    printf("%lld\n", res);
    return 0;
}
