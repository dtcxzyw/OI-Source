#include <algorithm>
#include <cstdio>
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
int iabs(int x) {
    return x >= 0 ? x : -x;
}
const int size = 1000005;
struct Pos {
private:
    int c[4];

public:
    int operator[](int i) const {
        return c[i];
    }
    int& operator[](int i) {
        return c[i];
    }
} P[size];
int d;
struct Node {
    Pos p, minp, maxp;
    int ls, rs;
} T[size];
void update(Node& a, const Node& b) {
    for(int i = 0; i < d; ++i)
        a.minp[i] = std::min(a.minp[i], b.minp[i]);
    for(int i = 0; i < d; ++i)
        a.maxp[i] = std::max(a.maxp[i], b.maxp[i]);
}
int nxtAxis[4], cnt = 0;
int build(int l, int r, int axis = 0) {
    int m = (l + r) >> 1;
    std::nth_element(P + l, P + m, P + r + 1,
                     [axis](const Pos& a, const Pos& b) {
                         return a[axis] < b[axis];
                     });
    int id = ++cnt;
    T[id].maxp = T[id].minp = T[id].p = P[m];
    if(l < m) {
        T[id].ls = build(l, m - 1, nxtAxis[axis]);
        update(T[id], T[T[id].ls]);
    }
    if(m < r) {
        T[id].rs = build(m + 1, r, nxtAxis[axis]);
        update(T[id], T[T[id].rs]);
    }
    return id;
}
int distance(const Pos& a, const Pos& b) {
    int res = 0;
    for(int i = 0; i < d; ++i)
        res += iabs(a[i] - b[i]);
    return res;
}
int calc(const Pos& minp, const Pos& maxp, const Pos& p) {
    int res = 0;
    for(int i = 0; i < d; ++i)
        res += std::max(iabs(p[i] - minp[i]), iabs(p[i] - maxp[i]));
    return res;
}
int ans = 0;
void query(int u, const Pos& p) {
    if(calc(T[u].minp, T[u].maxp, p) <= ans)
        return;
    ans = std::max(ans, distance(T[u].p, p));
    if(T[u].ls)
        query(T[u].ls, p);
    if(T[u].rs)
        query(T[u].rs, p);
}
int main() {
    int n = read();
    d = read();
    for(int i = 0; i < d; ++i)
        nxtAxis[i] = (i + 1) % d;
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j < d; ++j)
            P[i][j] = read();
    int root = build(1, n);
    for(int i = 1; i <= n; ++i)
        query(root, P[i]);
    printf("%d\n", ans);
    return 0;
}
