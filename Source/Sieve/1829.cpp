#include <algorithm>
#include <cstdio>
const int size = 10000005, mod = 20101009;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int p[size], F[size];
bool flag[size];
void pre(int n) {
    F[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i])
            p[++pcnt] = i, F[i] = 1 - i;
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j])
                F[val] = (1 - p[j]) * F[i];
            else {
                F[val] = F[i];
                break;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        F[i] = (F[i - 1] + asInt64(i) * F[i]) % mod;
}
Int64 S(Int64 x) {
    return ((x * (x + 1)) >> 1) % mod;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int end = std::min(n, m);
    pre(end);
    Int64 res = 0;
    for(int i = 1; i <= end;) {
        int dn = n / i, dm = m / i,
            j = std::min(n / dn, m / dm);
        res =
            (res +
             S(dn) * S(dm) % mod * (F[j] - F[i - 1])) %
            mod;
        i = j + 1;
    }
    if(res < 0)
        res += mod;
    printf("%lld\n", res);
    return 0;
}
