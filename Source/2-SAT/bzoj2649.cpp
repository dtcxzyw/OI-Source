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
void write(int x) {
    if(x >= 10)
        write(x / 10);
    putchar('0' + x % 10);
}
const int size = 1000005, maxv = size * 4,
          maxe = size * 2;
struct Edge {
    int to, nxt;
} E[maxe];
int last[size * 2], cnt = 0;
void addEdgeImpl(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
void addEdge(int u, int a, int v, int b) {
    u = u << 1 | a, v = v << 1 | b;
    addEdgeImpl(u, v);
    addEdgeImpl(v ^ 1, u ^ 1);
}
int pre[size], nxt[size], n;
void genNxt(int u, int* ed, int& lcnt) {
    int col = u & 1, id = u >> 1;
    if(id <= n) {
        if(col) {
            if(pre[id])
                ed[lcnt++] = (pre[id] + n) << 1;
            ed[lcnt++] = (id + n) << 1 | 1;
        }
    } else {
        int rid = id - n;
        if(col) {
            if(nxt[rid]) {
                ed[lcnt++] = nxt[rid] << 1;
                ed[lcnt++] = (nxt[rid] + n) << 1 | 1;
            }
        } else {
            ed[lcnt++] = rid << 1;
            if(pre[rid])
                ed[lcnt++] = (pre[rid] + n) << 1;
        }
    }
}
int dfn[maxv], low[maxv], icnt = 0, st[maxv], top = 0,
                          col[maxv], ccnt = 0;
bool flag[maxv];
void DFS(int u);
void update(int u, int v) {
    if(dfn[v]) {
        if(flag[v])
            low[u] = std::min(low[u], dfn[v]);
    } else {
        DFS(v);
        low[u] = std::min(low[u], low[v]);
    }
}
void DFS(int u) {
    dfn[u] = low[u] = ++icnt;
    flag[u] = true;
    st[++top] = u;
    if((u >> 1) <= n) {
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            update(u, v);
        }
    }
    int ed[2], lcnt = 0;
    genNxt(u, ed, lcnt);
    for(int i = 0; i < lcnt; ++i)
        update(u, ed[i]);
    if(dfn[u] == low[u]) {
        ++ccnt;
        int v;
        do {
            v = st[top--];
            flag[v] = false;
            col[v] = ccnt;
        } while(v != u);
    }
}
int gid[size], ans[size];
int main() {
    n = read();
    int m = read();
    int k = read();
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        addEdge(u, 0, v, 1);
    }
    for(int i = 1; i <= k; ++i) {
        int w = read(), last = 0;
        for(int j = 0; j < w; ++j) {
            int u = read();
            gid[u] = i;
            ans[i] = u;
            pre[u] = last;
            nxt[last] = u;
            last = u;
        }
    }
    int end = n << 2 | 1;
    for(int i = 2; i <= end; ++i) {
        if(!dfn[i])
            DFS(i);
        if((i & 1) && col[i] == col[i ^ 1]) {
            puts("NIE");
            return 0;
        }
    }
    puts("TAK");
    for(int i = 1; i <= n; ++i)
        if(col[i << 1 | 1] < col[i << 1])
            ans[gid[i]] = i;
    for(int i = 1; i <= k; ++i) {
        write(ans[i]);
        putchar(' ');
    }
    return 0;
}
