#include <algorithm>
#include <cstdio>
using Int64 = long long;
#define asInt64 static_cast<Int64>
inline Int64 addm(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a < mod ? a : a - mod;
}
inline Int64 mulm(Int64 a, Int64 b, Int64 mod) {
    return (a * b -
            asInt64(static_cast<long double>(a) / mod *
                    b) *
                mod +
            mod) %
        mod;
}
Int64 powm(Int64 a, Int64 k, Int64 mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = mulm(res, a, mod);
        k >>= 1, a = mulm(a, a, mod);
    }
    return res;
}
void next(Int64& v, Int64& x, Int64& y, Int64 p,
          Int64 phi, Int64 a, Int64 b) {
    switch(v % 3) {
        case 0:
            v = mulm(v, v, p), x = addm(x, x, phi),
            y = addm(y, y, phi);
            break;
        case 1:
            v = mulm(v, a, p), x = addm(x, 1, phi);
            break;
        case 2:
            v = mulm(v, b, p), y = addm(y, 1, phi);
            break;
    }
}
void exgcd(Int64 a, Int64 b, Int64& d, Int64& x,
           Int64& y) {
    if(b) {
        exgcd(b, a % b, d, y, x);
        y -= a / b * x;
    } else
        x = 1, y = 0, d = a;
}
std::pair<Int64, Int64> solve(Int64 a, Int64 b,
                              Int64 p) {
    Int64 d, x, y;
    exgcd(a, p, d, x, y);
    if(b % d)
        return std::make_pair(-1LL, 0LL);
    Int64 modv = p / d;
    if(modv < 0)
        modv = -modv;
    x %= modv;
    if(x < 0)
        x += modv;
    Int64 c = (b / d) % modv;
    if(c < 0)
        c += modv;
    return std::make_pair(mulm(x, c, modv), modv);
}
Int64 PollardRho(Int64 a, Int64 b, Int64 p) {
    a %= p, b %= p;
    Int64 phi = p - 1;
    Int64 v1 = 1, x1 = 0, y1 = 0;
    Int64 v2 = 1, x2 = 0, y2 = 0;
    for(Int64 i = 0; i < phi; ++i) {
        next(v1, x1, y1, p, phi, a, b);
        next(v2, x2, y2, p, phi, a, b);
        next(v2, x2, y2, p, phi, a, b);
        if(v1 == v2) {
            Int64 ka = x1 - x2;
            if(ka < 0)
                ka += phi;
            Int64 kb = y2 - y1;
            if(kb < 0)
                kb += phi;
            auto pair = solve(kb, ka, phi);
            if(pair.first == -1)
                return -1;
            for(Int64 x = pair.first; x < phi;
                x += pair.second)
                if(powm(a, x, p) == b)
                    return x;
            return -1;
        }
    }
    return -1;
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
Int64 solveDL(Int64 a, Int64 b, Int64 p, Int64 g) {
    Int64 phi = p - 1;
    Int64 lga = PollardRho(g, a, p);
    if(lga == -1)
        return -1;
    Int64 lgb = PollardRho(g, b, p);
    if(lgb == -1)
        return -1;
    return solve(lga, lgb, phi).first;
}
int main() {
    int t;
    Int64 p;
    scanf("%d%lld", &t, &p);
    Int64 g = calcG(p);
    for(int i = 0; i < t; ++i) {
        Int64 a, b;
        scanf("%lld%lld", &a, &b);
        printf("%lld\n", solveDL(a, b, p, g));
    }
    return 0;
}
