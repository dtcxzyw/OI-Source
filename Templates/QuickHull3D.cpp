// P4724
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
const int size = 2005;
typedef long double FT;
const FT eps = 1e-10;
FT getOffset() {
    static int seed = 54343;
    seed = seed * 48271LL % 2147483647;
    return seed / 2147483647.0 * 1e-12L;
}
struct Vec {
    FT x, y, z;
    Vec() {}
    Vec(FT x, FT y, FT z) : x(x), y(y), z(z) {}
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    Vec operator+(const Vec& rhs) const {
        return Vec(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    Vec operator*(FT k) const {
        return Vec(x * k, y * k, z * k);
    }
} P[size];
Vec cross(const Vec& a, const Vec& b) {
    return Vec(a.y * b.z - b.y * a.z,
               a.z * b.x - b.z * a.x,
               a.x * b.y - b.x * a.y);
}
FT dot(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
FT length2(const Vec& a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}
struct Plane {
    Vec a, b, c, N;
    Plane() {}
    Plane(const Vec& a, const Vec& b, const Vec& c)
        : a(a), b(b), c(c), N(cross(b - a, c - a)) {}
    FT area2() const {
        return sqrt(length2(N));
    }
    FT vol6(const Vec& d) const {
        Vec ad = d - a;
        return dot(N, ad);
    }
};
FT ans = 0.0;
void quickHullImpl(int beg, int end, const Plane& abc,
                   const Vec& d);
int partition(int beg, int end, const Plane& abc) {
    int mid = beg;
    FT maxv = 0.0;
    Vec d;
    for(int i = beg; i < end; ++i) {
        FT cc = abc.vol6(P[i]);
        if(cc > eps) {
            if(cc > maxv)
                d = P[i], maxv = cc;
            std::swap(P[i], P[mid++]);
        }
    }
    if(beg == mid)
        ans += abc.area2();
    else
        quickHullImpl(beg, mid, abc, d);
    return mid;
}
void quickHullImpl(int beg, int end, const Plane& abc,
                   const Vec& d) {
    beg = partition(beg, end, Plane(abc.a, abc.b, d));
    beg = partition(beg, end, Plane(abc.a, d, abc.c));
    partition(beg, end, Plane(abc.b, abc.c, d));
}
void quickHull(int n) {
    Vec lv = P[0], rv = P[0];
    for(int i = 1; i < n; ++i) {
        if(P[i].x < lv.x)
            lv = P[i];
        else if(P[i].x > rv.x)
            rv = P[i];
    }
    FT maxv = eps;
    Vec cv;
    for(int i = 0; i < n; ++i) {
        Plane cp(lv, rv, P[i]);
        FT cc = length2(cp.N);
        if(cc > maxv)
            maxv = cc, cv = P[i];
    }
    Plane bp(lv, rv, cv);
    maxv = eps;
    for(int i = 0; i < n; ++i) {
        FT cc = fabs(bp.vol6(P[i]));
        if(cc > maxv)
            maxv = cc, cv = P[i];
    }
    Vec ps[4] = { lv, rv, bp.c, cv };
    Vec mid = (lv + rv + bp.c + cv) * 0.25;
    int beg = 0;
    for(int i = 0; i < 4; ++i) {
        Vec np[3];
        int cnt = 0;
        for(int j = 0; j < 4; ++j)
            if(i != j)
                np[cnt++] = ps[j];
        Plane tp(np[0], np[1], np[2]);
        if(tp.vol6(mid) > eps)
            tp = Plane(np[0], np[2], np[1]);
        beg = partition(beg, n, tp);
    }
}
int main() {
    freopen("testdata.in", "r", stdin);
    int n;
    std::cin >> n;
    for(int i = 0; i < n; ++i) {
        std::cin >> P[i].x >> P[i].y >> P[i].z;
        P[i].x += getOffset();
        P[i].y += getOffset();
        P[i].z += getOffset();
    }
    quickHull(n);
    std::cout.precision(3);
    std::cout << std::fixed << ans * 0.5;
    return 0;
}
