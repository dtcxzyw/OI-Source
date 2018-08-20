// P3187
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
typedef double FT;
const FT eps = 1e-8;
struct Vec {
    FT x, y;
    Vec() {}
    Vec(FT x, FT y) : x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    Vec operator+(const Vec& rhs) const {
        return Vec(x + rhs.x, y + rhs.y);
    }
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y);
    }
    Vec operator*(FT k) const {
        return Vec(x * k, y * k);
    }
};
FT cross(const Vec& a, const Vec& b) {
    return a.x * b.y - a.y * b.x;
}
FT dot(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y;
}
const int size = 50005;
Vec P[size], V[size];
bool cmpX(const Vec& a, const Vec& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}
bool cmpY(const Vec& a, const Vec& b) {
    return a.y != b.y ? a.y < b.y : a.x < b.x;
}
int convex(int n) {
    std::sort(P, P + n, cmpX);
    V[0] = P[0];
    int cnt = 1;
    for(int i = 1; i < n; ++i) {
        while(cnt >= 2 &&
              cross(P[i] - V[cnt - 2], V[cnt - 1] - V[cnt - 2]) >=
                  0.0)
            --cnt;
        V[cnt++] = P[i];
    }
    int end = cnt + 1;
    for(int i = n - 2; i >= 1; --i) {
        while(cnt >= end &&
              cross(P[i] - V[cnt - 2], V[cnt - 1] - V[cnt - 2]) >=
                  0.0)
            --cnt;
        V[cnt++] = P[i];
    }
    return cnt;
}
struct Angle {
    FT x, y, angle;
    Angle() : angle(1e10) {}
    Angle(FT x, FT y) : x(x), y(y), angle(atan2(y, x)) {}
    bool operator<(const Angle& rhs) const {
        return angle < rhs.angle;
    }
};
struct Line {
    int base;
    Vec dir;
    Line() {}
    Line(int base, const Vec& dir) : base(base), dir(dir) {}
    Vec intersect(const Line& rhs) const {
        Vec delta = V[base] - V[rhs.base];
        FT t = cross(rhs.dir, delta) / cross(dir, rhs.dir);
        return V[base] + dir * t;
    }
    Angle calcAngle(int n) const {
        int nxt = base + 1;
        if(nxt == n)
            nxt = 0;
        Vec delta = V[nxt] - V[base];
        return Angle(dot(dir, delta), cross(dir, delta));
    }
    void rotate(const Angle& angle, int n) {
        int nxt = base + 1;
        if(nxt == n)
            nxt = 0;
        Vec delta = V[nxt] - V[base];
        dir = Vec(dir.x * angle.x - dir.y * angle.y,
                  dir.x * angle.y + dir.y * angle.x);
        if(fabs(cross(delta, dir)) < eps) {
            dir = delta;
            base = nxt;
        }
    }
} L[4], res[4];
FT area(Line* S) {
    Vec P[3];
    for(int i = 0; i < 3; ++i)
        P[i] = S[i].intersect(S[i + 1]);
    return cross(P[1] - P[0], P[2] - P[0]);
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        P[i].read();
    n = convex(n);
    int maxX = 0, minX = 0, maxY = 0, minY = 0;
    for(int i = 1; i < n; ++i) {
        if(V[i].x > V[maxX].x)
            maxX = i;
        else if(V[i].x < V[minX].x)
            minX = i;
        if(V[i].y > V[maxY].y)
            maxY = i;
        else if(V[i].y < V[minY].y)
            minY = i;
    }
    L[0] = Line(minY, Vec(1.0, 0.0));
    L[1] = Line(maxX, Vec(0.0, 1.0));
    L[2] = Line(maxY, Vec(-1.0, 0.0));
    L[3] = Line(minX, Vec(0.0, -1.0));
    memcpy(res, L, sizeof(L));
    FT ans = area(res);
    while(L[0].dir.x >= 0.0) {
        Angle angle;
        for(int i = 0; i < 4; ++i)
            angle = std::min(angle, L[i].calcAngle(n));
        for(int i = 0; i < 4; ++i)
            L[i].rotate(angle, n);
        FT carea = area(L);
        if(carea < ans) {
            ans = carea;
            memcpy(res, L, sizeof(L));
        }
    }
    printf("%.5lf\n", ans);
    Vec resP[4];
    for(int i = 0; i < 4; ++i)
        resP[i] = res[i].intersect(res[(i + 1) % 4]);
    int beg = 0;
    for(int i = 1; i < 4; ++i)
        if(cmpY(resP[i], resP[beg]))
            beg = i;
    for(int i = 0; i < 4; ++i) {
        int id = (i + beg) % 4;
        printf("%.5lf %.5lf\n", resP[id].x + eps, resP[id].y + eps);
    }
    return 0;
}
