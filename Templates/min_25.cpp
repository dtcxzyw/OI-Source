#include <cmath>
#include <cstdio>
const int mod = 1000000007, inv2 = 500000004;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
typedef long long Int64;
int clamp(Int64 x) {
    x %= mod;
    return x >= 0 ? x : x + mod;
}
Int64 n, sqr;
const int size = 100005;
int p[size], sp[size], pcnt = 0;
bool flag[size];
void pre(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            sp[pcnt] = add(sp[pcnt - 1], i);
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            flag[i * p[j]] = true;
            if(i % p[j] == 0)
                break;
        }
    }
}
int g[2][size], h[2][size];
Int64 q[2 * size];
int& getG(int (&g)[2][size], Int64 x) {
    if(x <= sqr)
        return g[0][x];
    return g[1][n / x];
}
Int64 S(Int64 n, int j) {
    if(n <= 1 || p[j] > n)
        return 0;
    int res = clamp(getG(g, n) - sp[j - 1] -
                    (getG(h, n) - (j - 1)) +
                    (j == 1 ? 2 : 0));
    for(int i = j; i <= pcnt; ++i) {
        Int64 cp = p[i], p1 = cp, p2 = p1 * p1;
        if(p2 > n)
            break;
        for(int e = 1; p2 <= n;
            ++e, p1 = p2, p2 *= cp) {
            res = clamp(res +
                        S(n / p1, i + 1) * (cp ^ e) +
                        (cp ^ (e + 1)));
        }
    }
    return res;
}
int main() {
    scanf("%lld", &n);
    sqr = sqrt(n);
    pre(sqr);
    Int64 i = 1;
    int m = 0;
    while(i <= n) {
        Int64 val = n / i;
        q[++m] = val;
        getG(g, val) = ((val + 2) % mod) *
            ((val - 1) % mod) % mod * inv2 % mod;
        getG(h, val) = (val - 1) % mod;
        i = n / val + 1;
    }
    for(int i = 1; i <= pcnt; ++i) {
        Int64 cp = p[i], p2 = cp * cp;
        for(int j = 1; j <= m && p2 <= q[j]; ++j) {
            Int64 k = q[j];
            int &vg = getG(g, k), &vh = getG(h, k);
            vg = clamp(
                vg -
                cp * (getG(g, k / cp) - sp[i - 1]));
            vh = clamp(vh -
                       (getG(h, k / cp) - (i - 1)));
        }
    }
    printf("%d\n", add(S(n, 1), 1));
    return 0;
}
