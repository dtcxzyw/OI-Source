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
const int size = 100005, maxv = 2 * size;
struct G {
    struct Edge {
        int to, nxt;
    } E[size * 3];
    int last[maxv], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].nxt = last[u], E[cnt].to = v;
        last[u] = cnt;
    }
} A, B;
int p[size], dfn[size], icnt = 0, nsiz;
bool ring[size];
void DFS(int u) {
    dfn[u] = ++icnt;
    for(int i = A.last[u]; i; i = A.E[i].nxt) {
        int v = A.E[i].to;
        if(v == p[u])
            continue;
        if(dfn[v]) {
            if(dfn[v] < dfn[u]) {
                int id = ++nsiz;
                for(int j = u; j != v; j = p[j])
                    B.addEdge(id, j), ring[j] = true;
                B.addEdge(v, id), ring[v] = true;
            }
        } else {
            ring[u] = false;
            p[v] = u;
            DFS(v);
            if(!ring[u])
                B.addEdge(u, v);
        }
    }
}
struct Node {
    int l, r, siz[2];
} T[size * 40];
int tcnt = 0;
int insert(int l, int r, int p) {
    int id = ++tcnt;
    T[id].siz[1] = 1;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = insert(l, m, p);
        else
            T[id].r = insert(m + 1, r, p);
    }
    return id;
}
int mergeImpl(int l, int r, int u, int v) {
    if(u && v) {
        int id = ++tcnt;
        if(l == r) {
            int uc = T[u].siz[1] != 0,
                vc = T[v].siz[1] != 0;
            T[id].siz[uc ^ vc] = 1;
        } else {
            int m = (l + r) >> 1;
            T[id].l = mergeImpl(l, m, T[u].l, T[v].l);
            T[id].r =
                mergeImpl(m + 1, r, T[u].r, T[v].r);
            T[id].siz[0] =
                T[T[id].l].siz[0] + T[T[id].r].siz[0];
            T[id].siz[1] =
                T[T[id].l].siz[1] + T[T[id].r].siz[1];
        }
        return id;
    }
    return u | v;
}
int query(int l, int r, int id, int nr, int ty) {
    if(id == 0)
        return 0;
    if(r <= nr)
        return T[id].siz[ty];
    int m = (l + r) >> 1,
        res = query(l, m, T[id].l, nr, ty);
    if(m < nr)
        res += query(m + 1, r, T[id].r, nr, ty);
    return res;
}
int X[size], root[maxv], n, siz;
int merge(int u, int v) {
    return mergeImpl(1, siz, u, v);
}
int Y[size];
void buildTree(int u) {
    if(u <= n)
        root[u] = insert(1, siz, X[u]);
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        buildTree(v);
        root[u] = merge(root[u], root[v]);
    }
}
int main() {
    n = read();
    int m = read();
    for(int i = 1; i <= n; ++i)
        X[i] = read();
    memcpy(Y + 1, X + 1, sizeof(int) * n);
    std::sort(Y + 1, Y + n + 1);
    siz = std::unique(Y + 1, Y + n + 1) - (Y + 1);
    for(int i = 1; i <= n; ++i)
        X[i] = std::lower_bound(Y + 1, Y + siz + 1,
                                X[i]) -
            Y;
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        A.addEdge(u, v);
        A.addEdge(v, u);
    }
    nsiz = n;
    DFS(1);
    buildTree(1);
    int q = read();
    for(int i = 1; i <= q; ++i) {
        int ty = read();
        int x = read();
        int y = std::upper_bound(Y + 1, Y + siz + 1,
                                 read()) -
            Y - 1;
        if(y)
            printf("%d\n",
                   query(1, siz, root[x], y, ty));
        else
            puts("0");
    }
    return 0;
}
