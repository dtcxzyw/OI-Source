#include <algorithm>
#include <cmath>
#include <cstdio>
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
#define asFloat static_cast<FT>
const FT eps = 1e-8, minx = -5.0, maxx = 1e6 + 5.0;
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
};
const int size = 100005;
struct Line {
    int k;
    Int64 b;
    Line() {}
    Line(int k, Int64 b) : k(k), b(b) {}
    Vec operator()(FT t) const {
        return Vec(t, b + k * t);
    }
    bool operator<(const Line& rhs) const {
        return k > rhs.k;
    }
    bool onRight(Vec p) const {
        return k * p.x + b > p.y + eps;
    }
} L[size];
Vec intersect(const Line& a, const Line& b) {
    FT x = asFloat(b.b - a.b) / asFloat(a.k - b.k);
    return Vec(x, x * a.k + a.b);
}
int q[size];
Vec P[size];
void rebuild(std::vector<Vec>& ps,
             std::vector<int>& ls, int l, int r) {
    int b = 1, e = 1;
    q[1] = l;
    for(int i = l + 1; i <= r; ++i) {
        while(b < e && !L[i].onRight(P[e - 1]))
            --e;
        if(L[i].k != L[q[e]].k)
            q[++e] = i;
        else if(L[q[e]].b > L[i].b)
            q[e] = i;
        if(b < e)
            P[e - 1] = intersect(L[q[e]], L[q[e - 1]]);
    }
    P[b - 1] = Vec(minx, L[q[b]].k * minx + L[q[b]].b);
    P[e] = Vec(maxx, L[q[e]].k * maxx + L[q[e]].b);
    ps.assign(P + b - 1, P + e + 1);
    ls.clear();
    for(int i = b; i <= e; ++i)
        ls.push_back(q[i]);
}
std::vector<Vec> S[20];
std::vector<int> LS[20];
int cnt = 0, cl = 0;
void insert(int k, Int64 b) {
    L[cnt] = Line(k, b);
    ++cnt, ++cl;
    int rsiz = cnt & -cnt;
    for(int i = 1; i < rsiz; i <<= 1, --cl)
        std::inplace_merge(L + cnt - i * 2,
                           L + cnt - i, L + cnt);
    rebuild(S[cl], LS[cl], cnt - rsiz, cnt - 1);
}
Int64 query(int x) {
    Int64 res = 1LL << 60;
    for(int i = 1; i <= cl; ++i) {
        int l = 0, r = S[i].size() - 1, p = 0;
        while(l <= r) {
            int m = (l + r) >> 1;
            if(S[i][m].x <= x)
                l = m + 1, p = m;
            else
                r = m - 1;
        }
        Line cl = L[LS[i][p]];
        res = std::min(res, asInt64(x) * cl.k + cl.b);
    }
    return res;
}
int h[size];
Int64 w[size];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        h[i] = read();
    for(int i = 1; i <= n; ++i)
        w[i] = w[i - 1] + read();
    insert(-2 * h[1], asInt64(h[1]) * h[1] - w[1]);
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
