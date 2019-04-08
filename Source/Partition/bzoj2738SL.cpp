#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
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
const int size = 505, maxq = 60005;
int n, S[size];
void add(int x) {
    while(x <= n) {
        ++S[x];
        x += x & -x;
    }
}
int query(int x) {
    int res = 0;
    while(x) {
        res += S[x];
        x -= x & -x;
    }
    return res;
}
void clear(int x) {
    while(x <= n) {
        if(S[x])
            S[x] = 0;
        else
            break;
        x += x & -x;
    }
}
struct Point {
    int x, y, z;
    bool operator<(const Point& rhs) const {
        return z < rhs.z;
    }
} P[size * size];
int find(int l, int r, int x) {
    int ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(P[m].z <= x)
            l = m + 1, ans = m;
        else
            r = m - 1;
    }
    return ans;
}
struct Query {
    int x1, y1, x2, y2, k, id;
} Q[maxq];
int ans[maxq];
struct Line {
    int op, by, ey, id;
    Line(int op, int by, int ey, int id)
        : op(op), by(by), ey(ey), id(id) {}
};
int tmp[maxq];
void solve(int l, int r, int pl, int pr, int ql,
           int qr) {
    if(ql > qr)
        return;
    if(l == r) {
        for(int i = ql; i <= qr; ++i)
            ans[Q[i].id] = l;
    } else {
        int m = (l + r) >> 1;
        int pm = find(pl, pr, m);
        std::map<int, std::vector<int> > X;
        for(int i = pl; i <= pm; ++i)
            X[P[i].x].push_back(P[i].y);
        std::map<int, std::vector<Line> > Y;
        for(int i = ql; i <= qr; ++i) {
            tmp[i] = 0;
            Y[Q[i].x1].push_back(
                Line(-1, Q[i].y1, Q[i].y2, i));
            Y[Q[i].x2].push_back(
                Line(1, Q[i].y1, Q[i].y2, i));
        }
        {
            auto cur = X.begin();
            for(const auto& task : Y) {
                while(cur != X.end() &&
                      cur->first <= task.first) {
                    for(auto y : cur->second)
                        add(y);
                    ++cur;
                }
                for(const auto& line : task.second) {
                    int cnt = query(line.ey) -
                        query(line.by);
                    tmp[line.id] += line.op * cnt;
                }
            }
            for(const auto& task : X)
                for(auto y : task.second)
                    clear(y);
        }
        int cur = ql;
        for(int i = ql; i <= qr; ++i) {
            if(Q[i].k > tmp[i])
                Q[i].k -= tmp[i];
            else
                std::swap(Q[cur++], Q[i]);
        }
        solve(l, m, pl, pm, ql, cur - 1);
        solve(m + 1, r, pm + 1, pr, cur, qr);
    }
}
int X[size * size];
int main() {
    n = read();
    int q = read();
    int siz = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int id = ++siz;
            P[id].x = i, P[id].y = j, P[id].z = read();
            X[id] = P[id].z;
        }
    }
    std::sort(X + 1, X + siz + 1);
    siz = std::unique(X + 1, X + siz + 1) - (X + 1);
    int tot = n * n;
    for(int i = 1; i <= tot; ++i)
        P[i].z = std::lower_bound(X + 1, X + siz + 1,
                                  P[i].z) -
            X;
    std::sort(P + 1, P + tot + 1);
    for(int i = 1; i <= q; ++i) {
        Q[i].id = i;
        Q[i].x1 = read() - 1;
        Q[i].y1 = read() - 1;
        Q[i].x2 = read();
        Q[i].y2 = read();
        Q[i].k = read();
    }
    solve(1, siz, 1, tot, 1, q);
    for(int i = 1; i <= q; ++i)
        printf("%d\n", X[ans[i]]);
    return 0;
}
