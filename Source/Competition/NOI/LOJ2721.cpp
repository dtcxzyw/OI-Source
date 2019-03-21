#include <algorithm>
#include <cstdio>
#include <set>
namespace IO {
    const int size = 1 << 24;
    char buf[size];
    void init() {
        fread(buf, 1, size, stdin);
    }
    char getc() {
        static char* S = buf;
        return *S++;
    }
}
typedef long long Int64;
template <typename T>
T read() {
    T res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
Int64 mulm(Int64 a, Int64 b, Int64 m) {
    Int64 res = a * b -
        static_cast<Int64>(
            static_cast<long double>(a) / m * b) *
            m;
    return res < 0 ? res + m : res;
}
const int size = 100005;
int choose(std::multiset<int>& ATK, int A, int G) {
    std::multiset<int>::iterator it =
        ATK.upper_bound(A);
    if(it != ATK.begin())
        --it;
    int res = *it;
    ATK.erase(it);
    ATK.insert(G);
    return res;
}
struct Expr {
    Int64 a, p;
    Expr() : p(0) {}
    Expr(Int64 a, Int64 p) : a(a), p(p) {}
    Int64 getX(Int64 minv) const {
        Int64 d = std::max(minv - a, 0LL);
        Int64 k = (d + p - 1) / p;
        return a + k * p;
    }
};
void exgcd(Int64 a, Int64 b, Int64& x, Int64& y,
           Int64& d) {
    if(b) {
        exgcd(b, a % b, y, x, d);
        y -= a / b * x;
    } else
        d = a, x = 1, y = 0;
}
Expr merge(const Expr& A, const Expr& B) {
    Int64 x, y, d;
    exgcd(A.p, B.p, x, y, d);
    Int64 sum = A.a - B.a;
    if(sum % d)
        return Expr();
    Int64 fac = sum / d;
    Int64 p = A.p / d * B.p;
    if(x < 0)
        x += p;
    if(fac < 0)
        fac += p;
    Int64 x0 =
        (A.a - mulm(mulm(x, fac, p), A.p, p)) % p;
    if(x0 < 0)
        x0 += p;
    return Expr(x0, p);
}
Expr calcExpr(Int64 A, Int64 B, Int64 P) {
    Int64 x, y, d;
    exgcd(A, P, x, y, d);
    if(B % d)
        return Expr();
    Int64 fac = B / d;
    Int64 p = P / d;
    if(x < 0)
        x += p;
    Int64 a = mulm(fac, x, p);
    return Expr(a, p);
}
Int64 A[size], P[size];
int G[size];
Int64 foo() {
    int n = read<int>();
    int m = read<int>();
    for(int i = 1; i <= n; ++i)
        A[i] = read<Int64>();
    for(int i = 1; i <= n; ++i)
        P[i] = read<Int64>();
    for(int i = 1; i <= n; ++i)
        G[i] = read<int>();
    std::multiset<int> ATK;
    for(int i = 1; i <= m; ++i)
        ATK.insert(read<int>());
    Expr cur(0, 1);
    Int64 minv = 0;
    for(int i = 1; i <= n; ++i) {
        int catk = choose(
            ATK, std::min(A[i], 1000005LL), G[i]);
        Expr now =
            calcExpr(catk % P[i], A[i] % P[i], P[i]);
        if(now.p == 0)
            return -1;
        cur = merge(cur, now);
        if(cur.p == 0)
            return -1;
        minv =
            std::max(minv, (A[i] + catk - 1) / catk);
    }
    return cur.getX(minv);
}
int main() {
    freopen("dragon.in", "r", stdin);
    freopen("dragon.out", "w", stdout);
    IO::init();
    int t = read<int>();
    for(int i = 1; i <= t; ++i)
        printf("%lld\n", foo());
    return 0;
}
