#include <algorithm>
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
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int tsiz, msiz, crt, siz[size];
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int csiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            csiz = std::max(csiz, siz[v]);
        }
    }
    csiz = std::max(csiz, tsiz - siz[u]);
    if(csiz < msiz)
        msiz = csiz, crt = u;
}
int getRoot(int u, int csiz) {
    tsiz = csiz, msiz = 1 << 30;
    getRootImpl(u, 0);
    return crt;
}
Int64 ans[size], sans, cw[size], sum;
int C[size], cnum[size], cur = 0, ccnt[size];
bool first[size];
void DFS(int u, int p) {
    siz[u] = 1;
    if(++cnum[C[u]] == 1)
        first[u] = true, ++cur;
    else
        first[u] = false;
    ccnt[u] = cur, sans += cur;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            DFS(v, u);
            siz[u] += siz[v];
        }
    }
    if(--cnum[C[u]] == 0) {
        --cur;
        cw[C[u]] += siz[u];
        sum += siz[u];
    }
}
void modify(int u, int p, bool op) {
    if(first[u]) {
        if(op)
            cw[C[u]] -= siz[u], sum -= siz[u];
        else
            cw[C[u]] += siz[u], sum += siz[u];
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            modify(v, u, op);
    }
}
void calc(int u, int p, Int64 ssiz) {
    if(first[u])
        sum -= cw[C[u]];
    ans[u] += sum + ssiz * ccnt[u];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            calc(v, u, ssiz);
    }
    if(first[u])
        sum += cw[C[u]];
}
void clear(int u, int p) {
    cw[C[u]] = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            clear(v, u);
    }
}
void solve(int u) {
    sans = sum = 0;
    DFS(u, 0);
    sum -= siz[u], cw[C[u]] -= siz[u];
    ans[u] += sans;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            modify(v, u, true);
            calc(v, u, siz[u] - siz[v]);
            modify(v, u, false);
        }
    }
    clear(u, 0);
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            divide(nrt);
        }
    }
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        C[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    divide(getRoot(1, n));
    for(int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
