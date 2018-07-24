#include <cstdio>
typedef long long Int64;
Int64 add(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a < mod ? a : a - mod;
}
#ifdef ONLINE_JUDGE
typedef __int128 Int128;
Int64 mulm(Int128 a, Int128 b, Int128 mod) {
    return a * b % mod;
}
#else
Int64 mulm(Int64 a, Int64 b, Int64 mod) {
    Int64 res = 0;
    while (b) {
        if (b & 1) res = add(res, a, mod);
        b >>= 1, a = add(a, a, mod);
    }
    return res;
}
#endif
const Int64 size = 10000005, p = 1000000007;
Int64 powm(Int64 a, Int64 k, Int64 mod) {
    Int64 res = 1;
    while (k) {
        if (k & 1) res = mulm(res, a, mod);
        k >>= 1, a = mulm(a, a, mod);
    }
    return res;
}
int mu[size] = {}, phi[size], prime[700000];
bool flag[size] = {};
void pre(int n) {
    int pcnt = 0;
    mu[1] = phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!flag[i]) {
            prime[++pcnt] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= pcnt; ++j) {
            int val = prime[j] * i;
            if (val > n) break;
            flag[val] = true;
            if (i % prime[j]) {
                mu[val] = -mu[i];
                phi[val] = phi[i] * (prime[j] - 1);
            } else {
                phi[val] = phi[i] * prime[j];
                break;
            }
        }
    }
    for (int i = 1; i <= n; ++i) mu[i] += mu[i - 1];
}
Int64 calcF(Int64 cnt, Int64 x, Int64 mod) {
    return add(powm(cnt - 1, x, mod), mulm(x & 1 ? mod - 1 : 1, cnt - 1, mod), mod);
}
Int64 calcPhi(Int64 x, Int64 mod) {
    if (x <= 10000000)
        return phi[x];
    else {
        Int64 res = x, i2 = 1;
        for (int i = 2; i2 <= x; ++i) {
            if (x % i == 0) {
                do
                    x /= i;
                while (x % i == 0);
                res -= res / i;
            }
            i2 += i << 1 | 1;
        }
        if (x != 1) res -= res / x;
        return res % mod;
    }
}
int foo() {
    Int64 n;
    int a;
    scanf("%lld%d", &n, &a);
    Int64 mod, invp;
    if (n % p)
        mod = p, invp = p - 2;
    else
        mod = p * p, invp = p * (p - 1) - 1;
    Int64 cnt = 2;
    for (int i = 1; i <= a;) {
        int div = a / i;
        int j = a / div;
        Int64 delta = mu[j] - mu[i - 1];
        if (delta < 0) delta += mod;
        cnt = add(cnt, mulm(mulm(mulm(delta, div, mod), div, mod), div + 3, mod), mod);
        i = j + 1;
    }
    cnt = mulm(cnt, powm(6, invp, mod), mod);
    Int64 i2 = 1, res = 0;
    for (int i = 1; i2 <= n; ++i) {
        if (n % i == 0) {
            Int64 j = n / i;
            res = add(res, mulm(calcF(cnt, i, mod), calcPhi(j, mod), mod), mod);
            if (i2 != n) res = add(res, mulm(calcF(cnt, j, mod), phi[i], mod), mod);
        }
        i2 += i << 1 | 1;
    }
    if (n % p)
        res = res * powm(n % mod, invp, mod) % mod;
    else
        res = (res / p) * powm(n / p, p - 2, p) % p;
    return res;
}
int main() {
    pre(10000000);
    int t;
    scanf("%d", &t);
    while (t--) printf("%d\n", foo());
    return 0;
}
