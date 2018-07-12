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
int getOp() {
    int c;
    do
        c = getchar();
    while (c != 'A' && c != 'Q');
    return c;
}
const int size = 600005, maxb = 23;
struct Node {
    int cnt, c[2];
} T[size * (maxb + 2)];
int cnt = 0;
int insert(int src, int val, int d) {
    int id = ++cnt;
    T[id] = T[src];
    ++T[id].cnt;
    if (d >= 0) {
        int x = (val >> d) & 1;
        T[id].c[x] = insert(T[src].c[x], val, d - 1);
    }
    return id;
}
int query(int tb, int te, int val, int d) {
    if (d < 0) return 0;
    int x = ((val >> d) & 1) ^ 1, ans = 0;
    if (T[T[te].c[x]].cnt > T[T[tb].c[x]].cnt)
        ans = 1 << d;
    else
        x ^= 1;
    return ans | query(T[tb].c[x], T[te].c[x], val, d - 1);
}
int root[size] = {};
int main() {
    int n = read();
    int m = read();
    int cur = 0;
    root[1] = insert(root[0], cur, maxb);
    for (int i = 1; i <= n; ++i) {
        cur ^= read();
        root[i + 1] = insert(root[i], cur, maxb);
    }
    for (int i = 0; i < m; ++i) {
        if (getOp() == 'A') {
            cur ^= read();
            ++n;
            root[n + 1] = insert(root[n], cur, maxb);
        } else {
            int l = read();
            int r = read();
            int x = read() ^ cur;
            printf("%d\n", query(root[l - 1], root[r], x, maxb));
        }
    }
    return 0;
}
