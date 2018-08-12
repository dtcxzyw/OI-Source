//TODO:4331
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
const int size = 1000005;
struct Node {
    int l, r, dis, val;
} T[size];
int merge(int u, int v) {
    if (u && v) {
        if (T[u].val < T[v].val) std::swap(u, v);
        T[u].r = merge(T[u].r, v);
        if (T[T[u].l].dis < T[T[u].r].dis) std::swap(T[u].l, T[u].r);
        T[u].dis = T[T[u].r].dis + 1;
    }
    return u | v;
}
int A[size];
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i)
        A[i] = read();

    return 0;
}
