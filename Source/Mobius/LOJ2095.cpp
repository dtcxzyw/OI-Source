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
int mini(int a, int b) {
    return a < b ? a : b;
}
const int size = 100005;
int p[10000], mu[size];
bool flag[size];
void pre(int n) {
    mu[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i])
            p[++pcnt] = i, mu[i] = -1;
        for(int j = 1; j <= pcnt && p[j] * i <= n;
            ++j) {
            int val = p[j] * i;
            flag[val] = true;
            if(i % p[j])
                mu[val] = -mu[i];
            else
                break;
        }
    }
    for(int i = 1; i <= n; ++i)
        mu[i] += mu[i - 1];
}
int main() {
    int n, k, l, h;
    scanf("%d%d%d%d", &n, &k, &l, &h);
    l = (l - 1) / k + 1, h /= k;
    int delta = h - l;
    pre(delta);
    Int64 res = l == 1;
    for(int i = 1; i <= delta;) {
        int d1 = (l - 1) / i, d2 = h / i;
        int j =
            mini(delta, mini(d1 ? (l - 1) / d1 : size,
                             d2 ? h / d2 : size));
        int d = d2 - d1;
        res =
            (res +
             (mu[j] - mu[i - 1]) * (powm(d, n) - d)) %
            mod;
        i = j + 1;
    }
    res = (res + mod) % mod;
    printf("%lld\n", res);
    return 0;
}
