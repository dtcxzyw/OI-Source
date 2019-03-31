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
const int size = 500005;
struct Graph {
    struct Edge {
        int to, nxt;
    } E[size];
    int last[size], cnt;
    Graph() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} G, Q;
char buf[size];
int d[size], L[size], R[size], son[size], seq[size],
    icnt = 0;
int DFS(int u, int dep) {
    L[u] = ++icnt;
    d[icnt] = dep, seq[icnt] = 1 << (buf[u] - 'a');
    int siz = 1, msiz = 0;
    for(int i = G.last[u]; i; i = G.E[i].nxt) {
        int v = G.E[i].to;
        int vsiz = DFS(v, dep + 1);
        siz += vsiz;
        if(msiz < vsiz)
            msiz = vsiz, son[u] = v;
    }
    R[u] = icnt;
    return siz;
}
int cnt[size];
bool ans[size];
bool query(int mask) {
    mask -= mask & -mask;
    return mask == 0;
}
void solve(int u, bool clean) {
    for(int i = G.last[u]; i; i = G.E[i].nxt) {
        int v = G.E[i].to;
        if(v != son[u])
            solve(v, true);
    }
    if(son[u])
        solve(son[u], false);
    for(int i = G.last[u]; i; i = G.E[i].nxt) {
        int v = G.E[i].to;
        if(v != son[u])
            for(int j = L[v]; j <= R[v]; ++j)
                cnt[d[j]] ^= seq[j];
    }
    cnt[d[L[u]]] ^= seq[L[u]];
    for(int i = Q.last[u]; i; i = Q.E[i].nxt) {
        int cd = Q.E[i].to;
        ans[i] = query(cnt[cd]);
    }
    if(clean) {
        for(int i = L[u]; i <= R[u]; ++i)
            cnt[d[i]] ^= seq[i];
    }
}
int main() {
    int n = read();
    int m = read();
    for(int i = 2; i <= n; ++i) {
        int p = read();
        G.addEdge(p, i);
    }
    scanf("%s", buf + 1);
    DFS(1, 1);
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int d = read();
        Q.addEdge(u, d);
    }
    solve(1, false);
    for(int i = 1; i <= m; ++i)
        puts(ans[i] ? "Yes" : "No");
    return 0;
}
