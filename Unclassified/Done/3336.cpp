#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 1000005;
struct Point {
    int x, fx;
    bool operator<(const Point& rhs) const {
        return x < rhs.x;
    }
    bool operator==(const Point& rhs) const {
        return x == rhs.x;
    }
} P[size];
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
template <int mod>
struct Base {
    int fac[mod], inv[mod], invFac[mod];
    Base() {
        fac[0] = fac[1] = inv[1] = invFac[0] =
            invFac[1] = 1;
    }
    void pre(int x) {
        static int cx = 1;
        while(cx < x) {
            ++cx;
            fac[cx] = asInt64(fac[cx - 1]) * cx % mod;
            inv[cx] = asInt64(mod - mod / cx) *
                inv[mod % cx] % mod;
            invFac[cx] = asInt64(invFac[cx - 1]) *
                inv[cx] % mod;
        }
    }
    Int64 C(int n, int m) {
        pre(n);
        return asInt64(fac[n]) * invFac[m] % mod *
            invFac[n - m] % mod;
    }
    Int64 lucas(int n, int m) {
        Int64 res = 1;
        while(n && m && res) {
            int cn = n % mod, cm = m % mod;
            n /= mod, m /= mod;
            if(n < m)
                return 0;
            res = res * C(cn, cm) % mod;
        }
        return res;
    }
    Int64 getInv(Int64 a) {
        Int64 res = 1;
        int k = mod - 2;
        while(k) {
            if(k & 1)
                res = res * a % mod;
            k >>= 1, a = a * a % mod;
        }
        return res;
    }
    Int64 getFac(int n, int m, int k) {
        return lucas(n, m) * k * getInv(k);
    }
};
const int m1 = 7, m2 = 2848631, m3 = m1 * m2;
Base<m1> Ca;
Base<m2> Cb;
Int64 C(int n, int m) {
    if(n < m || m < 0)
        return 0;
    return (Ca.getFac(n, m, m2) +
            Cb.getFac(n, m, m1)) %
        m3;
}
Int64 count(int fl, int l, int r, int dx) {
    if(fl >= r)
        return C(dx, l);
    else {
        Int64 res = 0;
        for(int i = fl; i < r; ++i)
            res = (res +
                   (C(i, i - fl) - C(i, i - fl - 1)) *
                       C(fl + l - i, r - 1 - i)) %
                m3;
        return (C(dx, l) - res) % m3;
    }
}
void solve(Point pl, Point pr, int& maxf, int& cnt) {
    int dx = pr.x - pl.x, dy = pr.fx - pl.fx;
    int l = (dx + dy) >> 1, r = dx - l;
    maxf = std::max(maxf, pl.fx + l);
    cnt = cnt * (dy >= 0 ? count(pl.fx, l, r, dx) :
                           count(pr.fx, r, l, dx)) %
        m3;
}
int main() {
    int n = read();
    int k = read();
    for(int i = 0; i < k; ++i) {
        P[i].x = read();
        P[i].fx = read();
    }
    P[k].x = P[k].fx = P[k + 1].fx = 0;
    P[k + 1].x = n;
    k += 2;
    std::sort(P, P + k);
    k = std::unique(P, P + k) - P;
    int maxf = 0, cnt = 1;
    for(int i = 1; i < k; ++i)
        solve(P[i - 1], P[i], maxf, cnt);
    printf("%d %d\n", (cnt + m3) % m3, maxf);
    return 0;
}
