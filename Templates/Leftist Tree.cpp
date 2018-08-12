//P1456
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
const int size = 100005;
struct Node {
    int val, l, r, dis;
} T[size];
int merge(int u, int v) {
    if (u && v) {
        if (T[u].val < T[v].val) std::swap(u, v);
        T[u].r = merge(T[u].r, v);
        if (T[T[u].l].dis < T[T[u].r].dis) std::swap(T[u].l, T[u].r);
        T[u].dis = T[T[u].r].dis + 1;
        return u;
    }
    return u | v;
}
int update(int u) {
    int res = merge(T[u].l, T[u].r);
    T[u].l = T[u].r = T[u].dis = 0;
    return merge(u, res);
}
int fa[size], root[size];
int find(int u) {
    return fa[u] == u ? u : fa[u] = find(fa[u]);
}
int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            T[i].val = read();
            T[i].l = T[i].r = T[i].dis = 0;
            fa[i] = i;
            root[i] = i;
        }
        int m = read();
        while (m--) {
            int u = find(read());
            int v = find(read());
            if (u != v) {
                fa[v] = u;
                T[root[u]].val >>= 1;
                T[root[v]].val >>= 1;
                root[u] = merge(update(root[u]), update(root[v]));
                printf("%d\n", T[root[u]].val);
            } else
                puts("-1");
        }
    }
    return 0;
}
