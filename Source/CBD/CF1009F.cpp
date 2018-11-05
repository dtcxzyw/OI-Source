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
void print(int x) {
    if(x >= 10)
        print(x / 10);
    putchar('0' + x % 10);
}
const int size = 1000005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int son[size], cl[size];
int DFS(int u, int p, int d) {
    int md = ++d;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            int vmd = DFS(v, u, d);
            if(vmd > md)
                md = vmd, son[u] = v;
        }
    }
    cl[u] = md - d + 1;
    return md;
}
int dp[size], ans[size], alp = 0;
bool vis[size];
int solve(int u) {
    int beg = alp++;
    ++dp[beg];
    vis[u] = true;
    int res = beg, sp = beg, cmd = 0;
    if(son[u])
        sp = solve(son[u]);
    int scl = beg + 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int lp = beg + 1, rp = alp,
                end = rp + cl[v];
            solve(v);
            while(rp < end)
                dp[lp++] += dp[rp++];
            if(scl < lp)
                scl = lp;
        }
    }
    for(int i = beg; i < scl; ++i)
        if(dp[i] > cmd)
            res = i, cmd = dp[i];
    if(dp[sp] > cmd || (dp[sp] >= cmd && sp < res))
        res = sp;
    ans[u] = res - beg;
    return res;
}
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    DFS(1, 0, 0);
    solve(1);
    for(int i = 1; i <= n; ++i) {
        print(ans[i]);
        putchar('\n');
    }
    return 0;
}
