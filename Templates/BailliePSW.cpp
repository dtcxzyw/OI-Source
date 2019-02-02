#include <cstdio>
#define PREDIV
typedef long long Int64;
const Int64 maxi = 1LL << 31;
#ifdef ONLINE_JUDGE
typedef __int128 Int128;
Int64 mulm(Int128 a, Int128 b, Int128 mod) {
    return a * b % mod;
}
#else
Int64 addm(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a < mod ? a : a - mod;
}
Int64 mulm(Int64 a, Int64 k, Int64 mod) {
    Int64 res = 0;
    while(k) {
        if(k & 1)
            res = addm(res, a, mod);
        k >>= 1, a = addm(a, a, mod);
    }
    return res;
}
#endif
Int64 powmBig(Int64 a, Int64 k, Int64 mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = mulm(res, a, mod);
        k >>= 1, a = mulm(a, a, mod);
    }
    return res;
}
Int64 powm(Int64 a, Int64 k, Int64 mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
bool isPerfectSquare(Int64 x) {
    Int64 l = 1, r = 1e9, ans = 0;
    while(l <= r) {
        Int64 m = (l + r) >> 1;
        if(m * m <= x)
            ans = m, l = m + 1;
        else
            r = m - 1;
    }
    return ans * ans == x;
}
int countTZ(Int64 x) {
    return __builtin_ctzl(x);
}
bool Fermat2Big(Int64 x) {
    Int64 d = x - 1, cd = d >> countTZ(d),
          t = powmBig(2, cd, x);
    while(cd != d) {
        Int64 ct = mulm(t, t, x);
        if(ct == 1 && t != 1 && t != d)
            return true;
        cd <<= 1, t = ct;
    }
    return t != 1;
}
bool Fermat2(Int64 x) {
    if(x > maxi)
        return Fermat2Big(x);
    Int64 d = x - 1, cd = d >> countTZ(d),
          t = powm(2, cd, x);
    while(cd != d) {
        Int64 ct = t * t % x;
        if(ct == 1 && t != 1 && t != d)
            return true;
        cd <<= 1, t = ct;
    }
    return t != 1;
}
Int64 gcd(Int64 a, Int64 b) {
    return b ? gcd(b, a % b) : a;
}
int jacobi(Int64 a, Int64 b) {
    a %= b;
    if(a < 0)
        a += b;

    int x = countTZ(a);
    a >>= x;
    unsigned int modv = b & 7;
    bool flag = (x & 1) && (modv == 3 || modv == 5);

    if(b == 1)
        return flag ? -1 : 1;

    if(gcd(a, b) != 1)
        return 0;

    flag ^= (a & 3) == 3 && (b & 3) == 3;

    int val = jacobi(b, a);
    return flag ? -val : val;
}
Int64 getD(Int64 x) {
    for(Int64 i = 5, add = 2;; add = -add, i = add - i)
        if(jacobi(i, x) == -1)
            return i;
}
struct LucasPair {
    Int64 U, V;
    LucasPair(Int64 U, Int64 V) : U(U), V(V) {}
};
// P=1
LucasPair calcLucasSeqBig(Int64 D, Int64 Q, Int64 mod,
                          Int64 k) {
    Int64 ck = 0, qck = 1;
    LucasPair cp(0, 2);
    for(int i = 62; i >= 0; --i) {
        cp = LucasPair(
            mulm(cp.U, cp.V, mod),
            (mulm(cp.V, cp.V, mod) - 2 * qck) % mod);
        if(cp.V < 0)
            cp.V += mod;
        qck = mulm(qck, qck, mod);
        ck <<= 1;
        if(k & (1LL << i)) {
            Int64 v1 = cp.U + cp.V;
            if(v1 & 1)
                v1 += mod;
            Int64 v2 = mulm(D, cp.U, mod) + cp.V;
            if(v2 & 1)
                v2 += mod;
            cp = LucasPair((v1 >> 1) % mod,
                           (v2 >> 1) % mod);
            qck = mulm(qck, Q, mod);
            ck |= 1;
        }
    }
    return cp;
}
LucasPair calcLucasSeq(Int64 D, Int64 Q, Int64 mod,
                       Int64 k) {
    D %= mod, Q %= mod;
    if(D < 0)
        D += mod;
    if(Q < 0)
        Q += mod;
    if(mod > maxi)
        return calcLucasSeqBig(D, Q, mod, k);
    Int64 ck = 0, qck = 1;
    LucasPair cp(0, 2);
    for(int i = 62; i >= 0; --i) {
        cp = LucasPair(cp.U * cp.V % mod,
                       (cp.V * cp.V - 2 * qck) % mod);
        if(cp.V < 0)
            cp.V += mod;
        qck = qck * qck % mod;
        ck <<= 1;
        if(k & (1LL << i)) {
            Int64 v1 = cp.U + cp.V;
            if(v1 & 1)
                v1 += mod;
            Int64 v2 = D * cp.U + cp.V;
            if(v2 & 1)
                v2 += mod;
            cp = LucasPair((v1 >> 1) % mod,
                           (v2 >> 1) % mod);
            qck = qck * Q % mod;
            ck |= 1;
        }
    }
    return cp;
}
bool Lucas(Int64 x) {
    Int64 D = getD(x), Q = (1 - D) >> 2;
    LucasPair p = calcLucasSeq(D, Q, x, x + 1);
    return p.U == 0 && p.V == ((2 * Q) % x + x) % x;
}
bool BailliePSW(Int64 x) {
    if(x == 1)
        return false;
#ifdef PREDIV
    Int64 pa[] = { 2, 3, 5, 7, 11, 13 };  // 80%
    for(Int64 p : pa) {
        if(x == p)
            return true;
        if(x % p == 0)
            return false;
    }
#else
    if(x == 2)
        return true;
#endif
    if(isPerfectSquare(x))
        return false;
    if(Fermat2(x))
        return false;
    return Lucas(x);
}
int main() {
    Int64 x;
    while(scanf("%lld", &x) != EOF)
        puts(BailliePSW(x) ? "Y" : "N");
    return 0;
}
