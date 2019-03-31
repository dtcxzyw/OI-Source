#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long Int64;
Int64 read() {
    Int64 res = 0, c;
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
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int siz[size], nrt, cmsiz, tsiz;
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p || vis[v])
            continue;
        getRootImpl(v, u);
        siz[u] += siz[v];
        msiz = std::max(msiz, siz[v]);
    }
    msiz = std::max(msiz, tsiz - siz[u]);
    if(cmsiz > msiz)
        cmsiz = msiz, nrt = u;
}
int getRoot(int u, int usiz) {
    cmsiz = 1 << 30, tsiz = usiz;
    getRootImpl(u, 0);
    return nrt;
}
int S[size], maxs;
void modify(int x, int op) {
    while(x <= maxs) {
        S[x] += op;
        x += x & -x;
    }
}
int query(int x) {
    int res = 0;
    while(x) {
        res += S[x];
        x -= x & -x;
    }
    return res;
}
int pcnt;
Int64 dis[size], cdis[size];
int find(Int64 d) {
    return std::upper_bound(cdis + 1, cdis + maxs + 1,
                            d) -
        cdis - 1;
}
void DFS(int u, int p, Int64 d) {
    dis[++pcnt] = d;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p || vis[v])
            continue;
        DFS(v, u, d + E[i].w);
    }
}
std::vector<std::pair<int, Int64> > Q[size];
int ans[size];
void calc(int u, int p, Int64 d) {
    for(int i = 0; i < Q[u].size(); ++i)
        ans[Q[u][i].first] +=
            query(find(Q[u][i].second - d));
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p || vis[v])
            continue;
        calc(v, u, d + E[i].w);
    }
}
void solve(int u) {
    pcnt = 0;
    DFS(u, 0, 0);
    std::sort(dis + 1, dis + pcnt + 1);
    maxs = std::unique_copy(dis + 1, dis + pcnt + 1,
                            cdis + 1) -
        (cdis + 1);
    for(int i = 1; i <= maxs; ++i)
        S[i] = 0;
    for(int i = 1; i <= pcnt; ++i)
        ++S[find(dis[i])];
    for(int i = 1; i <= maxs; ++i) {
        int j = i + (i & -i);
        if(j <= maxs)
            S[j] += S[i];
    }
    for(int i = 0; i < Q[u].size(); ++i)
        ans[Q[u][i].first] +=
            query(find(Q[u][i].second));
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(vis[v])
            continue;
        pcnt = 0;
        DFS(v, u, E[i].w);
        for(int j = 1; j <= pcnt; ++j)
            modify(find(dis[j]), -1);
        calc(v, u, E[i].w);
        for(int j = 1; j <= pcnt; ++j)
            modify(find(dis[j]), 1);
    }
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int crt = getRoot(v, siz[v]);
            divide(crt);
        }
    }
}
int main() {
    int n = read();
    int q = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    for(int i = 1; i <= q; ++i) {
        int u = read();
        Int64 l = read();
        Q[u].push_back(std::make_pair(i, l));
    }
    divide(getRoot(1, n));
    for(int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
