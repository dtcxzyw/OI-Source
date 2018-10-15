#include <cmath>
#include <cstdio>
const int size = 10005;
typedef double FT;
const FT inf = 1e20, eps = 1e-8;
struct Vec {
    FT x, y;
    Vec() {}
    Vec(FT x, FT y) : x(x), y(y) {}
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y);
    }
} P[size], latest;
FT dis(Vec a, Vec b) {
    FT dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
FT cross(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}
int sign(FT val) {
    return fabs(val) >= eps ? (val > eps ? 1 : 2) : 0;
}
struct Line {
    Vec ori, dir;
    Line(Vec beg, Vec end)
        : ori(beg), dir(end - beg) {}
    FT test(Vec p) const {
        return cross(p - ori, dir);
    }
};
FT ans = 0.0;
void quickHullImpl(int beg, int end,
                   const Line& line) {
    if(beg == end)
        return;
    FT marea = 0.0;
    Vec cv;
    for(int i = beg; i < end; ++i) {
        FT cc = line.test(P[i]);
        if(cc > marea)
            marea = cc, cv = P[i];
    }
}
void quickHull(int n) {
    Vec lv = P[0], rv = P[0];
    for(int i = 1; i < n; ++i) {
        if(P[i].x < lv.x)
            lv = P[i];
        else if(P[i].x > rv.x)
            rv = P[i];
    }
    latest = lv;
    int cp = 0;
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%lf%lf", &P[i].x, &P[i].y);
    quickHull(n);
    printf("%.2lf\n", ans);
    return 0;
}
