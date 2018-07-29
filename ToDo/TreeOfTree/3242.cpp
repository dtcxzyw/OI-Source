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
int getOp() {
    int c;
    do
        c = getchar();
    while (c != 'C' && c != 'Q');
    return c;
}
const int size = 40005;
struct Edge {
    int to, next;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u];
    last[u] = cnt;
}
int p[size][16], d[size], L[size], R[size], tcnt = 0;
void DFS(int u) {
    L[u] = ++tcnt;
    for (int i = 1; i < 16; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (v != p[u][0]) {
            p[v][0] = u;
            d[v] = d[u] + 1;
            DFS(v);
        }
    }
    R[u] = tcnt;
}
struct Node {
    int ls, rs, siz;
} T[size * 600];
int icnt = 0, root[size];
int queryImpl(int l, int r, int rt, int nl, int nr) {
    if (rt) {
        if (nl <= l && r <= nr)
            return T[rt].siz;
        else {
            int m = (l + r) >> 1, res = 0;
            if (nl <= m) res += queryImpl(l, m, T[rt].ls, nl, nr);
            if (m < nr) res += queryImpl(m + 1, r, T[rt].rs, nl, nr);
            return res;
        }
    }
    return 0;
}
int vsiz;
int query(int x, int kl, int kr) {
    int res = 0;
    while (x) {
        res += queryImpl(1, vsiz, root[x], kl, kr);
        x -= x & -x;
    }
    return res;
}
void modifyImpl(int l, int r, int &rt, int val, int op) {
    if (!rt) rt = ++icnt;
    T[rt].siz += op;
    if (l != r) {
        int m = (l + r) >> 1;
        if (val <= m)
            modifyImpl(l, m, T[rt].ls, val, op);
        else
            modifyImpl(m + 1, r, T[rt].rs, val, op);
    }
}
void modify(int x, int siz, int val, int op) {
    while (x <= siz) {
        modifyImpl(1, vsiz, root[x], val, op);
        x += x & -x;
    }
}
struct Line {
    int x, by, ey, w, op;
    Line() {}
    Line(int x, int by, int ey, int w, int op) : x(x), by(by), ey(ey), w(w), op(op) {}
    bool operator<(const Line &rhs) const {
        return x < rhs.x;
    }
} Lines[size * 4];
int lcnt = 0;
void insertRECT(int n, int bx, int ex, int by, int ey, int w) {
    if (bx <= ex && by <= ey) {
        if (bx > by) std::swap(bx, by), std::swap(ex, ey);
        Lines[++lcnt] = Line(bx, by, ey, w, 1);
        Lines[++lcnt] = Line(ex + 1, by, ey, w, -1);
    }
}
struct Info {
    int u, v, w;
} A[size];
struct Query {
    int x, y, k, id;
    bool operator<(const Query &rhs) const {
        return x < rhs.x;
    }
} Q[size];
int B[size], ans[size];
int main() {
    int n = read();
    int m = read();
    int q = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    DFS(1);
    for (int i = 1; i <= m; ++i) {
        A[i].u = read();
        A[i].v = read();
        B[i] = A[i].w = read();
    }
    std::sort(B + 1, B + m + 1);
    vsiz = std::unique(B + 1, B + m + 1) - (B + 1);
    for (int i = 1; i <= m; ++i) {
        int u = A[i].u;
        int v = A[i].v;
        int w = std::lower_bound(B + 1, B + vsiz + 1, A[i].w) - B;
        if (d[u] < d[v]) std::swap(u, v);
        int tu = u, tv = v;
        int delta = d[tu] - d[tv];
        for (int i = 0; i < 16; ++i)
            if (delta & (1 << i))
                tu = p[tu][i];
        if (tu == tv) {
            --delta;
            tu = u;
            for (int i = 0; i < 16; ++i)
                if (delta & (1 << i))
                    tu = p[tu][i];
            insertRECT(n, L[u], R[u], 1, L[tu] - 1, w);
            insertRECT(n, L[u], R[u], R[tu] + 1, n, w);
        } else
            insertRECT(n, L[u], R[u], L[v], R[v], w);
    }
    std::sort(Lines + 1, Lines + lcnt + 1);
    for (int i = 0; i < q; ++i) {
        Q[i].x = L[read()];
        Q[i].y = L[read()];
        Q[i].k = read();
        if (Q[i].x > Q[i].y) std::swap(Q[i].x, Q[i].y);
        Q[i].id = i;
    }
    std::sort(Q, Q + q);
    int cur = 1;
    for (int i = 0; i < q; ++i) {
        while (cur <= lcnt && Lines[cur].x <= Q[i].x) {
            modify(Lines[cur].by, n, Lines[cur].w, Lines[cur].op);
            modify(Lines[cur].ey + 1, n, Lines[cur].w, -Lines[cur].op);
            ++cur;
        }
        int k = Q[i].k, l = 1, r = vsiz;
        while (l != r) {
            int m = (l + r) >> 1;
            int lsiz = query(Q[i].y, l, m);
            if (k <= lsiz)
                r = m;
            else
                l = m + 1, k -= lsiz;
        }
        ans[Q[i].id] = B[l];
    }
    for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
    return 0;
}
