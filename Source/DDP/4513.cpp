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
void printImpl(int x) {
    if(x >= 10)
        printImpl(x / 10);
    putchar('0' + x % 10);
}
void print(int x) {
    if(x < 0)
        putchar('-'), x = -x;
    printImpl(x);
    putchar('\n');
}
int maxi(int a, int b) {
    return a > b ? a : b;
}
void swap(int& a, int& b) {
    int c = a ^ b;
    a ^= c, b ^= c;
}
const int size = 500005;
struct Info {
    int lmax, rmax, maxs, sum;
} T[size << 2];
Info merge(const Info& lhs, const Info& rhs) {
    Info res;
    res.lmax = maxi(lhs.lmax, lhs.sum + rhs.lmax);
    res.rmax = maxi(rhs.rmax, rhs.sum + lhs.rmax);
    res.maxs = maxi(lhs.rmax + rhs.lmax,
                    maxi(lhs.maxs, rhs.maxs));
    res.sum = lhs.sum + rhs.sum;
    return res;
}
void reset(int id, int v) {
    T[id].sum = T[id].maxs = T[id].rmax = T[id].lmax =
        v;
}
void update(int id) {
    T[id] = merge(T[id << 1], T[id << 1 | 1]);
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void build(int l, int r, int id) {
    if(l == r)
        reset(id, read());
    else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        update(id);
    }
}
int u, v;
void modify(int l, int r, int id) {
    if(l == r)
        reset(id, v);
    else {
        int m = (l + r) >> 1;
        if(u <= m)
            modify(ls);
        else
            modify(rs);
        update(id);
    }
}
Info query(int l, int r, int id) {
    if(u <= l && r <= v)
        return T[id];
    else {
        int m = (l + r) >> 1;
        if(u <= m && m < v)
            return merge(query(ls), query(rs));
        if(u <= m)
            return query(ls);
        return query(rs);
    }
}
int main() {
    int n = read();
    int m = read();
    build(1, n, 1);
    while(m--) {
        int k = read();
        u = read();
        v = read();
        if(k == 1) {
            if(u > v)
                swap(u, v);
            print(query(1, n, 1).maxs);
        } else
            modify(1, n, 1);
    }
    return 0;
}
