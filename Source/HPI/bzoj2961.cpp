#include <algorithm>
#include <cfloat>
#include <cstdio>
#include <cstdlib>
#include <set>
typedef double FT;
namespace IO {
    char in[1 << 24], *ip = in;
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    int readInt() {
        return strtol(ip, &ip, 10);
    }
    FT readFT() {
        return strtod(ip, &ip);
    }
}
struct Vec {
    FT x, y;
    Vec(FT x, FT y) : x(x), y(y) {}
    Vec operator+(const Vec& rhs) const {
        return Vec(x + rhs.x, y + rhs.y);
    }
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y);
    }
    bool operator<(const Vec& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
};
FT cross(const Vec& a, const Vec& b) {
    return a.x * b.y - b.x * a.y;
}
const FT eps = 1e-8, inf = 1e20, end = 10005;
typedef std::set<Vec>::iterator IterT;
IterT pre(IterT it) {
    return --it;
}
IterT nxt(IterT it) {
    return ++it;
}
void insert(std::set<Vec>& C, const Vec& c) {
    /*
    IterT r = C.lower_bound(c);
    IterT l = pre(r);
    if(cross(*r - *l, c - *l) > -eps)
        return;
    {
        IterT beg = l, end = l;
        while(l != C.begin()) {
            IterT p = pre(l);
            if(cross(*l - *p, c - *p) < eps)
                beg = l;
            else
                break;
            l = p;
        }
        C.erase(beg, end);
    }
    {
        IterT beg = r, end = r;
        while(true) {
            IterT p = nxt(r);
            if(p == C.end())
                break;
            if(cross(*r - *p, c - *p) > -eps)
                end = p;
            else
                break;
            r = p;
        }
        C.erase(beg, end);
    }
    */
    C.insert(c);
}
bool query(std::set<Vec>& C, const Vec& L) {
    /*
    FT l = -end, r = end;
    Vec dir(L.y, -L.x);
    if(dir.x < 0)
        dir.x = -dir.x;
    for(int i = 0; i < 60; ++i) {
        FT m = (l + r) / 2.0;
        IterT rp = C.lower_bound(Vec(m, 0.0));
        IterT lp = pre(rp);
        if(cross(dir, *rp - *lp) < -eps)
            l = m;
        else
            r = m;
    }
    Vec ans = *C.lower_bound(Vec(l, 0.0));
    */
    for(auto P : C) {
        if(-10001.0 <= P.x && P.x <= 10001.0) {
            if(2.0 * (L.x * P.x + L.y * P.y) + eps <
               L.x * L.x + L.y * L.y)
                return false;
        }
    }
    return true;
}
std::set<Vec> L, H;
int main() {
    IO::init();
    L.insert(Vec(-end, DBL_MAX));
    L.insert(Vec(end, DBL_MAX));
    H.insert(Vec(-end, DBL_MAX));
    H.insert(Vec(end, DBL_MAX));
    int n = IO::readInt();
    for(int i = 0; i < n; ++i) {
        int op = IO::readInt();
        FT x = IO::readFT();
        FT y = IO::readFT();
        Vec lc(x, y), hc(-x, -y);
        if(op)
            puts(query(L, lc) && query(H, hc) ? "Yes" :
                                                "No");
        else
            insert(L, lc), insert(H, hc);
        /*
                for(auto p : L)
                    printf("%lf %lf\n", p.x, p.y);
                puts("----------------");
                for(auto p : H)
                    printf("%lf %lf\n", p.x, p.y);
                puts("----------------");
                */
    }
    return 0;
}
