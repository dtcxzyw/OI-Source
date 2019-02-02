#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <vector>
using Int64 = long long;
using HashTable = std::unordered_map<Int64, int>;
using IterT = HashTable::const_iterator;
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
    a %= mod;
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = mulm(res, a, mod);
        k >>= 1, a = mulm(a, a, mod);
    }
    return res;
}
struct Prime {
    Int64 p, pc, bsiz, maxb, k, g;
    int c;
    HashTable map;
    Prime(Int64 p, int c, Int64 pc)
        : p(p), c(c), pc(pc) {}
};
auto fac(Int64 p) {
    std::vector<Prime> pfac;
    for(Int64 i = 2; i * i <= p; ++i)
        if(p % i == 0) {
            int pcnt = 0;
            Int64 pc = 1;
            do
                ++pcnt, pc *= i, p /= i;
            while(p % i == 0);
            pfac.push_back(Prime(i, pcnt, pc));
        }
    if(p != 1)
        pfac.push_back(Prime(p, 1, p));
    return pfac;
}
Int64 calcG(Int64 p, const std::vector<Prime>& fac) {
    for(Int64 i = 2; i < p; ++i) {
        bool flag = true;
        for(int j = 0; j < fac.size(); ++j)
            if(powm(i, p / fac[j].p, p) == 1) {
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
Int64 log(const Prime& fac, Int64 b) {
    Int64 xk = 0, cpc = 1;
    for(int i = 0; i < fac.c; ++i, cpc *= fac.p) {
        Int64 k = -xk % (fac.p - 1);
        if(k < 0)
            k += fac.p - 1;
        Int64 cb = powm(powm(fac.g, k, fac.p),
                        fac.c - 1 - i, fac.p);
        xk += cpc * lookUp(cb, fac.g, fac.p, fac.map,
                           fac.bsiz);
    }
    return xk;
}
Int64 log(const std::vector<Prime>& fac, Int64 phi,
          Int64 b) {
    Int64 res = 0;
    for(auto& p : fac) {
        res = (res +
               mulm(log(p, powm(b, phi / p.pc, p.p)),
                    p.k, phi)) %
            phi;
    }
    return res;
}
void PohligHellman(int t, Int64 p) {
    Int64 phi = p - 1;
    auto pf = fac(phi);
    Int64 g = calcG(p, pf);
    for(size_t i = 0; i < pf.size(); ++i) {
        Prime& cp = pf[i];
        cp.bsiz = sqrt(t * cp.p) + 1;
        cp.maxb = cp.p / cp.bsiz + 1;
        cp.g = powm(powm(g, phi / cp.pc, cp.p),
                    cp.pc / cp.p, cp.p);
        Int64 base = powm(cp.g, cp.bsiz, cp.p);
        for(Int64 cur = base, i = 1; i <= cp.maxb;
            ++i, cur = mulm(cur, base, cp.p)) {
            if(!cp.map.count(cur))
                cp.map[cur] = i;
        }
        cp.k =
            powm(phi / cp.pc,
                 cp.pc / cp.p * (cp.p - 1) - 1, cp.pc);
    }
    for(int i = 0; i < t; ++i) {
        Int64 a, b;
        scanf("%lld%lld", &a, &b);
        Int64 lga = log(pf, phi, a),
              lgb = log(pf, phi, b);
        printf("%lld\n", solve(lga, lgb, phi));
    }
}
int main() {
    int t;
    Int64 p;
    scanf("%d%lld", &t, &p);
    PohligHellman(t, p);
    return 0;
}
