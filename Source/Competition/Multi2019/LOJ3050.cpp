#include <cstdio>
#include <cstring>
#include <map>
#include <string>
typedef long long Int64;
#define asInt64 static_cast<Int64>
template <typename Int = int>
Int read() {
    Int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int readMod(int mod) {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = (res * 10LL + c - '0') % mod;
        c = getchar();
    }
    return res;
}
namespace Foo1 {
    const int mod = 998244353, phi = mod - 1, bsiz = 1
        << 15;
    int A[bsiz], B[bsiz];
    void foo() {
        A[0] = 1;
        for(int i = 1; i < bsiz; ++i)
            A[i] = A[i - 1] * 19LL % mod;
        B[0] = 1;
        Int64 fac = A[bsiz - 1] * 19LL % mod;
        for(int i = 1; i < bsiz; ++i)
            B[i] = B[i - 1] * fac % mod;
        int n = read();
        for(int i = 1; i <= n; ++i) {
            int c = readMod(phi);
            int res = asInt64(A[c & 32767]) *
                B[c >> 15] % mod;
            printf("%d\n", res);
        }
    }
}
namespace Foo2 {
    const int mod = 1145141, phi = mod - 1, bsiz = 1
        << 11;
    int A[bsiz], B[bsiz];
    void foo() {
        A[0] = 1;
        for(int i = 1; i < bsiz; ++i)
            A[i] = A[i - 1] * 19LL % mod;
        B[0] = 1;
        Int64 fac = A[bsiz - 1] * 19LL % mod;
        for(int i = 1; i < bsiz; ++i)
            B[i] = B[i - 1] * fac % mod;
        int n = read();
        for(int i = 1; i <= n; ++i) {
            int c = readMod(phi);
            int res = asInt64(A[c & 2047]) *
                B[c >> 11] % mod;
            printf("%d\n", res);
        }
    }
}
namespace Foo3 {
    void foo() {}
}
namespace Foo4 {
    const int mod = 998244353;
    int A[100005];
    void foo() {
        int n = read();
        A[0] = 1;
        for(int i = 1; i <= 100000; ++i)
            A[i] = A[i - 1] * 19 % mod;
        for(int i = 1; i <= n; ++i) {
            int c = read();
            printf("%d\n", A[c]);
        }
    }
}
namespace Shared {
    Int64 mulm(Int64 a, Int64 b, Int64 mod) {
        Int64 res = (a * b -
                     static_cast<Int64>(
                         static_cast<long double>(a) /
                         mod * b) *
                         mod) %
            mod;
        return res < 0 ? res + mod : res;
    }
    Int64 iabs(Int64 x) {
        return x >= 0 ? x : -x;
    }
    int countTZ(Int64 x) {
        return __builtin_ctzll(x);
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
    Int64 getRand32() {
        static int seed = 25477;
        return seed = seed * 48271LL % 2147483647;
    }
    Int64 getRand64() {
        return getRand32() << 32 | getRand32();
    }
    Int64 add(Int64 a, Int64 b, Int64 mod) {
        a += b;
        return a < mod ? a : a - mod;
    }
}
namespace Foo5 {
    using namespace Shared;
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
            if(t != 1 && t != end && ct == 1)
                return true;
            t = ct;
        }
        return t != 1;
    }
    bool primeTestImpl(Int64 x) {
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
    bool primeTest(Int64 x) {
        if((x & 1) == 0)
            return x == 2;
        const int p[5] = { 3, 5, 7, 11, 13 };
        for(int i = 0; i < 5; ++i)
            if(x % p[i] == 0)
                return x == p[i];
        return primeTestImpl(x);
    }
    void foo() {
        int n = read();
        for(int i = 1; i <= n; ++i) {
            Int64 l = read<Int64>();
            Int64 r = read<Int64>();
            for(Int64 j = l; j <= r; ++j)
                putchar(primeTest(j) ? 'p' : '.');
            putchar('\n');
        }
    }
}
namespace Foo6 {
    using namespace Shared;
    Int64 pollardRho(Int64 n) {
        Int64 c = getRand64() % (n - 1) + 1, x = 0,
              y = 0, t = 1, q = 1;
        for(int k = 2; t == 1; k <<= 1, y = x, q = 1) {
            for(int i = 0; i < k && t == 1; ++i) {
                x = add(mulm(x, x, n), c, n);
                q = mulm(q, iabs(x - y), n);
                if((i & 127) == 0)
                    t = gcd(q, n);
            }
        }
        return t == 1 ? 0 : t;
    }
    Int64 getFacImpl(Int64 x) {
        if(Foo5::primeTest(x))
            return x;
        else {
            Int64 d = 0;
            while(!d)
                d = pollardRho(x);
            while(x % d == 0)
                x /= d;
            return getFacImpl(x == 1 ? d :
                                       std::min(x, d));
        }
    }
    Int64 getFac(Int64 x) {
        if((x & 1) == 0)
            return 2;
        const int p[5] = { 3, 5, 7, 11, 13 };
        for(int i = 0; i < 5; ++i)
            if(x % p[i] == 0)
                return p[i];
        return getFacImpl(x);
    }
    int getMu(Int64 x) {
        if(x % 4 == 0 || x % 9 == 0)
            return '0';
        int res = 0;
        while(x != 1) {
            Int64 fac = getFac(x);
            int p = 0;
            do
                x /= fac, ++p;
            while(x % fac == 0);
            if(p >= 2)
                return '0';
            res ^= 1;
        }
        return res ? '-' : '+';
    }
    void foo() {
        int n = read();
        for(int i = 1; i <= n; ++i) {
            Int64 l = read<Int64>();
            Int64 r = read<Int64>();
            for(Int64 j = l; j <= r; ++j)
                putchar(getMu(j));
            putchar('\n');
        }
    }
}
namespace Foo7 {
    void foo() {}
}
namespace Foo8 {
    void foo() {}
}
int main() {
    typedef void (*Func)();
    std::map<std::string, Func> LUT;
    LUT["1_998244353"] = Foo1::foo;
    LUT["1?"] = Foo2::foo;
    LUT["1?+"] = Foo3::foo;
    LUT["1wa_998244353"] = Foo4::foo;
    LUT["2p"] = Foo5::foo;
    LUT["2u"] = Foo6::foo;
    LUT["2g"] = Foo7::foo;
    LUT["2g?"] = Foo8::foo;
    char t[20];
    scanf("%s", t);
    LUT[t]();
    return 0;
}
