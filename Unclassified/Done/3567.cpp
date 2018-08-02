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
const int size = 500005;
struct Node {
    int siz, ls, rs;
} T[size * 20];
int icnt = 0;
int insert(int l, int r, int src, int p) {
    int id = ++icnt;
    T[id] = T[src];
    ++T[id].siz;
    if (l != r) {
        int m = (l + r) >> 1;
        if (p <= m)
            T[id].ls = insert(l, m, T[id].ls, p);
        else
            T[id].rs = insert(m + 1, r, T[id].rs, p);
    }
    return id;
}
int query(int l, int r, int a, int b, int k) {
    int siz = T[a].siz - T[b].siz;
    if (siz <= k) return 0;
    if (l == r) return l;
    int lsiz = T[T[a].ls].siz - T[T[b].ls].siz;
    int m = (l + r) >> 1;
    if (lsiz > k) return query(l, m, T[a].ls, T[b].ls, k);
    return query(m + 1, r, T[a].rs, T[b].rs, k);
}
int root[size];
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i <= n; ++i)
        root[i] = insert(1, n, root[i - 1], read());
    while (m--) {
        int l = read();
        int r = read();
        int k = (r - l + 1) >> 1;
        printf("%d\n", query(1, n, root[r], root[l - 1], k));
    }
    return 0;
}
