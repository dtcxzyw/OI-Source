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
const int size = 505, lsiz = size * size;
struct Node {
    int l, r, siz;
} T[lsiz * 100];
int icnt = 0;
int insertImpl(int l, int r, int src, int p) {
    int id = ++icnt;
    T[id] = T[src];
    ++T[id].siz;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = insertImpl(l, m, T[id].l, p);
        else
            T[id].r = insertImpl(m + 1, r, T[id].r, p);
    }
    return id;
}
int res, nl, nr;
void queryImpl(int l, int r, int a, int b) {
    int delta = T[b].siz - T[a].siz;
    if(delta == 0)
        return;
    if(nl <= l && r <= nr)
        res += delta;
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            queryImpl(l, m, T[a].l, T[b].l);
        if(m < nr)
            queryImpl(m + 1, r, T[a].r, T[b].r);
    }
}
int root[size][size], n, siz;
void insert(int x, int y, int val) {
    while(x <= n) {
        root[x][y] =
            insertImpl(1, siz, root[x][y], val);
        x += x & -x;
    }
}
int query(int x, int a, int b) {
    res = 0;
    while(x) {
        queryImpl(1, siz, root[x][a], root[x][b]);
        x -= x & -x;
    }
    return res;
}
int bx, ex, by, ey;
int queryRange(int lv, int rv) {
    nl = lv, nr = rv;
    return query(ex, by - 1, ey) -
        query(bx - 1, by - 1, ey);
}
int solve(int l, int r, int k) {
    if(l == r)
        return l;
    else {
        int m = (l + r) >> 1;
        int lsiz = queryRange(l, m);
        if(lsiz >= k)
            return solve(l, m, k);
        return solve(m + 1, r, k - lsiz);
    }
}
int A[size][size], B[lsiz];
int main() {
    n = read();
    int q = read();
    siz = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            A[i][j] = B[++siz] = read();
    std::sort(B + 1, B + siz + 1);
    siz = std::unique(B + 1, B + siz + 1) - (B + 1);
    for(int i = 1; i <= n; ++i)
        for(int j = n; j >= 1; --j) {
            root[j][i] = root[j][i - 1];
            int pos =
                std::lower_bound(B + 1, B + siz + 1,
                                 A[j][i]) -
                B;
            insert(j, i, pos);
        }
    while(q--) {
        bx = read();
        by = read();
        ex = read();
        ey = read();
        printf("%d\n", B[solve(1, siz, read())]);
    }
    return 0;
}
