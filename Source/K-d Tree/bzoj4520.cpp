#include <algorithm>
#include <climits>
#include <cstdio>
#include <queue>
#include <set>
typedef long long Int64;
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 100005;
struct Pos {
    int x, y;
} P[size];
Int64 dist(const Pos& a, const Pos& b) {
    Int64 dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
bool cmpX(const Pos& a, const Pos& b) {
    return a.x < b.x;
}
bool cmpY(const Pos& a, const Pos& b) {
    return a.y < b.y;
}
struct Node {
    int l, r, minx, maxx, miny, maxy;
    void update(const Node& rhs) {
        minx = std::min(minx, rhs.minx);
        maxx = std::max(maxx, rhs.maxx);
        miny = std::min(miny, rhs.miny);
        maxy = std::max(maxy, rhs.maxy);
    }
    Int64 evalMax(const Pos& a) const {
        Int64 dx1 = minx - a.x, dx2 = maxx - a.x;
        Int64 dy1 = miny - a.y, dy2 = maxy - a.y;
        return std::max(dx1 * dx1, dx2 * dx2) +
            std::max(dy1 * dy1, dy2 * dy2);
    }
} T[size];
#define ls T[u].l
#define rs T[u].r
int build(int l, int r, bool axis) {
    if(l > r)
        return 0;
    int m = (l + r) >> 1;
    std::nth_element(P + l, P + m, P + r + 1,
                     axis ? cmpX : cmpY);
    T[m].minx = T[m].maxx = P[m].x;
    T[m].miny = T[m].maxy = P[m].y;
    axis ^= 1;
    T[m].l = build(l, m - 1, axis);
    T[m].r = build(m + 1, r, axis);
    if(T[m].l)
        T[m].update(T[T[m].l]);
    if(T[m].r)
        T[m].update(T[T[m].r]);
    return m;
}
Int64 cur;
int pair;
std::set<Int64> sec;
Int64 makePair(Int64 a, Int64 b) {
    if(a < b)
        std::swap(a, b);
    return a << 20 | b;
}
void query(int id, int u) {
    if(u == 0)
        return;
    {
        Int64 md = dist(P[id], P[u]);
        if(md > cur && !sec.count(makePair(id, u)))
            cur = md, pair = u;
    }
    Int64 lv = T[ls].evalMax(P[id]),
          rv = T[rs].evalMax(P[id]);
    if(lv > rv) {
        if(lv > cur)
            query(id, ls);
        if(rv > cur)
            query(id, rs);
    } else {
        if(rv > cur)
            query(id, rs);
        if(lv > cur)
            query(id, ls);
    }
}
struct Info {
    int u, v;
    Int64 d;
    Info(int u, int v, Int64 d) : u(u), v(v), d(d) {}
    bool operator<(const Info& rhs) const {
        if(d != rhs.d)
            return d < rhs.d;
        return u < rhs.u;
    }
};
int main() {
    int n = read();
    int k = read();
    for(int i = 1; i <= n; ++i) {
        P[i].x = read();
        P[i].y = read();
    }
    int rt = build(1, n, false);
    std::priority_queue<Info> heap;
    for(int i = 1; i <= n; ++i) {
        cur = pair = -1;
        query(i, rt);
        if(pair != -1)
            heap.push(Info(i, pair, cur));
    }
    for(int i = 1; i <= k; ++i) {
        Info top = heap.top();
        heap.pop();
        cur = pair = -1;
        query(top.u, rt);
        if(pair != -1)
            heap.push(Info(top.u, pair, cur));
        if(!sec.insert(makePair(top.u, top.v))
                .second) {
            --i;
            continue;
        }
        if(i == k) {
            printf("%lld\n", top.d);
            break;
        }
    }
    return 0;
}
