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
int iabs(int x) {
    return x >= 0 ? x : -x;
}
const int size = 300005;
struct Pos {
    int x, y;
    Pos() {}
    Pos(int x, int y) : x(x), y(y) {}
} P[size];
bool cmpX(Pos a, Pos b) {
    return a.x < b.x;
}
bool cmpY(Pos a, Pos b) {
    return a.y < b.y;
}
void updateMin(Pos &a, Pos b) {
    a.x = std::min(a.x, b.x);
    a.y = std::min(a.y, b.y);
}
void updateMax(Pos &a, Pos b) {
    a.x = std::max(a.x, b.x);
    a.y = std::max(a.y, b.y);
}
struct Node {
    Pos p, min, max;
    int ls, rs, siz;
} T[2 * size];
int gc[2 * size], top = 0;
int newNode(Pos p) {
    static int cnt = 0;
    int id = top ? gc[top--] : ++cnt;
    T[id].min = T[id].max = T[id].p = p;
    T[id].ls = T[id].rs = 0;
    T[id].siz = 1;
    return id;
}
void update(int p, int u) {
    if (u) {
        updateMin(T[p].min, T[u].min);
        updateMax(T[p].max, T[u].max);
        T[p].siz = T[T[p].ls].siz + T[T[p].rs].siz + 1;
    }
}
int cnt;
void del(int u) {
    if (u) {
        gc[++top] = u;
        del(T[u].ls);
        del(T[u].rs);
        P[++cnt] = T[u].p;
    }
}
int build(int l, int r, bool axis = false) {
    if (l > r) return 0;
    int m = (l + r) >> 1;
    std::nth_element(P + l, P + m, P + r + 1, axis ? cmpX : cmpY);
    int id = newNode(P[m]);
    T[id].ls = build(l, m - 1, !axis);
    update(id, T[id].ls);
    T[id].rs = build(m + 1, r, !axis);
    update(id, T[id].rs);
    return id;
}
int *path[2 * size], pcnt = 0;
void insert(int &u, Pos pos, bool axis = false) {
    if (u) {
        ++T[u].siz;
        updateMin(T[u].min, pos);
        updateMax(T[u].max, pos);
        path[++pcnt] = &u;
        if ((axis ? cmpX : cmpY)(pos, T[u].p))
            insert(T[u].ls, pos, !axis);
        else
            insert(T[u].rs, pos, !axis);
    } else
        u = newNode(pos);
}
void rebalance() {
    for (int i = 1; i <= pcnt; ++i) {
        int &u = *path[i];
        int limit = (T[u].siz * 3) >> 2;
        if (std::max(T[T[u].ls].siz, T[T[u].rs].siz) > limit) {
            cnt = 0;
            del(u);
            u = build(1, cnt);
            break;
        }
    }
}
int calc(Pos a, Pos b) {
    return iabs(a.x - b.x) + iabs(a.y - b.y);
}
int calc(Pos a, const Node &b) {
    return std::max(b.min.x - a.x, 0) + std::max(a.x - b.max.x, 0) + std::max(b.min.y - a.y, 0) + std::max(a.y - b.max.y, 0);
}
int res;
void query(int u, Pos p) {
    if (u) {
        if (calc(p, T[u]) >= res) return;
        res = std::min(res, calc(p, T[u].p));
        query(T[u].ls, p);
        query(T[u].rs, p);
    }
}
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i <= n; ++i) {
        P[i].x = read();
        P[i].y = read();
    }
    int rt = build(1, n);
    for (int i = 0; i < m; ++i) {
        int t = read();
        int x = read();
        int y = read();
        if (t == 1) {
            Pos pos(x, y);
            pcnt = 0;
            insert(rt, pos);
            rebalance();
        } else {
            res = 1 << 30;
            query(rt, Pos(x, y));
            printf("%d\n", res);
        }
    }
    return 0;
}
