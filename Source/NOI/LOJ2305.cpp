#include <algorithm>
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
int getOp() {
    int c;
    do
        c = getchar();
    while(c < 'A' || c > 'C');
    return c;
}
const int maxn = 50005, maxm = maxn * 2;
struct Edge {
    int to, nxt;
} E[maxm * 2];
int last[maxm], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int dfn[maxm], low[maxm], ts, st[maxm],
    top = 0, col[maxm], ccnt;
bool flag[maxm];
void DFS(int u) {
    dfn[u] = low[u] = ++ts;
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
    if(dfn[u] <= low[u]) {
        int c = ++ccnt, v;
        do {
            v = st[top--];
            flag[v] = false;
            col[v] = c;
        } while(v != u);
    }
}
struct Link {
    int u, x, v, y;
} L[maxm];
char buf[maxn], res[maxn], rmap[128][2], map[maxn][2];
bool solve(int n, int m) {
    cnt = ts = ccnt = 0;
    memset(last + 2, 0, sizeof(int) * 2 * n);
    for(int i = 1; i <= m; ++i) {
        if(L[i].x == buf[L[i].u] - 'a' + 'A')
            continue;
        int cu =
            L[i].u << 1 | (L[i].x == map[L[i].u][1]);
        if(L[i].y == buf[L[i].v] - 'a' + 'A')
            addEdge(cu, cu ^ 1);
        else {
            int cv = L[i].v << 1 |
                (L[i].y == map[L[i].v][1]);
            addEdge(cu, cv);
            addEdge(cv ^ 1, cu ^ 1);
        }
    }
    memset(dfn + 2, 0, sizeof(int) * 2 * n);
    int end = n * 2 + 1;
    for(int i = 2; i <= end; ++i) {
        if(!dfn[i])
            DFS(i);
        if((i & 1) && col[i] == col[i ^ 1])
            return false;
    }
    for(int i = 2; i <= end; i += 2)
        res[i >> 1] = map[i >> 1][col[i] > col[i ^ 1]];
    return true;
}
int pos[10];
int main() {
    rmap['a'][0] = 'B', rmap['a'][1] = 'C';
    rmap['b'][0] = 'A', rmap['b'][1] = 'C';
    rmap['c'][0] = 'A', rmap['c'][1] = 'B';
    int n, d, m;
    scanf("%d%d%s%d", &n, &d, buf + 1, &m);
    for(int i = 1; i <= m; ++i) {
        L[i].u = read();
        L[i].x = getOp();
        L[i].v = read();
        L[i].y = getOp();
    }
    int cd = 0;
    for(int i = 1; i <= n; ++i)
        if(buf[i] == 'x')
            pos[cd++] = i;
        else {
            map[i][0] = rmap[buf[i]][0];
            map[i][1] = rmap[buf[i]][1];
        }
    int end = 1 << d;
    for(int i = 0; i < end; ++i) {
        for(int j = 0; j < d; ++j) {
            int cp = pos[j];
            buf[cp] = 'a' + ((i >> j) & 1);
            map[cp][0] = rmap[buf[cp]][0];
            map[cp][1] = rmap[buf[cp]][1];
        }
        if(solve(n, m)) {
            for(int j = 1; j <= n; ++j)
                putchar(res[j]);
            puts("");
            return 0;
        }
    }
    puts("-1");
    return 0;
}
