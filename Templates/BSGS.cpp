#include <cmath>
#include <cstdio>
#include <unordered_map>
using Int64 = long long;
#define asInt64 static_cast<Int64>
inline Int64 addm(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a < mod ? a : a - mod;
}
#ifdef ONLINE_JUDGE
using Int128 = __int128;
inline Int64 mulm(Int128 a, Int128 b, Int128 mod) {
    return a * b % mod;
}
#else
inline Int64 mulm(Int64 a, Int64 b, Int64 mod) {
    return (a * b -
            asInt64(static_cast<long double>(a) / mod *
                    b) *
                mod +
            mod) %
        mod;
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
Int64 calcG(Int64 p) {
    Int64 fac[70], x = p - 1;
    int fcnt = 0;
    for(Int64 i = 2; i <= x; ++i)
        if(x % i == 0) {
            do
                x /= i;
            while(x % i == 0);
            fac[++fcnt] = i;
        }
    for(Int64 i = 2; i < p; ++i) {
        bool flag = true;
        for(int j = 1; j <= fcnt; ++j)
            if(powm(i, p / fac[j], p) == 1) {
                flag = false;
                break;
            }
        if(flag)
            return i;
    }
    return -1;
}
void exgcd(Int64 a, Int64 b, Int64& d, Int64& x,
           Int64& y) {
    if(b) {
        exgcd(b, a % b, d, y, x);
        y -= a / b * x;
    } else
        x = 1, y = 0, d = a;
}
Int64 solve(Int64 a, Int64 b, Int64 p) {
    Int64 d, x, y;
    exgcd(a, p, d, x, y);
    if(b % d)
        return -1;
    Int64 c = b / d, modv = p / d;
    if(modv < 0)
        modv = -modv;
    x %= modv;
    if(x < 0)
        x += modv;
    c %= modv;
    if(c < 0)
        c += modv;
    return mulm(x, c, modv);
}
using HashTable = std::unordered_map<Int64, int>;
using IterT = HashTable::const_iterator;
Int64 lookUp(Int64 x, Int64 g, Int64 p,
             const HashTable& map, Int64 bsiz) {
    for(Int64 i = 1, cur = mulm(x, g, p); i <= bsiz;
        ++i, cur = mulm(cur, g, p)) {
        IterT it = map.find(cur);
        if(it != map.cend())
            return it->second * bsiz - i;
    }
    return -1;
}
void BSGS(int t, Int64 p) {
    Int64 g = calcG(p), phi = p - 1;
    Int64 bsiz = sqrt(p / t) + 1;
    Int64 maxb = p / bsiz + 1;
    HashTable map;
    {
        Int64 base = powm(g, bsiz, p);
        for(Int64 cur = base, i = 1; i <= maxb;
            ++i, cur = mulm(cur, base, p)) {
            if(!map.count(cur))
                map[cur] = i;
        }
    }
    for(int i = 1; i <= t; ++i) {
        Int64 a, b;
        scanf("%lld%lld", &a, &b);
        Int64 lga = lookUp(a, g, p, map, bsiz);
        Int64 lgb = lookUp(b, g, p, map, bsiz);
        printf("%lld\n", solve(lga, lgb, phi));
    }
}
int main() {
    int t;
    Int64 p;
    scanf("%d%lld", &t, &p);
    BSGS(t, p);
    return 0;
}
