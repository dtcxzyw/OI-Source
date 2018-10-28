#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 600005, mod = 998244353;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int fac[size * 2], inv[size * 2], invFac[size * 2];
void pre(int x) {
    static int cx = 1;
    while(cx < x) {
        ++cx;
        fac[cx] = asInt64(fac[cx - 1]) * cx % mod;
        inv[cx] = asInt64(mod - mod / cx) *
            inv[mod % cx] % mod;
        invFac[cx] =
            asInt64(invFac[cx - 1]) * inv[cx] % mod;
    }
}
int C(int n, int m) {
    pre(n);
    return asInt64(fac[n]) * invFac[m] % mod *
        invFac[n - m] % mod;
}
int solve(int n, int m) {
    if(m >= 2) {
        int k = n + m - 1;
        return sub(C(k, m), C(k, m - 2));
    }
    return m == 1 ? n : 1;
}
int S[size], n;
void modify(int x) {
    while(x <= n) {
        ++S[x];
        x += x & -x;
    }
}
int query(int x) {
    int res = 0;
    while(x) {
        res += S[x];
        x -= x & -x;
    }
    return res;
}
int foo() {
    n = read();
    memset(S, 0, sizeof(int) * (n + 1));
    int res = 0, crge = n, i;
    for(i = 1; i <= n; ++i) {
        int a = read();
        int lle = query(a);
        modify(a);
        int rge = (n - a) - (i - 1 - lle);
        bool flag = crge > rge;
        if(flag)
            crge = rge;
        if(crge == 0)
            break;
        res = add(res, solve(n - i + 1, crge - 1));
        if(!flag && lle != a - 1)
            break;
    }
    while(++i <= n)
        read();
    return res;
}
int main() {
    fac[0] = fac[1] = invFac[0] = invFac[1] = inv[1] =
        1;
    int t = read();
    while(t--)
        printf("%d\n", foo());
    return 0;
}
