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
const int size = 2000005;
struct Edge {
    int to, nxt;
} E[size];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int dfn[size] = {}, low[size], st[size], col[size],
    top = 0, icnt = 0, ccnt = 0;
bool flag[size] = {};
void DFS(int u) {
    dfn[u] = low[u] = ++icnt;
    flag[u] = true;
    st[++top] = u;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(dfn[v]) {
            if(flag[v])
                low[u] = std::min(low[u], dfn[v]);
        } else {
            DFS(v);
            low[u] = std::min(low[u], low[v]);
        }
    }
    if(low[u] == dfn[u]) {
        ++ccnt;
        int v;
        do {
            v = st[top--];
            col[v] = ccnt;
            flag[v] = false;
        } while(u != v);
    }
}
bool solve(int n) {
    int end = n << 1 | 1;
    for(int i = 1; i <= end; ++i)
        if(!dfn[i])
            DFS(i);
    for(int i = 2; i <= end; i += 2)
        if(col[i] == col[i + 1])
            return false;
    return true;
}
int main() {
    int n = read();
    int m = read();
    while(m--) {
        int u = read();
        int a = read();
        int v = read();
        int b = read();
        addEdge(u << 1 | (a ^ 1), v << 1 | b);
        addEdge(v << 1 | (b ^ 1), u << 1 | a);
    }
    if(solve(n)) {
        puts("POSSIBLE");
        for(int i = 1; i <= n; ++i) {
            putchar(col[i << 1] < col[i << 1 | 1] ?
                        '0' :
                        '1');
            putchar(' ');
        }
    } else
        puts("IMPOSSIBLE");
    return 0;
}
