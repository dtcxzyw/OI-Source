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
int p[100000], mu[size], f[size];
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
    f[1] = 1;
    for(int i = 2; i <= n; ++i)
        f[i] = add(f[i - 1], f[i - 2]);
    f[0] = 1;
    for(int i = 2; i <= n; ++i)
        f[i] = asInt64(f[i - 1]) * f[i] % mod;
}
int queryFac(int n, int m) {
    int end = mini(n, m);
    Int64 res = 0;
    for(int i = 1; i <= end;) {
        int dn = n / i, dm = m / i;
        int j = mini(n / dn, m / dm);
        res = (res +
               asInt64(mu[j] - mu[i - 1]) * dn % phi *
                   dm) %
            phi;
        i = j + 1;
    }
    if(res < 0)
        res += phi;
    return res;
}
int query(int n, int m) {
    Int64 res = 1;
    int end = mini(n, m);
    for(int i = 1; i <= end;) {
        int dn = n / i, dm = m / i;
        int j = mini(n / dn, m / dm);
        Int64 fmul =
            f[j] * powm(f[i - 1], mod - 2) % mod;
        res = res * powm(fmul, queryFac(dn, dm)) % mod;
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
