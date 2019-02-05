#include <algorithm>
#include <cstdio>
typedef long long Int64;
Int64 add(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a < mod ? a : a - mod;
}
int countTZ(Int64 x) {
    return __builtin_ctzll(x);
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
    a %= mod;
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
        if(t != 1 && t != end && ct == 1)
            return true;
        t = ct;
    }
    return t != 1;
}
bool primeTest(Int64 x) {
    if(x == 1)
        return false;
    if(x == 46856248255981)
        return false;
    if(x == 2 || x == 3 || x == 7 || x == 61 ||
       x == 24251)
        return true;
    Int64 d = x - 1;
    d >>= countTZ(d);
    const int p[5] = { 2, 3, 7, 61, 24251 };
    for(int i = 0; i < 5; ++i)
        if(witness(x, p[i], d))
            return false;
    return true;
}
int A[15];
int main() {
    Int64 res = 0;
    for(int i = 1; i <= 9; ++i) {
        for(int j = 1; j <= i; ++j)
            A[j] = j;
        do {
            Int64 val = 0;
            for(int j = 1; j <= i; ++j)
                val = val * 10 + A[j];
            // printf("check %lld\n", val);
            if(primeTest(val)) {
                printf("find %lld\n", val);
                res = std::max(val, res);
            }
        } while(
            std::next_permutation(A + 1, A + i + 1));
    }
    printf("%lld\n", res);
    return 0;
}
