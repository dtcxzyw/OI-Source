//TODO:P4782
#include <algorithm>
#include <cstdio>
#include <vector>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 2000005;
struct G {
    struct Edge {
        int to, nxt;
    } E[size];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} g1, g2;
int dfn[size] = {}, low[size], st[size], col[size], top = 0, icnt = 0, ccnt = 0;
bool flag[size] = {};
std::vector<int> nodes[size];
void DFS(int u) {
    dfn[u] = low[u] = ++icnt;
    flag[u] = true;
    st[++top] = u;
    for (int i = g1.last[u]; i; i = g1.E[i].nxt) {
        int v = g1.E[i].to;
        if (dfn[v]) {
            if (flag[v])
                low[u] = std::min(low[u], dfn[v]);
        } else {
            DFS(v);
            low[u] = std::min(low[u], low[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++ccnt;
        int v;
        do {
            v = st[top--];
            col[v] = ccnt;
            nodes[ccnt].push_back(v);
            flag[v] = false;
        } while (u != v);
    }
}
bool solve(int n) {
    int end = n << 1 | 1;
    for (int i = 1; i <= end; ++i)
        if (!dfn[i])
            DFS(i);
    for (int i = 2; i <= end; i += 2)
        if (col[i] == col[i + 1])
            return false;
    return true;
}
int res[size] = {};
void color(int u) {
    res[u] = 2;
    for (int i = g2.last[u]; i; i = g2.E[i].nxt) {
        int v = g2.E[i].to;
        if (res[v] == 0) color(v);
    }
}
int main() {
    int n = read();
    int m = read();
    while (m--) {
        int u = read();
        int a = read();
        int v = read();
        int b = read();
        g1.addEdge(u << 1 | (a ^ 1), v << 1 | b);
        g1.addEdge(v << 1 | (b ^ 1), u << 1 | a);
    }
    if (solve(n)) {
        puts("POSSIBLE");
        int end = n << 1 | 1;
        for (int i = 1; i <= end; ++i)
            for (int j = g1.last[i]; j; j = g1.E[j].nxt) {
                int v = g1.E[i].to;
                if (col[i] != col[v])
                    g2.addEdge(col[i], col[v]);
            }
        for (int i = 1; i <= ccnt; ++i)
            if (res[i] == 0) {
                res[i] = 1;
                for (int j = 0; j < nodes[i].size(); ++j) {
                    int to = col[nodes[i][j] ^ 1];
                    if (res[to] == 0) color(to);
                }
            }
        for (int i = 1; i <= n; ++i) {
            putchar(res[col[i << 1]] == 1 ? '0' : '1');
            putchar(' ');
        }
    } else
        puts("IMPOSSIBLE");
    return 0;
}
