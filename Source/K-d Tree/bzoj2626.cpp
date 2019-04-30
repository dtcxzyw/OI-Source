#include <algorithm>
#include <cstdio>
#include <set>
namespace IO {
    char in[1 << 22];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
}
typedef long long Int64;
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
const int size = 100005;
struct Pos {
    int id, x, y;
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
struct Info {
    Int64 d;
    int u;
    Info(Int64 d, int u) : d(d), u(u) {}
    bool operator<(const Info& rhs) const {
        if(d != rhs.d)
            return d < rhs.d;
        return u > rhs.u;
    }
};
typedef std::set<Info> Heap;
Heap cur;
void query(const Pos& p, int u) {
    if(u == 0)
        return;
    {
        Info md(dist(p, P[u]), P[u].id);
        if(*cur.begin() < md) {
            cur.erase(cur.begin());
            cur.insert(md);
        }
    }
    Int64 lv = T[ls].evalMax(p), rv = T[rs].evalMax(p);
    if(lv > rv) {
        if(lv >= cur.begin()->d)
            query(p, ls);
        if(rv >= cur.begin()->d)
            query(p, rs);
    } else {
        if(rv >= cur.begin()->d)
            query(p, rs);
        if(lv >= cur.begin()->d)
            query(p, ls);
    }
}
int main() {
    IO::init();
    int n = read();
    for(int i = 1; i <= n; ++i) {
        P[i].id = i;
        P[i].x = read();
        P[i].y = read();
    }
    int rt = build(1, n, false);
    int m = read();
    for(int i = 0; i < m; ++i) {
        Pos p;
        p.x = read();
        p.y = read();
        int k = read();
        cur.clear();
        for(int j = 0; j < k; ++j)
            cur.insert(Info(-1, -j));
        query(p, rt);
        printf("%d\n", cur.begin()->u);
    }
    return 0;
}
