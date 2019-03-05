// ERROR
#include <algorithm>
#include <cstdio>
#include <vector>
const int size = 405, inf = 1 << 30;
struct G {
    struct Edge {
        int to, nxt;
    } E[size];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} A, B;
int p[size][6], d[size];
int lca(int u, int v) {
    if(u == 0 || v == 0)
        return u | v;
    if(d[u] < d[v])
        std::swap(u, v);
    int delta = d[u] - d[v];
    for(int i = 0; i < 6; ++i)
        if(delta & (1 << i))
            u = p[u][i];
    if(u == v)
        return u;
    for(int i = 5; i >= 0; --i)
        if(p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    return p[u][0];
}
int T[size], C[size], in[size], q[size], ans = 0;
struct Sol {
    int lim, cw;
    Sol(int lim, int cw) : lim(lim), cw(cw) {}
};
std::vector<Sol> DFS(int u, int t) {
    ans = std::max(ans, t);
    std::vector<Sol> cur;
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        std::vector<Sol> vres = DFS(v, t + T[v]);
        if(i == B.last[u])
            cur = vres;
        else {
            std::vector<Sol> mix;
            for(int j = 0; j < cur.size(); ++j) {
                Sol a = cur[j];
                int minv = inf;
                for(int k = 0; k < vres.size(); ++k)
                    if(vres[k].lim >= a.lim)
                        minv =
                            std::min(vres[k].cw, minv);
                if(minv != inf) {
                    a.cw += minv;
                    mix.push_back(a);
                }
            }
            for(int j = 0; j < vres.size(); ++j) {
                Sol a = vres[j];
                int minv = inf;
                for(int k = 0; k < cur.size(); ++k)
                    if(cur[k].lim >= a.lim)
                        minv =
                            std::min(cur[k].cw, minv);
                if(minv != inf) {
                    a.cw += minv;
                    mix.push_back(a);
                }
            }
            cur.swap(mix);
        }
    }
    Sol base(T[u], C[u]);
    cur.erase(std::remove_if(cur.begin(), cur.end(),
                             [=](Sol sol) {
                                 return sol.lim <=
                                     base.lim &&
                                     sol.cw >= base.cw;
                             }),
              cur.end());
    cur.push_back(base);
    return cur;
}
int main() {
    int n, m, w;
    scanf("%d%d%d", &n, &m, &w);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &T[i]);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &C[i]);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        A.addEdge(u, v);
        ++in[v];
    }
    int rt = n + 1, qcnt = 0;
    for(int i = 1; i <= n; ++i)
        if(!in[i]) {
            q[++qcnt] = i;
            p[i][0] = rt;
            d[i] = 1;
            B.addEdge(rt, i);
        }
    for(int i = 1; i <= qcnt; ++i) {
        int u = q[i];
        for(int j = A.last[u]; j; j = A.E[j].nxt) {
            int v = A.E[j].to;
            p[v][0] = lca(p[v][0], u);
            if(--in[v] == 0) {
                B.addEdge(p[v][0], v);
                for(int i = 1; i < 6; ++i)
                    p[v][i] = p[p[v][i - 1]][i - 1];
                d[v] = d[p[v][0]] + 1;
                q[++qcnt] = v;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        printf("fa %d %d\n", i, p[i][0]);
    std::vector<Sol> sols = DFS(rt, 0);
    int res = 0;
    for(int i = 0; i < sols.size(); ++i) {
        Sol cs = sols[i];
        if(cs.cw)
            res = std::max(
                res, std::min(cs.lim, w / cs.cw));
    }
    printf("%d\n", ans - res);
    return 0;
}
