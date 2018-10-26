#include <algorithm>
#include <cstdio>
#include <cstring>
#include <limits>
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
const Int64 end = std::numeric_limits<Int64>::max() -
    asInt64(mod - 1) * (mod - 1);
int cat[size], fac[size], inv[size];
int preInv(int x) {
    static int cx = 1;
    inv[1] = 1;
    while(cx < x) {
        ++cx;
        inv[cx] = asInt64(mod - mod / x) *
            inv[mod % cx] % mod;
    }
}
void pre(int x) {
    static int cx = 0;
    preInv(x + 1);
    while(cx < x) {
        ++cx;
        fac[cx] = asInt64(fac[cx - 1]) * cx % mod;
        cat[cx] = asInt64(cat[cx - 1]) * (4 * cx - 2) %
            mod * inv[cx + 1] % mod;
    }
}
int A[size], S[size], n;
void modify(int x) {
    while(x) {
        ++S[x];
        x -= x & -x;
    }
}
int query(int x) {
    int res = 0;
    while(x <= n) {
        res += S[x];
        x += x & -x;
    }
    return res;
}
int foo() {
    n = read();
    pre(n);
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    memset(S, 0, sizeof(int) * (n + 1));
    Int64 res = 0;
    return res % mod;
}
int main() {
    cat[0] = inv[1] = 1;
    int t = read();
    while(t--)
        printf("%d\n", foo());
    return 0;
}
