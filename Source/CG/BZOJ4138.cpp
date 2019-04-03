#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
const int size = 1005;
typedef long double FT;
const FT eps = 1e-8L;
struct Vec {
    FT x, y;
    Vec() {}
    Vec(FT x, FT y) : x(x), y(y) {}
    Vec operator+(const Vec& rhs) const {
        return Vec(x + rhs.x, y + rhs.y);
    }
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y);
    }
    FT length2() const {
        return x * x + y * y;
    }
    Vec rotate(FT cx, FT cy) const {
        return Vec(x * cx - y * cy, x * cy + y * cx);
    }
    bool operator<(const Vec& rhs) const {
        return x < rhs.x;
    }
} P[size], C[size], T[size];
FT dis2(const Vec& a, const Vec& b) {
    FT dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
struct Circle {
    Vec ori;
    FT r2;
    Circle(const Vec& ori, FT r2) : ori(ori), r2(r2) {}
    bool out(const Vec& p) const {
        return dis2(ori, p) > r2 + eps;
    }
};
Circle makeCircle(const Vec& a, const Vec& b) {
    Vec mid((a.x + b.x) * 0.5, (a.y + b.y) * 0.5);
    return Circle(mid, dis2(b, mid));
}
FT cross(const Vec& a, const Vec& b) {
    return a.x * b.y - b.x * a.y;
}
struct Line {
    Vec ori, dir;
    Line(const Vec& a, const Vec& b)
        : ori((a.x + b.x) * 0.5, (a.y + b.y) * 0.5),
          dir(b.y - a.y, a.x - b.x) {}
};
Vec intersect(const Line& a, const Line& b) {
    Vec delta = a.ori - b.ori;
    FT t = cross(b.dir, delta) / cross(a.dir, b.dir);
    return Vec(a.ori.x + a.dir.x * t,
               a.ori.y + a.dir.y * t);
}
Circle makeCircle(const Vec& a, const Vec& b,
                  const Vec& c) {
    Line ab(a, b), ac(a, c);
    Vec p = intersect(ab, ac);
    return Circle(
        p, std::max(dis2(a, p),
                    std::max(dis2(b, p), dis2(c, p))));
}
FT calc(int b, int e) {
    memcpy(T + b, C + b, sizeof(Vec) * (e - b));
    std::random_shuffle(T + b, T + e);
    Circle cur(Vec(0.0, 0.0), 0.0);
    for(int i = b; i < e; ++i)
        if(cur.out(T[i])) {
            cur = Circle(T[i], 0.0);
            for(int j = b; j < i; ++j)
                if(cur.out(T[j])) {
                    cur = makeCircle(T[i], T[j]);
                    for(int k = b; k < j; ++k)
                        if(cur.out(T[k]))
                            cur = makeCircle(
                                T[i], T[j], T[k]);
                }
        }
    return cur.r2;
}
FT ans;
void solve(FT angle, int n) {
    FT cx = cos(angle), cy = sin(angle);
    for(int i = 0; i < n; ++i)
        C[i] = P[i].rotate(cx, cy);
    std::sort(C, C + n);
    int l = 1, r = n - 1;
    while(l <= r) {
        int m = (l + r) >> 1;
        FT r1 = calc(0, m), r2 = calc(m, n);
        if(std::min(r1, r2) >= ans)
            break;
        ans = std::min(ans, std::max(r1, r2));
        if(r1 < r2)
            l = m + 1;
        else
            r = m - 1;
    }
}
int main() {
    srand(time(0));
    while(true) {
        int n;
        scanf("%d", &n);
        if(n == 0)
            break;
        for(int i = 0; i < n; ++i)
            scanf("%Lf%Lf", &P[i].x, &P[i].y);
        ans = 1e20;
        const int step = 160;
        const FT pi = acos(-1.0);
        for(FT i = 0.0; i < step; ++i)
            solve(pi * i / step, n);
        printf("%.2Lf\n", sqrtl(ans));
    }
    return 0;
}
