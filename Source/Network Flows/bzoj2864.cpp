#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
typedef double FT;
const FT eps = 1e-8, inf = 1e20;
const int size = 1005;
struct Edge {
    int to, nxt;
    FT f;
} E[size * 10];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, FT f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, FT f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0.0);
}
int d[size], q[size], gap[size], S, T, nsiz;
void BFS() {
    int b = 0, e = 1;
    d[T] = 1, q[0] = T, gap[1] = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(!d[v]) {
                d[v] = d[u] + 1;
                ++gap[d[v]];
                q[e++] = v;
            }
        }
    }
    if(d[S] == 0)
        d[S] = nsiz + 1;
}
int now[size];
FT aug(int u, FT f) {
    if(u == T || f < eps)
        return f;
    FT res = 0.0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] + 1 == d[u] &&
           (k = aug(v, std::min(E[i].f, f))) > eps) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f < eps)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = nsiz + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
FT ISAP() {
    BFS();
    memcpy(now, last, sizeof(now));
    FT res = 0.0;
    while(d[S] <= nsiz)
        res += aug(S, inf);
    return res;
}
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
FT cross(const Vec& a, const Vec& b) {
    return a.x * b.y - b.x * a.y;
}
FT length(const Vec& a) {
    return sqrt(a.x * a.x + a.y * a.y);
}
struct Line {
    Vec ori, dir;
    Line() {}
    Line(const Vec& s, const Vec& t)
        : ori(s), dir(t - s) {}
    FT lerp(const Vec& p) const {
        Vec off = p - ori;
        FT t = fabs(dir.x) > fabs(dir.y) ?
            off.x / dir.x :
            off.y / dir.y;
        return std::max(0.0, std::min(1.0, t));
    }
    bool solve(const Vec& p, FT r, FT v,
               std::pair<FT, FT>& t) {
        FT d = cross(dir, p - ori) / length(dir);
        if(fabs(d) + eps > r)
            return false;
        FT off = sqrt(r * r - d * d);
        Vec voff = dir * (off / length(dir));
        Vec mid =
            p + Vec(dir.y, -dir.x) * (d / length(dir));
        t.first = lerp(mid + voff) * length(dir) / v;
        t.second = lerp(mid - voff) * length(dir) / v;
        if(t.first > t.second)
            std::swap(t.first, t.second);
        return t.second - t.first > eps;
    }
};
Vec boss[size];
std::vector<FT> TS[size];
Line L[size];
int V[size], R[size];
int main() {
    freopen("data/8.in", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%lf%lf", &boss[i].x, &boss[i].y);
    nsiz = m;
    S = ++nsiz;
    for(int i = 1; i <= m; ++i) {
        int sx, sy, ex, ey, E;
        scanf("%d%d%d%d%d%d%d", &sx, &sy, &ex, &ey,
              &V[i], &R[i], &E);
        addEdge(S, i, E);
        L[i] = Line(Vec(sx, sy), Vec(ex, ey));
        if(length(L[i].dir) < eps)
            continue;
        for(int j = 1; j <= n; ++j) {
            std::pair<FT, FT> ct;
            if(L[i].solve(boss[j], R[i], V[i], ct)) {
                TS[j].push_back(ct.first);
                TS[j].push_back(ct.second);
            }
        }
    }
    T = ++nsiz;
    for(int j = 1; j <= n; ++j) {
        std::sort(TS[j].begin(), TS[j].end());
        std::vector<int> pid;
        pid.push_back(0);
        for(int i = 1; i < TS[j].size(); ++i) {
            int id = ++nsiz;
            pid.push_back(id);
            addEdge(id, T, TS[j][i] - TS[j][i - 1]);
        }
        for(int i = 1; i <= m; ++i) {
            if(length(L[i].dir) < eps)
                continue;
            std::pair<FT, FT> ct;
            if(L[i].solve(boss[j], R[i], V[i], ct)) {
                int ps = std::lower_bound(
                             TS[j].begin(),
                             TS[j].end(), ct.first) -
                    TS[j].begin();
                int pt = std::lower_bound(
                             TS[j].begin(),
                             TS[j].end(), ct.second) -
                    TS[j].begin();
                for(int k = ps + 1; k <= pt; ++k)
                    addEdge(i, pid[k], inf);
            }
        }
    }
    printf("%.6lf\n", ISAP());
    return 0;
}
