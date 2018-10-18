// P1742
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
const int size = 100005;
typedef double FT;
const FT eps = 1e-12;
FT read() {
    char buf[32];
    int cnt = 0, c;
    do
        c = getchar();
    while(!isgraph(c));
    while(isgraph(c)) {
        buf[cnt++] = c;
        c = getchar();
    }
    buf[cnt] = '\0';
    return strtod(buf, 0);
}
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
    Vec operator*(FT k) const {
        return Vec(x * k, y * k);
    }
    FT length2() const {
        return x * x + y * y;
    }
} P[size];
FT cross(const Vec& a, const Vec& b) {
    return a.x * b.y - b.x * a.y;
}
struct Circle {
    Vec c;
    FT r2;
    Circle(const Vec& c, FT r2) : c(c), r2(r2 + eps) {}
    bool out(const Vec& p) const {
        return (p - c).length2() > r2;
    }
};
Circle makeCircle(const Vec& a, const Vec& b) {
    Vec mid = (a + b) * 0.5;
    return Circle(mid, (a - mid).length2());
}
struct Line {
    Vec ori, dir;
    Line(const Vec& a, const Vec& b) {
        ori = (a + b) * 0.5;
        Vec delta = a - b;
        dir = Vec(-delta.y, delta.x);
    }
};
Vec intersect(const Line& a, const Line& b) {
    Vec delta = a.ori - b.ori;
    FT t = cross(b.dir, delta) / cross(a.dir, b.dir);
    return a.ori + a.dir * t;
}
Circle makeCircle(const Vec& a, const Vec& b,
                  const Vec& c) {
    Line ab(a, b), ac(a, c);
    if(fabs(cross(ab.dir, ac.dir)) < eps) {
        FT dab = (a - b).length2(),
           dac = (a - c).length2(),
           dbc = (b - c).length2();
        FT maxd = fmax(dab, fmax(dac, dbc));
        if(maxd == dab)
            return makeCircle(a, b);
        if(maxd == dac)
            return makeCircle(a, c);
        return makeCircle(b, c);
    }
    Vec o = intersect(ab, ac);
    return Circle(o, (a - o).length2());
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        P[i].x = read();
        P[i].y = read();
    }
    std::random_shuffle(P, P + n);
    Circle c(Vec(1e10, 1e10), 0.0);
    for(int i = 0; i < n; ++i) {
        if(c.out(P[i])) {
            c = Circle(P[i], 0.0);
            for(int j = 0; j < i; ++j) {
                if(c.out(P[j])) {
                    c = makeCircle(P[i], P[j]);
                    for(int k = 0; k < j; ++k) {
                        if(c.out(P[k]))
                            c = makeCircle(P[i], P[j],
                                           P[k]);
                    }
                }
            }
        }
    }
    printf("%.10lf\n%.10lf %.10lf\n", sqrt(c.r2),
           c.c.x, c.c.y);
    return 0;
}
