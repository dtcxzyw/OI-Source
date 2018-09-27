#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int getOp() {
    int c;
    do
        c = getchar();
    while(c != 'C' && c != 'A');
    return c;
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
bool vis[size];
int root, tsiz, msiz, siz[size];
void getRootImpl(int u, int p) {
    int maxs = 0;
    siz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v] && v != p) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            maxs = std::max(maxs, siz[v]);
        }
    }
    maxs = std::max(maxs, tsiz - siz[u]);
    if(maxs < msiz) {
        msiz = maxs;
        root = u;
    }
}
int getRoot(int u, int csiz) {
    msiz = 1 << 30, tsiz = csiz;
    getRootImpl(u, 0);
    return root;
}
int dis1, c1;
void DFS(int u, int p, int base) {
    if(dis1 < base)
        dis1 = base, c1 = 0;
    if(dis1 == base)
        ++c1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v] && v != p)
            DFS(v, u, base + E[i].w);
    }
}
struct Info {
    int maxd, cnt;
} dp[size];
void solve(int u) {
    int dis2, dis3, c2, c3;
    dis2 = dis3 = c2 = c3 = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            dis1 = c1 = 0;
            DFS(v, u, E[i].w);
            int cdis3 = dis1 + dis2;
            if(dis3 < cdis3)
                dis3 = cdis3, c3 = 0;
            if(dis3 == cdis3)
                c3 += c1 * c2;
            if(dis1 > dis2)
                dis2 = dis1, c2 = 0;
            if(dis1 == dis2)
                c2 += c1;
        }
    }
    dp[u].maxd = dis3;
    dp[u].cnt = c3;
}
int fa[size];
void divide(int u) {
    solve(u);
    vis[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            fa[nrt] = u;
            divide(nrt);
        }
    }
}
void update(int u) {}
bool col[size];
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    int rt = getRoot(1, n);
    divide(rt);
    int q = read();
    while(q--) {
        if(getOp() == 'C') {
            int u = read();
            col[u] ^= 1;

            while(u) {
                update(u);
                u = fa[u];
            }
        } else {
            if(dp[rt].cnt)
                printf("%d\n", dp[rt].maxd);
            else
                puts("They have disappeared.");
        }
    }
    return 0;
}
