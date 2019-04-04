#include <algorithm>
#include <cmath>
#include <cstdio>
const int size = 12005, maxd = 30;
struct Node {
    int c[2], siz;
} T[size * 40];
int tcnt = 0;
int insert(int src, int x, int d) {
    int id = ++tcnt;
    T[id] = T[src];
    ++T[id].siz;
    if(d != -1) {
        int& c = T[id].c[(x >> d) & 1];
        c = insert(c, x, d - 1);
    }
    return id;
}
int query(int b, int e, int x, int d) {
    if(d == -1)
        return 0;
    int bx = (x >> d) & 1, nb = bx ^ 1;
    int lsiz = T[T[e].c[nb]].siz - T[T[b].c[nb]].siz;
    if(lsiz)
        return query(T[b].c[nb], T[e].c[nb], x,
                     d - 1) |
            (1 << d);
    return query(T[b].c[bx], T[e].c[bx], x, d - 1);
}
int A[size], root[size];
int query(int b, int e, int x) {
    if(b >= e)
        return 0;
    return query(b >= 0 ? root[b] : 0, root[e], x,
                 maxd);
}
int F[111][size];
int main() {
    root[0] = insert(0, 0, maxd);
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &A[i]);
        A[i] ^= A[i - 1];
        root[i] = insert(root[i - 1], A[i], maxd);
    }
    int bsiz = sqrt(n) + 1;
    int bcnt = n / bsiz;
    for(int i = 0; i <= bcnt; ++i) {
        int b = i * bcnt;
        for(int j = b + 1; j <= n; ++j)
            F[i][j] =
                std::max(F[i][j - 1],
                         query(b - 1, j - 1, A[j]));
    }
    long long lastAns = 0;
    for(int i = 1; i <= m; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        l = (l + lastAns) % n + 1;
        r = (r + lastAns) % n + 1;
        if(l > r)
            std::swap(l, r);
        --l;
        int lb = l / bcnt, ans = F[lb + 1][r],
            end = std::min((lb + 1) * bcnt - 1, r);
        for(int j = l; j <= end; ++j)
            ans = std::max(ans, query(j, r, A[j]));
        printf("%d\n", ans);
        lastAns = ans;
    }
    return 0;
}
