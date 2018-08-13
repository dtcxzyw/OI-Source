#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
struct Pos {
    int x, y;
};
const int size = 200005;
struct RECT {
    Pos b, e;
    bool intersect(const RECT &rhs) const {
        return std::max(b.x, rhs.b.x) < std::min(e.x, rhs.e.x) &&
               std::max(b.y, rhs.b.y) < std::min(e.y, rhs.e.y);
    }
    bool cover(const RECT &rhs) const {
        return b.x <= rhs.b.x && rhs.e.x <= e.x &&
               b.y <= rhs.b.y && rhs.e.y <= e.y;
    }
    void merge(const RECT &rhs) {
        b.x = std::min(b.x, rhs.b.x);
        b.y = std::min(b.y, rhs.b.y);
        e.x = std::max(e.x, rhs.e.x);
        e.y = std::max(e.y, rhs.e.y);
    }
};
struct RECTB : RECT {
    Pos w;
    int area, id;
} R[size];
bool cmpX(const RECTB &a, const RECTB &b) {
    return a.w.x < b.w.x;
}
bool cmpY(const RECTB &a, const RECTB &b) {
    return a.w.y < b.w.y;
}
bool cmpArea(const RECTB &a, const RECTB &b) {
    return a.area > b.area;
}
struct Node {
    RECT self, bounds;
    int l, r, siz, id;
    bool flag;
} T[size];
#define ls T[id].l
#define rs T[id].r
int icnt = 0;
int buildTree(int l, int r, bool axis = false) {
    int m = (l + r) >> 1;
    std::nth_element(R + l, R + m, R + r + 1, axis ? cmpX : cmpY);
    int id = ++icnt;
    T[id].bounds = T[id].self = R[m];
    T[id].id = R[m].id;
    T[id].flag = true;
    T[id].siz = 1;
    if (l < m) {
        ls = buildTree(l, m - 1, !axis);
        T[id].bounds.merge(T[ls].bounds);
        T[id].siz += T[ls].siz;
    }
    if (m < r) {
        rs = buildTree(m + 1, r, !axis);
        T[id].bounds.merge(T[rs].bounds);
        T[id].siz += T[rs].siz;
    }
    return id;
}
bool flag[size] = {};
void color(int id, int uid) {
    if (T[id].siz) {
        if (T[id].id != uid) {
            T[id].flag = false;
            flag[T[id].id] = true;
        }
        color(ls, uid);
        color(rs, uid);
        T[id].siz = T[ls].siz + T[rs].siz + T[id].flag;
    }
}
void tryCover(int id, const RECTB &rect) {
    if (T[id].siz == 0 || !rect.intersect(T[id].bounds)) return;
    if (rect.cover(T[id].bounds)) {
        color(id, rect.id);
    } else {
        if (T[id].flag && rect.id != T[id].id &&
            rect.cover(T[id].self)) {
            T[id].flag = false;
            flag[T[id].id] = true;
        }
        tryCover(ls, rect);
        tryCover(rs, rect);
        T[id].siz = T[ls].siz + T[rs].siz + T[id].flag;
    }
}
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i) {
        R[i].b.x = read();
        R[i].b.y = read();
        R[i].e.x = read();
        R[i].e.y = read();
        R[i].w.x = R[i].b.x + R[i].e.x;
        R[i].w.y = R[i].b.y + R[i].e.y;
        R[i].area = (R[i].e.x - R[i].b.x) * (R[i].e.y - R[i].b.y);
        R[i].id = i;
    }
    int rt = buildTree(1, n);
    std::sort(R + 1, R + n + 1, cmpArea);
    for (int i = 1; i <= n; ++i)
        if (!flag[R[i].id])
            tryCover(rt, R[i]);
    printf("%d\n", n - T[rt].siz);
    return 0;
}
