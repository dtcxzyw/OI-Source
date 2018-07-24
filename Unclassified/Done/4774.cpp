#include <cstdio>
#include <set>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
#ifdef ONLINE_JUDGE
typedef __int128 Int128;
Int64 mulm(Int128 a, Int128 b, Int128 mod) {
    return a * b % mod;
}
#else
Int64 add(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a < mod ? a : a - mod;
}
Int64 mulm(Int64 a, Int64 b, Int64 mod) {
    a %= mod, b %= mod;
    if (a < 0) a += mod;
    if (b < 0) b += mod;
    Int64 res = 0;
    while (b) {
        if (b & 1) res = add(res, a, mod);
        b >>= 1, a = add(a, a, mod);
    }
    return res;
}
#endif
void exgcd(Int64 a, Int64 b, Int64 &x, Int64 &y, Int64 &d) {
    if (b) {
        exgcd(b, a % b, y, x, d);
        y -= a / b * x;
    } else
        x = 1, y = 0, d = a;
}
const int size = 100005;
Int64 A[size], P[size], atk[size];
typedef std::multiset<Int64>::iterator IterT;
bool merge(Int64 &k, Int64 &b, Int64 a, Int64 p, Int64 atk) {
    Int64 ka = k * atk;
    Int64 x, y, d;
    exgcd(ka, p, x, y, d);
    Int64 delta = a - b * atk;
    if (delta % d) return false;
    Int64 tmod = p / d;
    Int64 t1 = mulm(x, delta / d, tmod);
    Int64 xmod = k * tmod;
    b = (mulm(t1, k, xmod) + b) % xmod;
    k = xmod;
    return true;
}
Int64 foo() {
    int n = read();
    int m = read();
    for (int i = 0; i < n; ++i) A[i] = read();
    for (int i = 0; i < n; ++i) P[i] = read();
    for (int i = 0; i < n; ++i) atk[i] = read();
    std::multiset<Int64> atks;
    for (int i = 0; i < m; ++i) atks.insert(read());
    Int64 ck = 1, cb = 0, minc = 0;
    for (int i = 0; i < n; ++i) {
        Int64 a = A[i], p = P[i];
        IterT it = atks.upper_bound(a);
        if (it != atks.begin()) --it;
        Int64 catk = *it;
        atks.erase(it);
        atks.insert(atk[i]);
        minc = std::max(minc, (a - 1) / catk + 1);
        if (!merge(ck, cb, a, p, catk)) return -1;
    }
    cb = (cb % ck + ck) % ck;
    return cb + (cb < minc ? ck * ((minc - cb - 1) / ck + 1) : 0);
}
int main() {
    int t = read();
    while (t--) printf("%lld\n", foo());
    return 0;
}
