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
const int size = 500005;
namespace SegA {
    int sum[size << 2], tag[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
    void update(int id) {
        sum[id] = sum[id << 1] + sum[id << 1 | 1];
    }
    void color(int l, int r, int id, int val) {
        sum[id] = (r - l + 1) * val;
        tag[id] = val;
    }
    void pushDown(int l, int r, int id) {
        if(tag[id]) {
            int m = (l + r) >> 1;
            color(ls, tag[id]);
            color(rs, tag[id]);
            tag[id] = 0;
        }
    }
    void modify(int l, int r, int id, int nl, int nr,
                int val) {
        if(nl <= l && r <= nr)
            color(l, r, id, val);
        else {
            pushDown(l, r, id);
            int m = (l + r) >> 1;
            if(nl <= m)
                modify(ls, nl, nr, val);
            if(m < nr)
                modify(rs, nl, nr, val);
            update(id);
        }
    }
    int query(int l, int r, int id, int nl, int nr) {
        if(nl <= l && r <= nr)
            return sum[id];
        pushDown(l, r, id);
        int m = (l + r) >> 1, res = 0;
        if(nl <= m)
            res += query(ls, nl, nr);
        if(m < nr)
            res += query(rs, nl, nr);
        return res;
    }
}
namespace SegB {
    struct Node {
        int l, r, val;
    } T[size * 100];
    int tcnt = 0;
    int modify(int l, int r, int src, int nl, int nr,
               int val) {
        int id = ++tcnt;
        if(nl <= l && r <= nr)
            T[id].val = val;
        else {
            T[id] = T[src];
            int m = (l + r) >> 1;
            if(nl <= m)
                T[id].l =
                    modify(l, m, T[id].l, nl, nr, val);
            if(m < nr)
                T[id].r = modify(m + 1, r, T[id].r, nl,
                                 nr, val);
        }
        return id;
    }
    int query(int l, int r, int id, int p) {
        if(id == 0)
            return -1;
        int m = (l + r) >> 1, res;
        if(p <= m)
            res = query(l, m, T[id].l, p);
        else
            res = query(m + 1, r, T[id].r, p);
        return res != -1 ? res : T[id].val;
    }
}
int t[size], rt[size];
int main() {
    int n = read();
    int m = read();
    int ty = read();
    int lastAns = 0;
    SegB::T[0].val = -1;
    for(int i = 1; i <= m; ++i) {
        rt[i] = rt[i - 1];
        int op = read();
        switch(op) {
            case 1: {
                int l = (read() + lastAns) % n + 1;
                int r = (read() + lastAns) % n + 1;
                if(l > r)
                    std::swap(l, r);
                int res = SegA::query(1, n, 1, l, r);
                printf("%d\n", res);
                if(ty)
                    lastAns = res;
            } break;
            case 2: {
                int l = (read() + lastAns) % n + 1;
                int tp = SegB::query(1, n, rt[i], l);
                if(tp > 0) {
                    int nt = SegB::query(
                        1, n, rt[tp - 1], l);
                    if(nt == -1)
                        nt = 0;
                    rt[i] = SegB::modify(1, n, rt[i],
                                         l, l, nt);
                    SegA::modify(1, n, 1, l, l, t[nt]);
                }
            } break;
            case 3: {
                int l = (read() + lastAns) % n + 1;
                int r = (read() + lastAns) % n + 1;
                if(l > r)
                    std::swap(l, r);
                t[i] = read();
                rt[i] =
                    SegB::modify(1, n, rt[i], l, r, i);
                SegA::modify(1, n, 1, l, r, t[i]);
            } break;
        }
    }
    return 0;
}
