//P4196
#include <algorithm>
#include <cmath>
#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
typedef double FT;
const FT eps = 1e-8;
const int size = 505;
struct Vec {
    FT x, y;
    Vec() {}
    Vec(FT x, FT y) : x(x), y(y) {}
    Vec operator+(const Vec &rhs) const {
        return Vec(x + rhs.x, y + rhs.y);
    }
    Vec operator-(const Vec &rhs) const {
        return Vec(x - rhs.x, y - rhs.y);
    }
    Vec operator*(FT k) const {
        return Vec(x * k, y * k);
    }
};
FT cross(const Vec &a, const Vec &b) {
    return a.x * b.y - a.y * b.x;
}
struct Line {
    Vec ori, dir;
    FT ang;
    void init(const Vec &src, const Vec &dst) {
        ori = src;
        dir = dst - src;
        ang = atan2(dir.y, dir.x);
    }
    bool onLeft(const Vec &p) {
        return cross(dir, p - ori) > eps;
    }
    bool operator<(const Line &rhs) const {
        return ang < rhs.ang;
    }
} L[size];
Vec intersect(const Line &a, const Line &b) {
    Vec delta = a.ori - b.ori;
    FT t = cross(b.dir, delta) / cross(a.dir, b.dir);
    return a.ori + a.dir * t;
}
Vec P[size];
int q[size];
FT solve(int n) {
    std::sort(L, L + n);
    int b = 0, e = 0;
    q[0] = 0;
    for (int i = 1; i < n; ++i) {
        while (b < e && !L[i].onLeft(P[e - 1])) --e;
        while (b < e && !L[i].onLeft(P[b])) ++b;
        if (fabs(cross(L[i].dir, L[q[e]].dir)) > eps)
            q[++e] = i;
        else if (L[q[e]].onLeft(L[i].ori))
            q[e] = i;
        if (b < e) P[e - 1] = intersect(L[q[e - 1]], L[q[e]]);
    }
    while (b < e && !L[q[b]].onLeft(P[e - 1])) --e;
    if (e - b + 1 < 3) return 0.0;
    P[e] = intersect(L[q[b]], L[q[e]]);
    FT area = 0.0;
    for (int i = b + 1; i <= e; ++i) P[i] = P[i] - P[b];
    for (int i = b + 1; i < e; ++i)
        area += cross(P[i], P[i + 1]);
    return area * 0.5;
}
int main() {
    int n = read();
    int cnt = 0;
    for (int t = 0; t < n; ++t) {
        int m = read();
        for (int i = 0; i < m; ++i) {
            P[i].x = read();
            P[i].y = read();
        }
        for (int i = 0; i < m; ++i)
            L[cnt++].init(P[i], P[i + 1 < m ? i + 1 : 0]);
    }
    printf("%.3lf\n", solve(cnt));
    return 0;
}
