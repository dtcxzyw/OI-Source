#include <algorithm>
#include <cstdio>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
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
struct Edge {
    int to, next;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u];
    last[u] = cnt;
}
int siz[size], depth[size], p[size][17], id[size], L[size], R[size], icnt = 0;
void DFS(int u) {
    L[u] = ++icnt;
    id[icnt] = u;
    siz[u] = 1;
    for (int i = 1; i < 17; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (v != p[u][0]) {
            depth[v] = depth[u] + 1;
            p[v][0] = u;
            DFS(v);
            siz[u] += siz[v];
        }
    }
    R[u] = icnt;
}
int dis(int u, int v) {
    int res = 0;
    if (depth[u] < depth[v]) std::swap(u, v);
    int delta = depth[u] - depth[v];
    for (int i = 0; i < 17; ++i)
        if (delta & (1 << i)) {
            res += (1 << i);
            u = p[u][i];
        }
    for (int i = 16; i >= 0; --i)
        if (p[u][i] != p[v][i]) {
            res += (2 << i);
            u = p[u][i], v = p[v][i];
        }
    return u == v ? res : res + 2;
}
struct Node {
    int siz, ls, rs;
} T[size * 20];
int ncnt = 0, root[size];
int insert(int l, int r, int src, int p) {
    int id = ++ncnt;
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
int queryKth(int l, int r, int a, int b, int k) {
    if (l == r)
        return l;
    else {
        int m = (l + r) >> 1;
        int lsiz = T[T[a].ls].siz - T[T[b].ls].siz;
        if (k <= lsiz) return queryKth(l, m, T[a].ls, T[b].ls, k);
        return queryKth(m + 1, r, T[a].rs, T[b].rs, k - lsiz);
    }
}
Int64 bid[size], dist[size][17];
int pt[size][17], rt[size], dt[size], link[size];
std::pair<int, int> findNode(Int64 u, int tcnt, int n) {
    int p = std::upper_bound(bid + 1, bid + tcnt + 1, u) - bid - 1;
    int tp = u - bid[p] + 1;
    int tid = queryKth(1, n, root[R[rt[p]]], root[L[rt[p]] - 1], tp);
    return std::make_pair(p, tid);
}
Int64 dis(Int64 u, Int64 v, int tcnt, int n) {
    Int64 res = 0;
    std::pair<int, int> nu = findNode(u, tcnt, n), nv = findNode(v, tcnt, n);
    int tu = nu.first, tv = nv.first;
    int cu, cv;
    if (tu != tv) {
        if (dt[tu] < dt[tv]) std::swap(tu, tv);
        int delta = dt[tu] - dt[tv];
        for (int i = 0; i < 17; ++i)
            if (delta & (1 << i))
                tu = pt[tu][i];
        bool flag = tu == tv;
        tu = nu.first, tv = nv.first;
        if (flag) {
            if (dt[tu] < dt[tv]) {
                std::swap(tu, tv);
                std::swap(nu, nv);
            }
            res += depth[nu.second] - depth[rt[tu]];
            int delta = dt[tu] - dt[tv] - 1;
            for (int i = 0; i < 17; ++i)
                if (delta & (1 << i)) {
                    res += dist[tu][i];
                    tu = pt[tu][i];
                }
            ++res;
            cu = link[tu], cv = nv.second;
        } else {
            res += depth[nu.second] - depth[rt[tu]] + depth[nv.second] - depth[rt[tv]];
            if (dt[tu] < dt[tv]) std::swap(tu, tv);
            int delta = dt[tu] - dt[tv];
            for (int i = 0; i < 17; ++i)
                if (delta & (1 << i)) {
                    res += dist[tu][i];
                    tu = pt[tu][i];
                }
            for (int i = 16; i >= 0; --i)
                if (pt[tu][i] != pt[tv][i]) {
                    res += dist[tu][i] + dist[tv][i];
                    tu = pt[tu][i], tv = pt[tv][i];
                }
            res += 2;
            cu = link[tu], cv = link[tv];
        }
    } else
        cu = nu.second, cv = nv.second;
    return res + dis(cu, cv);
}
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
    depth[1] = 0;
    DFS(1);

    for (int i = 1; i <= n; ++i)
        root[i] = insert(1, n, root[i - 1], id[i]);

    dt[1] = 0;
    bid[1] = 1;
    rt[1] = 1;
    Int64 cnt = n;
    int tcnt = 1;
    while (m--) {
        int id = ++tcnt;
        int src = read();
        std::pair<int, int> dst = findNode(read(), tcnt - 1, n);
        bid[id] = cnt + 1;
        cnt += siz[src];
        rt[id] = src;
        pt[id][0] = dst.first;
        for (int j = 1; j < 17; ++j)
            pt[id][j] = pt[pt[id][j - 1]][j - 1];
        dist[id][0] = depth[dst.second] - depth[rt[dst.first]] + 1;
        for (int j = 1; j < 17; ++j)
            dist[id][j] = dist[id][j - 1] + dist[pt[id][j - 1]][j - 1];
        dt[id] = dt[dst.first] + 1;
        link[id] = dst.second;
    }
    while (q--)
        printf("%lld\n", dis(read(), read(), tcnt, n));
    return 0;
}
