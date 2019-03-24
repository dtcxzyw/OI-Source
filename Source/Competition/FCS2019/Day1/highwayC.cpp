#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int size = 100005;
struct Edge {
    int u, v, w;
} E[size];
bool cmp(int a, int b) {
    return E[a].w < E[b].w;
}
typedef std::vector<int> ES;
int n, fa[105];
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
ES merge(const ES& A, const ES& B) {
    ES X(A.size() + B.size());
    std::merge(A.begin(), A.end(), B.begin(), B.end(),
               X.begin(), cmp);
    ES Y;
    memset(fa + 1, 0, sizeof(int) * n);
    for(int i = 0, ecnt = n - 1; i < X.size(); ++i) {
        Edge& e = E[X[i]];
        int u = find(e.u), v = find(e.v);
        if(u != v) {
            Y.push_back(X[i]);
            fa[u] = v;
            if(--ecnt == 0)
                break;
        }
    }
    return Y;
}
ES G[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void build(int l, int r, int id) {
    if(l == r)
        G[id].push_back(l);
    else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        G[id] = merge(G[id << 1], G[id << 1 | 1]);
    }
}
ES query(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return G[id];
    else {
        int m = (l + r) >> 1;
        if(nl <= m && m < nr)
            return merge(query(ls, nl, nr),
                         query(rs, nl, nr));
        if(nl <= m)
            return query(ls, nl, nr);
        return query(rs, nl, nr);
    }
}
int main() {
    int m, q;
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= m; ++i)
        scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
    build(1, m, 1);
    for(int i = 1; i <= q; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        ES res = query(1, m, 1, l, r);
        int ans = 0;
        for(int j = 0; j < res.size(); ++j)
            ans += E[res[j]].w;
        printf("%d\n", ans);
    }
    return 0;
}
