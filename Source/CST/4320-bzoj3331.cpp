#include <algorithm>
#include <cstdio>
namespace IO {
    void init() {
        setvbuf(stdin, 0, _IONBF, 0);
        setvbuf(stdout, 0, _IONBF, 0);
    }
    const int size = 1 << 23;
    char in[size];
    char getc() {
        static char *S = in, *T = in;
        if(S == T)
            S = in, T = in + fread(in, 1, size, stdin);
        return S == T ? EOF : *S++;
    }
    char out[size], *S = out, *T = out + size;
    void putc(char ch) {
        if(S == T) {
            fwrite(out, size, 1, stdout);
            S = out;
        }
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
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
void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 500005, maxv = 2 * size;
struct G {
    struct Edge {
        int to, nxt;
    } E[size * 4];
    int last[maxv], cnt = 0;
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} A, B;
int dfn[size], low[size], st[size], ssiz = 0, icnt = 0,
                                    nsiz;
void DFS(int u) {
    dfn[u] = low[u] = ++icnt;
    st[++ssiz] = u;
    for(int i = A.last[u]; i; i = A.E[i].nxt) {
        int v = A.E[i].to;
        if(dfn[v])
            low[u] = std::min(low[u], dfn[v]);
        else {
            DFS(v);
            low[u] = std::min(low[u], low[v]);
            if(dfn[u] <= low[v]) {
                int id = ++nsiz, p;
                do {
                    p = st[ssiz--];
                    B.addEdge(id, p);
                } while(p != v);
                B.addEdge(u, id);
            }
        }
    }
}
int son[maxv], p[maxv], d[maxv], len[maxv], n;
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        if(v != p[u]) {
            p[v] = u;
            d[v] = d[u] + 1;
            len[v] = len[u] + (v <= n);
            int vsiz = buildTree(v);
            siz += vsiz;
            if(vsiz > msiz)
                msiz = vsiz, son[u] = v;
        }
    }
    return siz;
}
int top[maxv];
void buildChain(int u) {
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
int getLCA(int u, int v) {
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]])
            std::swap(u, v);
        u = p[top[u]];
    }
    return d[u] < d[v] ? u : v;
}
int main() {
    IO::init();
    n = read();
    int m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        A.addEdge(u, v);
        A.addEdge(v, u);
    }
    nsiz = n;
    DFS(1);
    len[1] = 1;
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    int q = read();
    for(int i = 1; i <= q; ++i) {
        int u = read();
        int v = read();
        int lca = getLCA(u, v);
        write(len[u] + len[v] - len[lca] -
              len[p[lca]]);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
