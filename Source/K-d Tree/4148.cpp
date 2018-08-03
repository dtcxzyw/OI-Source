#include <algorithm>
#include <cstdio>
int read(int ls = 0) {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res ^ ls;
}
const int size = 200005;
struct Pos {
    int x, y;
    bool operator<=(Pos rhs) const {
        return x <= rhs.x && y <= rhs.y;
    }
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
    int ls, rs, siz, sum, val;
} T[size];
int gc[size], top = 0;
int newNode(Pos p, int val) {
    static int cnt = 0;
    int id = top ? gc[top--] : ++cnt;
    T[id].min = T[id].max = T[id].p = p;
    T[id].ls = T[id].rs = 0;
    T[id].siz = 1;
    T[id].sum = T[id].val = val;
    return id;
}
void update(int p, int u) {
    if (u) {
        updateMin(T[p].min, T[u].min);
        updateMax(T[p].max, T[u].max);
        T[p].siz = T[T[p].ls].siz + T[T[p].rs].siz + 1;
        T[p].sum = T[T[p].ls].sum + T[T[p].rs].sum + T[p].val;
    }
}
struct Info {
    Pos pos;
    int val;
} A[size];
bool cmpAX(const Info &a, const Info &b) {
    return a.pos.x < b.pos.x;
}
bool cmpAY(const Info &a, const Info &b) {
    return a.pos.y < b.pos.y;
}
int cnt = 0;
void del(int u) {
    if (u) {
        gc[++top] = u;
        del(T[u].ls);
        del(T[u].rs);
        ++cnt;
        A[cnt].pos = T[u].p;
        A[cnt].val = T[u].val;
    }
}
int build(int l, int r, bool axis = false) {
    if (l > r) return 0;
    int m = (l + r) >> 1;
    std::nth_element(A + l, A + m, A + r + 1, axis ? cmpAX : cmpAY);
    int id = newNode(A[m].pos, A[m].val);
    T[id].ls = build(l, m - 1, !axis);
    update(id, T[id].ls);
    T[id].rs = build(m + 1, r, !axis);
    update(id, T[id].rs);
    return id;
}
int *path[size], pcnt = 0;
void insert(int &u, const Info &info, bool axis = false) {
    if (u) {
        ++T[u].siz, T[u].sum += info.val;
        updateMin(T[u].min, info.pos);
        updateMax(T[u].max, info.pos);
        path[++pcnt] = &u;
        if ((axis ? cmpX : cmpY)(info.pos, T[u].p))
            insert(T[u].ls, info, !axis);
        else
            insert(T[u].rs, info, !axis);
    } else
        u = newNode(info.pos, info.val);
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
int query(int u, Pos pmin, Pos pmax) {
    if (u) {
        if (pmin <= T[u].min && T[u].max <= pmax) return T[u].sum;
        if (std::max(pmin.x, T[u].min.x) > std::min(pmax.x, T[u].max.x) ||
            std::max(pmin.y, T[u].min.y) > std::min(pmax.y, T[u].max.y))
            return 0;
        int res = 0;
        if (pmin <= T[u].p && T[u].p <= pmax) res += T[u].val;
        res += query(T[u].ls, pmin, pmax);
        res += query(T[u].rs, pmin, pmax);
        return res;
    }
    return 0;
}
int main() {
    int n = read(), ls = 0, rt = 0;
    while (true) {
        int type = read();
        switch (type) {
            case 1: {
                Info info;
                info.pos.x = read(ls);
                info.pos.y = read(ls);
                info.val = read(ls);
                pcnt = 0;
                insert(rt, info);
                rebalance();
                break;
            }
            case 2: {
                Pos pmin, pmax;
                pmin.x = read(ls);
                pmin.y = read(ls);
                pmax.x = read(ls);
                pmax.y = read(ls);
                printf("%d\n", ls = query(rt, pmin, pmax));
                break;
            }
            case 3: {
                return 0;
            }
        }
    }
    return 0;
}
