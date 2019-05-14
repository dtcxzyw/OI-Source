#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
const int size = 505;
typedef double FT;
typedef long long Int64;
const FT eps = 1e-10;
struct Vec {
    Int64 x, y;
    Vec() {}
    Vec(Int64 x, Int64 y) : x(x), y(y) {}
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y);
    }
} P[size], latest;
FT dis(const Vec& a, const Vec& b) {
    Int64 dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
Int64 cross(const Vec& a, const Vec& b) {
    return a.x * b.y - a.y * b.x;
}
struct Line {
    Vec ori, dst, dir;
    Line(const Vec& a, const Vec& b)
        : ori(a), dst(b), dir(b - a) {}
    Int64 test(const Vec& p) const {
        return cross(p - ori, dir);
    }
};
FT res = 0.0;
void update(const Vec& p) {
    res += dis(latest, p);
    latest = p;
}
void quickHullImpl(int b, int e, const Line& line) {
    if(b == e)
        return;
    Int64 mval = 0;
    Vec mv;
    for(int i = b; i < e; ++i) {
        Int64 cv = line.test(P[i]);
        if(cv > mval)
            mval = cv, mv = P[i];
    }
    int le = b, rb = e;
    Line ac(line.ori, mv), cb(mv, line.dst);
    for(int i = b; i < e;) {
        if(cb.test(P[i]) > 0)
            std::swap(P[--rb], P[i]);
        else {
            if(ac.test(P[i]) > 0)
                std::swap(P[le++], P[i]);
            ++i;
        }
    }
    quickHullImpl(b, le, ac);
    update(mv);
    quickHullImpl(rb, e, cb);
}
void quickHull(int n) {
    srand(time(0));
    std::random_shuffle(P + 1, P + n + 1);
    Vec a = P[1], b = P[1];
    for(int i = 1; i <= n; ++i) {
        if(a.x > P[i].x)
            a = P[i];
        else if(b.x < P[i].x)
            b = P[i];
    }
    Line ab(a, b), ba(b, a);
    int le = 1, rb = n + 1;
    for(int i = 1; i <= n;) {
        Int64 tv = ab.test(P[i]);
        if(tv < 0)
            std::swap(P[--rb], P[i]);
        else {
            if(tv > 0)
                std::swap(P[le++], P[i]);
            ++i;
        }
    }
    latest = a;
    quickHullImpl(1, le, ab);
    update(b);
    quickHullImpl(rb, n + 1, ba);
    update(a);
}
int main() {
    freopen("data/fields8.in", "r", stdin);
    int n;
    scanf("%d", &n);
    int siz = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < 2; ++j) {
            ++siz;
            scanf("%lld%lld", &P[siz].x, &P[siz].y);
        }
    }
    quickHull(siz);
    printf("%.10lf\n", res);
    return 0;
}
