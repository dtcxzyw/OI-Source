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
const int size = 105;
struct Edge {
    int to, nxt;
} E[size * size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
bool vis[size], col[size];
bool DFS(int u, bool c) {
    if(vis[u])
        return col[u] == c;
    vis[u] = true;
    col[u] = c;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!DFS(v, !c))
            return false;
    }
    return true;
}
int main() {
    int n = read();
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    bool flag = true;
    for(int i = 1; i <= n && flag; ++i)
        if(!vis[i])
            flag &= DFS(i, false);
    puts(flag ? "Yes" : "No");
    return 0;
}
