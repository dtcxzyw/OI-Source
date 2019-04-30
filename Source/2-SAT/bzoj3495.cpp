#include <algorithm>
#include <cstdio>
namespace IO {
    char buf[1 << 23];
    char getc() {
        static char *S = buf, *T = buf;
        if(S == T)
            S = buf, T = buf +
                fread(buf, 1, sizeof(buf), stdin);
        return S != T ? *S++ : EOF;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 4000500;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdgeImpl(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
void addEdge(int u, int uc, int v, int vc) {
    int idu = u << 1 | uc, idv = v << 1 | vc;
    addEdgeImpl(idu, idv);
    addEdgeImpl(idv ^ 1, idu ^ 1);
}
int dfn[size], low[size], icnt = 0, st[size], top = 0,
                          col[size], ccnt = 0;
bool flag[size];
void DFS(int u) {
    dfn[u] = low[u] = ++icnt;
    st[++top] = u;
    flag[u] = true;
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
int main() {
    int n = read();
    int m = read();
    int k = read();
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        addEdge(u, 0, v, 1);
    }
    for(int t = 1; t <= k; ++t) {
        int c = read(), last = 0;
        for(int i = 0; i < c; ++i) {
            int u = read();
            addEdge(u, 1, u + n, 1);
            if(i) {
                addEdge(u, 1, last, 0);
                addEdge(last, 1, u + n, 1);
            }
            last = u + n;
        }
    }
    int end = n * 4 + 1;
    for(int i = 2; i <= end; ++i) {
        if(!dfn[i])
            DFS(i);
        if((i & 1) && col[i] == col[i ^ 1]) {
            puts("NIE");
            return 0;
        }
    }
    puts("TAK");
    return 0;
}
