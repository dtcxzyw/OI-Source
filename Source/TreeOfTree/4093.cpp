#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int end = 100000, size = end + 5;
struct Node {
    int ls, rs, maxv;
} T[size * 300];
int icnt = 0, root[size] = {}, res;
void queryImpl(int l, int r, int rt, int nr) {
    if (rt && T[rt].maxv > res) {
        if (r <= nr)
            res = T[rt].maxv;
        else {
            int m = (l + r) >> 1;
            queryImpl(l, m, T[rt].ls, nr);
            if (m < nr) queryImpl(m + 1, r, T[rt].rs, nr);
        }
    }
}
int query(int x, int y) {
    res = 0;
    while (x) {
        queryImpl(1, end, root[x], y);
        x -= x & -x;
    }
    return res;
}
void insertImpl(int l, int r, int &rt, int p, int val) {
    if (!rt) rt = ++icnt;
    T[rt].maxv = std::max(T[rt].maxv, val);
    if (l != r) {
        int m = (l + r) >> 1;
        if (p <= m)
            insertImpl(l, m, T[rt].ls, p, val);
        else
            insertImpl(m + 1, r, T[rt].rs, p, val);
    }
}
void insert(int x, int y, int val) {
    while (x <= end) {
        insertImpl(1, end, root[x], y, val);
        x += x & -x;
    }
}
int A[size], maxv[size], minv[size];
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i <= n; ++i) A[i] = read();
    memcpy(maxv + 1, A + 1, sizeof(int) * n);
    memcpy(minv + 1, A + 1, sizeof(int) * n);
    while (m--) {
        int u = read();
        int v = read();
        maxv[u] = std::max(maxv[u], v);
        minv[u] = std::min(minv[u], v);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int dp = query(A[i], minv[i]) + 1;
        ans = std::max(ans, dp);
        insert(maxv[i], A[i], dp);
    }
    printf("%d\n", ans);
    return 0;
}
