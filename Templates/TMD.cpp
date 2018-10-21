// P4074
#include <algorithm>
#include <cmath>
#include <cstdio>
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
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int d[size], p[size][17], L[size], R[size],
    id[size * 2], icnt = 0;
void DFS(int u) {
    for(int i = 1; i < 17; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    L[u] = ++icnt;
    id[icnt] = u;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u][0]) {
            d[v] = d[u] + 1;
            p[v][0] = u;
            DFS(v);
        }
    }
    R[u] = ++icnt;
    id[icnt] = u;
}
int getLCA(int u, int v) {
    if(d[u] < d[v])
        std::swap(u, v);
    int delta = d[u] - d[v];
    for(int i = 0; i < 17; ++i)
        if(delta & (1 << i))
            u = p[u][i];
    if(u == v)
        return u;
    for(int i = 16; i >= 0; --i)
        if(p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];
    return p[u][0];
}
int bid[size * 2], v[size], w[size], c[size],
    ccnt[size], tmpc[size];
bool flag[size];
Int64 ans = 0;
void modify(int u) {
    flag[u] ^= 1;
    int t = c[u];
    if(flag[u])
        ans += v[t] * asInt64(w[++ccnt[t]]);
    else
        ans -= v[t] * asInt64(w[ccnt[t]--]);
}
struct Modify {
    int u, col, pcl, t;
} M[size];
void modify(int u, int dst) {
    bool t = flag[u];
    if(t)
        modify(u);
    c[u] = dst;
    if(t)
        modify(u);
}
struct Query {
    int l, r, id, lca, t;
    bool operator<(const Query& rhs) const {
        if(bid[l] != bid[rhs.l])
            return l < rhs.l;
        if(bid[r] != bid[rhs.r])
            return r < rhs.r;
        return t < rhs.t;
    }
} Q[size];
Int64 res[size];
int main() {
    int n = read();
    int m = read();
    int q = read();
    for(int i = 1; i <= m; ++i)
        v[i] = read();
    for(int i = 1; i <= n; ++i)
        w[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    DFS(1);
    int siz = pow(icnt, 2.0 / 3.0);
    for(int i = 1, cp = 1; cp <= icnt; ++i) {
        for(int j = 0; j < siz && cp <= icnt;
            ++j, ++cp)
            bid[cp] = i;
    }
    for(int i = 1; i <= n; ++i)
        tmpc[i] = c[i] = read();
    int mcnt = 0, qcnt = 0;
    for(int i = 1; i <= q; ++i) {
        if(read()) {
            int u = read();
            int v = read();
            if(L[u] > L[v])
                std::swap(u, v);
            int lca = getLCA(u, v);
            Query& cur = Q[qcnt++];
            cur.l = (lca == u ? L[u] : R[u]);
            cur.r = L[v];
            cur.t = i;
            cur.id = qcnt;
            cur.lca = (lca == u ? 0 : lca);
        } else {
            Modify& cur = M[++mcnt];
            cur.u = read();
            cur.col = read();
            cur.t = i;
            cur.pcl = tmpc[cur.u];
            tmpc[cur.u] = cur.col;
        }
    }
    std::sort(Q, Q + qcnt);
    M[0].t = 0;
    M[mcnt + 1].t = 1 << 30;
    int ct = 0, cl = 1, cr = 0;
    for(int i = 0; i < qcnt; ++i) {
        while(M[ct + 1].t < Q[i].t) {
            ++ct;
            modify(M[ct].u, M[ct].col);
        }
        while(M[ct].t > Q[i].t) {
            modify(M[ct].u, M[ct].pcl);
            --ct;
        }
        while(cr < Q[i].r)
            modify(id[++cr]);
        while(cr > Q[i].r)
            modify(id[cr--]);
        while(cl < Q[i].l)
            modify(id[cl++]);
        while(cl > Q[i].l)
            modify(id[--cl]);
        if(Q[i].lca)
            modify(Q[i].lca);
        res[Q[i].id] = ans;
        if(Q[i].lca)
            modify(Q[i].lca);
    }
    for(int i = 1; i <= qcnt; ++i)
        printf("%lld\n", res[i]);
    return 0;
}
