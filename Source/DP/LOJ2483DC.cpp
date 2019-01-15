#include <cmath>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
typedef double FT;
const FT eps = 1e-8, minx = -5.0, right = 1e6,
         maxx = right + 5.0;
struct Point {
    FT x, y;
    Point(FT x, FT y) : x(x), y(y) {}
    bool operator<(const Point& rhs) const {
        return x < rhs.x - eps;
    }
};
std::set<Point> convex;
typedef std::set<Point>::iterator IterT;
std::map<int, Int64> line;
typedef std::map<int, Int64>::iterator IterLT;
Point intersect(FT l, FT r, FT yl, FT yr, FT zl,
                FT zr) {
    FT k = (zr - yr) / (yl - zl);
    FT t = k / (1.0 + k);
    return Point(t * l + (1.0 - t) * r,
                 t * yl + (1.0 - t) * yr);
}
void processPoint(FT k, FT b) {
    FT l = 0.0, r = right;
    while(r - l >= eps) {
        FT m = (l + r) * 0.5;
        IterT end = convex.upper_bound(Point(m, 0.0));
        IterT beg = end;
        --beg;
        Point lp = *beg, rp = *end;
        FT slope = (rp.y - lp.y) / (rp.x - lp.x);
        (k < slope ? l : r) = m;
    }
    IterT mid = convex.upper_bound(Point(l, 0.0));
    {
        Point p = *mid;
        if(p.x * k + b - eps > p.y)
            return;
    }
    std::vector<Point> toErase, toAdd;
    {
        IterT cur = mid, nxt = cur;
        --nxt;
        while(true) {
            if(cur == convex.begin()) {
                toErase.push_back(*cur);
                toAdd.push_back(
                    Point(minx, k * minx + b));
                break;
            }
            Point lp = *nxt, rp = *cur;
            FT ly = k * lp.x + b, ry = k * rp.x + b;
            toErase.push_back(rp);
            if(ly < lp.y && ry < rp.y)
                cur = nxt, --nxt;
            else {
                toAdd.push_back(intersect(
                    lp.x, rp.x, lp.y, rp.y, ly, ry));
                break;
            }
        }
    }
    {
        IterT cur = mid, nxt = cur;
        ++nxt;
        while(true) {
            if(nxt == convex.end()) {
                toErase.push_back(*cur);
                toAdd.push_back(
                    Point(maxx, k * maxx + b));
                break;
            }
            Point lp = *cur, rp = *nxt;
            FT ly = k * lp.x + b, ry = k * rp.x + b;
            toErase.push_back(lp);
            if(ly < lp.y && ry < rp.y)
                cur = nxt, ++nxt;
            else {
                toAdd.push_back(intersect(
                    lp.x, rp.x, lp.y, rp.y, ly, ry));
                break;
            }
        }
    }
    for(int i = 0; i < toErase.size(); ++i)
        convex.erase(toErase[i]);
    for(int i = 0; i < toAdd.size(); ++i)
        convex.insert(toAdd[i]);
}
void insert(int k, Int64 b) {
    IterLT it = line.find(k);
    if(it != line.end() && it->second < b)
        return;
    line[k] = b;
    processPoint(k, b);
}
Int64 query(int x) {
    IterT end = convex.upper_bound(Point(x, 0.0));
    IterT beg = end;
    --beg;
    Point lp = *beg, rp = *end;
    FT k = (rp.y - lp.y) / (rp.x - lp.x);
    int ik = k;
    if(ik & 1)
        ik = (k > ik ? ik + 1 : ik - 1);
    return asInt64(x) * ik + line[ik];
}
const int size = 100005;
int h[size];
Int64 w[size];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        h[i] = read();
    for(int i = 1; i <= n; ++i)
        w[i] = w[i - 1] + read();
    {
        Int64 p1 = asInt64(h[1]) * h[1] - w[1];
        convex.insert(
            Point(minx, p1 - 2 * h[1] * minx));
        convex.insert(
            Point(maxx, p1 - 2 * h[1] * maxx));
        line[-2 * h[1]] = p1;
    }
    for(int i = 2; i <= n; ++i) {
        Int64 dp = query(h[i]) + asInt64(h[i]) * h[i] +
            w[i - 1];
        if(i < n) {
            insert(-2 * h[i],
                   dp + asInt64(h[i]) * h[i] - w[i]);
        } else
            printf("%lld\n", dp);
    }
    return 0;
}
