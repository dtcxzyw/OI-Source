//P4718
#include <algorithm>
#include <cstdio>
#include <cstdlib>
typedef long long Int64;
Int64 add(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a < mod ? a : a - mod;
}
Int64 sub(Int64 a, Int64 b, Int64 mod) {
    a -= b;
    return a >= 0 ? a : a + mod;
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
Int64 powm(Int64 a, Int64 k, Int64 mod) {
    Int64 res = 1;
    while (k) {
        if (k & 1) res = mulm(res, a, mod);
        k >>= 1, a = mulm(a, a, mod);
    }
    return res;
}
bool witness(Int64 x, Int64 base, Int64 d) {
    Int64 t = powm(base, d, x);
    Int64 end = x - 1;
    while (t != end && t != 1 && d != end)
        d <<= 1, t = mulm(t, t, x);
    return t == end | (d & 1);
}
bool primeTest(Int64 x) {
    Int64 d = x - 1;
    d >>= __builtin_ctzll(d);
    for (int i = 0; i < 5; ++i)
        if (!witness(x, rand() % (x - 2) + 2, d))
            return false;
    return true;
}
Int64 gcd(Int64 a, Int64 b) {
    return b ? gcd(b, a % b) : a;
}
Int64 iabs(Int64 x) {
    return x >= 0 ? x : -x;
}
void getFacImpl(Int64 x, Int64 &res) {
    if (x <= res) return;
    if (primeTest(x))
        res = x;
    else {
        Int64 a = rand() % x, b = a;
        int i = 1, k = 2;
        while (true) {
            ++i;
            a = sub(mulm(a, a, x), 1, x);
            Int64 d = gcd(iabs(a - b), x);
            if (d > 1 && d != x) {
                Int64 e = x / d;
                if (e > d) std::swap(d, e);
                getFacImpl(d, res);
                getFacImpl(e, res);
                return;
            }
            if (i == k) k <<= 1, b = a;
        }
    }
}
Int64 getFac(Int64 x) {
    Int64 res = 1;
    int t = __builtin_ctzll(x);
    if (t) x >>= t, res = 2;
    const int p[5] = {3, 5, 7, 11, 13};
    for (int i = 0; i < 5; ++i)
        if (x % p[i] == 0) {
            res = p[i];
            do
                x /= p[i];
            while (x % p[i] == 0);
        }
    getFacImpl(x, res);
    return res;
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        Int64 x;
        scanf("%lld", &x);
        Int64 res = getFac(x);
        if (res == x)
            puts("Prime");
        else
            printf("%lld\n", res);
    }
    return 0;
}
