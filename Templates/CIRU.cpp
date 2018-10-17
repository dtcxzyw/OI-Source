// SP8073
#include <algorithm>
#include <cmath>
#include <cstdio>
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
    bool operator<(const Range& rhs) const {
        return fabs(beg - rhs.beg) > eps ?
            beg < rhs.beg :
            end < rhs.end;
    }
};
const int size = 1005;
struct Circle {
    Vec p;
    FT r;
    std::vector<Range> range;
    bool operator<(const Circle& rhs) const {
        return r < rhs.r;
    }
    FT area2(FT x) const {
        return r * r * (x - sin(x));
    }
    bool test(const Circle& rhs) const {
        FT dr = rhs.r - r;
        return (rhs.p - p).length2() <= dr * dr + eps;
    }
    Vec operator()(FT angle) const {
        return p + Vec(cos(angle) * r, sin(angle) * r);
    }
} C[size];
int filtrate(int n) {
    std::sort(C, C + n);
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        bool flag = true;
        for(int j = i + 1; j < n; ++j)
            if(C[i].test(C[j])) {
                flag = false;
                break;
            }
        if(flag)
            C[cnt++] = C[i];
    }
    return cnt;
}
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
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%lf%lf%lf", &C[i].p.x, &C[i].p.y,
              &C[i].r);
    n = filtrate(n);
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            intersect(C[i], C[j]);
    FT ans = 0.0;
    for(int i = 0; i < n; ++i) {
        if(C[i].range.size()) {
            std::vector<Range>& r = C[i].range;
            std::sort(r.begin(), r.end());
            int cnt = 1;
            for(int j = 1; j < r.size(); ++j)
                if(r[cnt - 1].end > r[j].beg - eps)
                    r[cnt - 1].end = std::max(
                        r[cnt - 1].end, r[j].end);
                else
                    r[cnt++] = r[j];
            if(r.size() == cnt)
                r.push_back(r[0]);
            else
                r[cnt] = r[0];
            for(int j = 0; j < cnt; ++j) {
                Vec beg = C[i](r[j].end),
                    end = C[i](r[j + 1].beg);
                ans += cross(beg, end);
                FT da = r[j + 1].beg - r[j].end;
                if(da < -eps)
                    da += 2.0 * pi;
                ans += C[i].area2(da);
            }
        } else
            ans += 2.0 * pi * C[i].r * C[i].r;
    }
    printf("%.3lf\n", 0.5 * ans);
    return 0;
}
