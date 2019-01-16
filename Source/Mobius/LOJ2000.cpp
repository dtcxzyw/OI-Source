#include <cstdio>
int mini(int a, int b) {
    return a < b ? a : b;
}
int maxi(int a, int b) {
    return a > b ? a : b;
}
const int size = 1000005, mod = 1000000007,
          phi = mod - 1;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int p[100000], mu[size], f[size], g[size];
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
    f[1] = 1;
    for(int i = 2; i <= n; ++i)
        f[i] = add(f[i - 1], f[i - 2]);
    for(int i = 1; i <= n; ++i)
        g[i] = 1;
    for(int i = 1; i <= n; ++i) {
        Int64 fv = f[i], ifv = powm(fv, mod - 2);
        for(int j = i, c = 1; j <= n; j += i, ++c)
            if(mu[c])
                g[j] = g[j] * (mu[c] == 1 ? fv : ifv) %
                    mod;
    }
    g[0] = 1;
    for(int i = 1; i <= n; ++i)
        g[i] = asInt64(g[i - 1]) * g[i] % mod;
}
int query(int n, int m) {
    Int64 res = 1;
    int end = mini(n, m);
    for(int i = 1; i <= end;) {
        int dn = n / i, dm = m / i;
        int j = mini(n / dn, m / dm);
        Int64 fmul =
            g[j] * powm(g[i - 1], mod - 2) % mod;
        res = res *
            powm(fmul, asInt64(dn) * dm % phi) % mod;
        i = j + 1;
    }
    return res;
}
struct Query {
    int n, m;
} Q[1005];
int main() {
    int t;
    scanf("%d", &t);
    int n = 0;
    for(int i = 1; i <= t; ++i) {
        scanf("%d%d", &Q[i].n, &Q[i].m);
        n = maxi(n, mini(Q[i].n, Q[i].m));
    }
    pre(n);
    for(int i = 1; i <= t; ++i)
        printf("%d\n", query(Q[i].n, Q[i].m));
    return 0;
}
