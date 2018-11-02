#include <cstdio>
#include <cstring>
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
const int size = 505, esiz = 100005;
struct Edge {
    int to, nxt;
} E[esiz];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
bool use[esiz], flag[size], vis[size];
int st[size], top = 0, ec[esiz];
void scan(int u) {
    vis[u] = flag[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(flag[v]) {
            ++ec[i];
            int ct = top;
            while(ct && E[st[ct]].to != v) {
                int id = st[ct];
                ++ec[id];
                --ct;
            }
        }
        if(!use[i]) {
            use[i] = true;
            st[++top] = i;
            scan(v);
            --top;
            use[i] = false;
        }
    }
    flag[u] = false;
}
int ban;
bool DFS(int u) {
    vis[u] = flag[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(i != ban && (flag[v] || DFS(v)))
            return true;
    }
    flag[u] = false;
    return false;
}
bool solve(int n, int m) {
    for(int i = 1; i <= n; ++i)
        if(!vis[i])
            scan(i);
    memset(vis, 0, sizeof(vis));
    ban = 1;
    for(int i = 2; i <= m; ++i)
        if(ec[ban] < ec[i])
            ban = i;
    for(int i = 1; i <= n; ++i)
        if(!vis[i] && DFS(i))
            return false;
    return true;
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
    }
    puts(solve(n, m) ? "YES" : "NO");
    return 0;
}
