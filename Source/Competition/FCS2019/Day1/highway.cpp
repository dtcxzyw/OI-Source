#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 100005;
struct Node {
    int l, r, siz;
} T[size * 40];
int tcnt = 0;
int insert(int l, int r, int src, int p) {
    int id = ++tcnt;
    T[id] = T[src];
    ++T[id].siz;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = insert(l, m, T[id].l, p);
        else
            T[id].r = insert(m + 1, r, T[id].r, p);
    }
    return id;
}
int query(int l, int r, int b, int e, int k) {
    if(l == r)
        return l;
    int lsiz = T[T[e].l].siz - T[T[b].l].siz,
        m = (l + r) >> 1;
    if(lsiz >= k)
        return query(l, m, T[b].l, T[e].l, k);
    return query(m + 1, r, T[b].r, T[e].r, k - lsiz);
}
struct Edge {
    int u, v, w, id;
} E[size];
int cnt[size * 10], root[size], id2e[size], fa[105];
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
int main() {
    int n = read();
    int m = read();
    int q = read();
    int maxw = 0;
    for(int i = 1; i <= m; ++i) {
        E[i].u = read();
        E[i].v = read();
        E[i].w = read();
        ++cnt[E[i].w];
        maxw = std::max(maxw, E[i].w);
    }
    for(int i = 1; i <= maxw; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = m; i >= 1; --i) {
        E[i].id = cnt[E[i].w]--;
        id2e[E[i].id] = i;
    }
    for(int i = 1; i <= m; ++i)
        root[i] = insert(1, m, root[i - 1], E[i].id);
    for(int i = 1; i <= q; ++i) {
        memset(fa + 1, 0, sizeof(int) * n);
        int l = read();
        int r = read();
        int w = 0, siz = r - l + 1;
        for(int j = 1, ecnt = n - 1; j <= siz; ++j) {
            int eid = id2e[query(1, m, root[l - 1],
                                 root[r], j)];
            int u = find(E[eid].u), v = find(E[eid].v);
            if(u != v) {
                w += E[eid].w;
                fa[u] = v;
                if(--ecnt == 0)
                    break;
            }
        }
        printf("%d\n", w);
    }
    return 0;
}
