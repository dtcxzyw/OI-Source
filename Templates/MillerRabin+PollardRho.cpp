// TODO:P4718
#include <algorithm>
#include <cstdio>
#include <cstdlib>
typedef long long Int64;
Int64 getRand32() {
    static int seed = 25477;
    return seed = seed * 48271LL % 2147483647;
}
Int64 getRand64() {
    return getRand32() << 32 | getRand32();
}
int countTZ(Int64 x) {
    return __builtin_ctzll(x);
}
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
    while(b) {
        if(b & 1)
            res = add(res, a, mod);
        b >>= 1, a = add(a, a, mod);
    }
    return res;
}
#endif
Int64 powm(Int64 a, Int64 k, Int64 mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = mulm(res, a, mod);
        k >>= 1, a = mulm(a, a, mod);
    }
    return res;
}
bool witness(Int64 x, Int64 base, Int64 d) {
    Int64 t = powm(base, d, x);
    Int64 end = x - 1;
    while(d != end) {
        d <<= 1;
        Int64 ct = mulm(t, t, x);
        if(t != 1 && t != x - 1 && ct == 1)
            return true;
        t = ct;
    }
    return t != 1;
}
bool primeTest(Int64 x) {
    if(x == 46856248255981)
        return false;
    if(x == 61 || x == 24251)
        return true;
    Int64 d = x - 1;
    d >>= countTZ(d);
    const int p[5] = { 2, 3, 7, 61, 24251 };
    for(int i = 0; i < 5; ++i)
        if(witness(x, p[i], d))
            return false;
    return true;
}
Int64 iabs(Int64 x) {
    return x >= 0 ? x : -x;
}
Int64 gcd(Int64 a, Int64 b) {
    if(a && b) {
        int off = countTZ(a | b);
        a >>= countTZ(a);
        do {
            b >>= countTZ(b);
            if(a > b)
                std::swap(a, b);
            b -= a;
        } while(b);
        return a << off;
    }
    return a | b;
}
void getFacImpl(Int64 x, Int64& res) {
    if(x <= res)
        return;
    if(primeTest(x))
        res = x;
    else {
        static int c = 547475638;
        while(true) {
            Int64 a = getRand64() % (x - 2) + 2, b = a;
            int i = 1, k = 2;
            while(true) {
                ++i;
                a = add(mulm(a, a, x), c % x, x);
                Int64 d = gcd(iabs(a - b), x);
                if(d > 1 && d != x) {
                    Int64 e = x / d;
                    if(e > d)
                        std::swap(d, e);
                    getFacImpl(d, res);
                    getFacImpl(e, res);
                    return;
                }
                if(a == b)
                    break;
                if(i == k)
                    k <<= 1, b = a;
            }
            --c;
        }
    }
}
Int64 getFac(Int64 x) {
    Int64 res = 1;
    int t = countTZ(x);
    if(t)
        x >>= t, res = 2;
    const int p[5] = { 3, 5, 7, 11, 13 };
    for(int i = 0; i < 5; ++i)
        if(x % p[i] == 0) {
            res = p[i];
            do
                x /= p[i];
            while(x % p[i] == 0);
        }
    getFacImpl(x, res);
    return res;
}
int main() {
    freopen("testdata.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while(t--) {
        Int64 x;
        scanf("%lld", &x);
        Int64 res = getFac(x);
        if(res == x)
            puts("Prime");
        else
            printf("%lld\n", res);
    }
    return 0;
}
