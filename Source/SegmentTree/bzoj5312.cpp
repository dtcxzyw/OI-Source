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
const int size = 200005;
int av[size << 2], ov[size << 2], mv[size << 2],
    tag[size << 2];
void update(int id) {
    av[id] = av[id << 1] & av[id << 1 | 1];
    ov[id] = ov[id << 1] | ov[id << 1 | 1];
    mv[id] = std::max(mv[id << 1], mv[id << 1 | 1]);
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void build(int l, int r, int id) {
    if(l == r)
        av[id] = ov[id] = mv[id] = read();
    else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        update(id);
    }
}
void color(int id, int val) {
    av[id] += val, ov[id] += val, mv[id] += val,
        tag[id] += val;
}
void pushDown(int id) {
    if(tag[id]) {
        color(id << 1, tag[id]);
        color(id << 1 | 1, tag[id]);
        tag[id] = 0;
    }
}
void And(int l, int r, int id, int nl, int nr,
         int val) {
    int deltaA = (av[id] & val) - av[id],
        deltaB = (ov[id] & val) - ov[id];
    if(deltaB == 0)
        return;
    if(nl <= l && r <= nr && deltaA == deltaB)
        color(id, deltaA);
    else {
        pushDown(id);
        int m = (l + r) >> 1;
        if(nl <= m)
            And(ls, nl, nr, val);
        if(m < nr)
            And(rs, nl, nr, val);
        update(id);
    }
}
void Or(int l, int r, int id, int nl, int nr,
        int val) {
    int deltaA = (av[id] | val) - av[id],
        deltaB = (ov[id] | val) - ov[id];
    if(deltaA == 0)
        return;
    if(nl <= l && r <= nr && deltaA == deltaB)
        color(id, deltaA);
    else {
        pushDown(id);
        int m = (l + r) >> 1;
        if(nl <= m)
            Or(ls, nl, nr, val);
        if(m < nr)
            Or(rs, nl, nr, val);
        update(id);
    }
}
int query(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return mv[id];
    pushDown(id);
    int m = (l + r) >> 1;
    if(nl <= m && m < nr)
        return std::max(query(ls, nl, nr),
                        query(rs, nl, nr));
    if(nl <= m)
        return query(ls, nl, nr);
    return query(rs, nl, nr);
}
int main() {
    int n = read();
    int m = read();
    build(1, n, 1);
    for(int i = 1; i <= m; ++i) {
        int op = read();
        int l = read();
        int r = read();
        switch(op) {
            case 1:
                And(1, n, 1, l, r, read());
                break;
            case 2:
                Or(1, n, 1, l, r, read());
                break;
            case 3:
                printf("%d\n", query(1, n, 1, l, r));
                break;
        }
    }
    return 0;
}
