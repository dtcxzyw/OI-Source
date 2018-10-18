// SP8119
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
typedef double FT;
const FT eps = 1e-8, pi = acos(-1.0);
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
    Vec operator/(FT k) const {
        return Vec(x / k, y / k);
    }
    FT length2() const {
        return x * x + y * y;
    }
    FT angle() const {
        return atan2(y, x);
    }
};
FT dis(const Vec& a, const Vec& b) {
    return sqrt((a - b).length2());
}
FT cross(const Vec& a, const Vec& b) {
    return a.x * b.y - b.x * a.y;
}
struct Range {
    FT beg, end;
    Range(FT beg, FT end) : beg(beg), end(end) {}
};
const int size = 1005;
struct Circle {
    Vec p;
    FT r;
    int c;
    std::vector<Range> range;
    bool operator<(const Circle& rhs) const {
        return r < rhs.r;
    }
    FT area2(FT x) const {
        return r * r * (x - sin(x));
    }
    Vec operator()(FT angle) const {
        return p + Vec(cos(angle) * r, sin(angle) * r);
    }
} C[size];
void addRange(Circle& c, const Vec& beg,
              const Vec& end) {
    FT ba = (beg - c.p).angle(),
       ea = (end - c.p).angle();
    if(fabs(ea - ba) > eps) {
        if(ea > ba)
            c.range.push_back(Range(ba, ea));
        else {
            c.range.push_back(Range(ba, pi));
            c.range.push_back(Range(-pi, ea));
        }
    }
}
void intersect(Circle& a, Circle& b) {
    FT dab = dis(a.p, b.p);
    if(dab > a.r + b.r - eps)
        return;
    if(dab < fabs(a.r - b.r) + eps) {
        if(a.r - b.r > -eps)
            ++b.c;
        if(b.r - a.r > -eps)
            ++a.c;
        return;
    }
    FT dac = (dab * dab + a.r * a.r - b.r * b.r) /
        (2.0 * dab);
    FT dec = sqrt(a.r * a.r - dac * dac);
    Vec base = (b.p - a.p) / dab;
    Vec c = a.p + base * dac;
    Vec off(-base.y * dec, base.x * dec);
    Vec p1 = c + off, p2 = c - off;
    addRange(a, p2, p1);
    addRange(b, p1, p2);
}
FT ans[size], mr[size * 2];
int sum[size * 2];
bool cmpEq(FT a, FT b) {
    return fabs(a - b) < eps;
}
bool cmpLe(FT a, FT b) {
    return b - a > eps;
}
int find(int siz, FT x) {
    return std::lower_bound(mr, mr + siz, x, cmpLe) -
        mr;
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%lf%lf%lf", &C[i].p.x, &C[i].p.y,
              &C[i].r);
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            intersect(C[i], C[j]);
    for(int i = 0; i < n; ++i) {
        if(C[i].range.size()) {
            std::vector<Range>& r = C[i].range;
            int cnt = 2;
            mr[0] = -pi, mr[1] = pi;
            for(int j = 0; j < r.size(); ++j) {
                mr[cnt++] = r[j].beg;
                mr[cnt++] = r[j].end;
            }
            memset(sum, 0, sizeof(int) * cnt);
            std::sort(mr, mr + cnt);
            cnt =
                std::unique(mr, mr + cnt, cmpEq) - mr;
            for(int j = 0; j < r.size(); ++j) {
                ++sum[find(cnt, r[j].beg)];
                --sum[find(cnt, r[j].end)];
            }
            int c = C[i].c;
            for(int j = 1; j < cnt; ++j) {
                FT b = mr[j - 1], e = mr[j];
                c += sum[j - 1];
                Vec beg = C[i](b), end = C[i](e);
                ans[c] += cross(beg, end);
                ans[c] += C[i].area2(e - b);
            }
        } else
            ans[C[i].c] += 2.0 * pi * C[i].r * C[i].r;
    }
    for(int i = 0; i < n; ++i)
        printf("[%d] = %.3lf\n", i + 1,
               0.5 * (ans[i] - ans[i + 1]));
    return 0;
}
