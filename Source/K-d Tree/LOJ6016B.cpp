#include <algorithm>
#include <cstdio>
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
struct Point {
    int x, y, z;
    Point() {}
    Point(int x, int y, int z) : x(x), y(y), z(z) {}
} P[size];
typedef const Point& CRef;
bool cmpX(CRef a, CRef b) {
    return a.x < b.x;
}
bool cmpY(CRef a, CRef b) {
    return a.y < b.y;
}
bool cmpZ(CRef a, CRef b) {
    return a.z < b.z;
}
typedef bool (*cmpFunc)(CRef, CRef);
cmpFunc LUT[3] = { cmpZ, cmpX, cmpY };
void updateMin(Point& a, CRef b) {
    a.x = std::min(a.x, b.x);
    a.y = std::min(a.y, b.y);
    a.z = std::min(a.z, b.z);
}
void updateMax(Point& a, CRef b) {
    a.x = std::max(a.x, b.x);
    a.y = std::max(a.y, b.y);
    a.z = std::max(a.z, b.z);
}
struct Node {
    Point p, minP, maxP;
    int siz, c[2];
    void update(Node& rhs) {
        updateMin(minP, rhs.minP);
        updateMax(maxP, rhs.maxP);
    }
} T[size];
#define ls T[u].c[0]
#define rs T[u].c[1]
int tcnt = 0;
int build(int l, int r, int axis) {
    if(l > r)
        return 0;
    int m = (l + r) >> 1;
    std::nth_element(P + l, P + m, P + r + 1,
                     LUT[axis]);
    axis = (axis + 1) % 3;
    int u = ++tcnt;
    T[u].p = T[u].minP = T[u].maxP = P[m];
    if((ls = build(l, m - 1, axis)))
        T[u].update(T[ls]);
    if((rs = build(m + 1, r, axis)))
        T[u].update(T[rs]);
    T[u].siz = 1 + T[ls].siz + T[rs].siz;
    return u;
}
void insert(int& u, CRef p, int axis) {
    if(u) {
        ++T[u].siz;
        updateMin(T[u].minP, p);
        updateMax(T[u].maxP, p);
        bool cp = (LUT[axis])(T[u].p, p);
        insert(T[u].c[cp], p, (axis + 1) % 3);
    } else {
        u = ++tcnt;
        T[u].p = T[u].minP = T[u].maxP = p;
        T[u].siz = 1;
        ls = rs = 0;
    }
}
int ans, x1, x2, y1, y2, z1, z2;
void queryImpl(int u) {
    if(u == 0 || ans < 0)
        return;
    if(T[u].minP.x > x2 || T[u].maxP.x < x1 ||
       T[u].minP.y > y2 || T[u].maxP.y < y1 ||
       T[u].minP.z > z2 || T[u].maxP.z < z1)
        return;
    if(x1 <= T[u].minP.x && T[u].maxP.x <= x2 &&
       y1 <= T[u].minP.y && T[u].maxP.y <= y2 &&
       z1 <= T[u].minP.z && T[u].maxP.z <= z2) {
        ans -= T[u].siz;
        return;
    }
    if(x1 <= T[u].p.x && T[u].p.x <= x2 &&
       y1 <= T[u].p.y && T[u].p.y <= y2 &&
       z1 <= T[u].p.z && T[u].p.z <= z2)
        --ans;
    queryImpl(ls);
    queryImpl(rs);
}
int query(int rt, int k) {
    --k;
    int res = (1 << 30) - 1, sum = 0;
    for(int i = 29; i >= 0; --i) {
        int cur = res ^ (1 << i);
        z1 = cur + 1, z2 = res;
        int rem = k - sum;
        ans = rem;
        queryImpl(rt);
        if(ans >= 0) {
            res = cur;
            sum += rem - ans;
        }
    }
    return res;
}
int main() {
    int n = read();
    int q = read();
    int rt = 0, cnt = 0, lastAns = 0;
    for(int i = 1; i <= q; ++i) {
        if(read() == 1) {
            int x = read() ^ lastAns;
            int y = read() ^ lastAns;
            int z = read() ^ lastAns;
            P[++cnt] = Point(x, y, z);
            insert(rt, P[cnt], 0);
        } else {
            x1 = read() ^ lastAns;
            y1 = read() ^ lastAns;
            x2 = read() ^ lastAns;
            y2 = read() ^ lastAns;
            int k = read() ^ lastAns;
            int res = query(rt, k);
            if(res)
                printf("%d\n", res);
            else
                puts("NAIVE!ORZzyz.");
            lastAns = res;
        }
        if(i % 5000 == 0) {
            tcnt = 0;
            rt = build(1, cnt, 0);
        }
    }
    return 0;
}
