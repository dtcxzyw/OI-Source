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
const int size = 20005;
struct Edge {
    int to, nxt;
} E[size * 10];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int dfn[size], low[size], ccnt = 0;
bool cut[size];
void DFS(int u, int p) {
    static int icnt = 0;
    dfn[u] = low[u] = ++icnt;
    int child = 0;
    bool flag = false;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            if(dfn[v])
                low[u] = std::min(low[u], dfn[v]);
            else {
                DFS(v, u);
                ++child;
                low[u] = std::min(low[u], low[v]);
                if(p && dfn[u] <= low[v])
                    flag = true;
            }
        }
    }
    if(!p && child > 1)
        flag = true;
    if(flag) {
        cut[u] = true;
        ++ccnt;
    }
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
    for(int i = 1; i <= n; ++i)
        if(!dfn[i])
            DFS(i, 0);
    printf("%d\n", ccnt);
    for(int i = 1; i <= n; ++i)
        if(cut[i])
            printf("%d ", i);
    return 0;
}
