#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 100005, maxv = 2 * size;
struct G {
    struct Edge {
        int to, nxt;
    } E[size * 4];
    int last[maxv], cnt;
    void reset() {
        cnt = 0;
        memset(last, 0, sizeof(last));
    }
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} A, B;
int dfn[size], low[size], st[maxv], ssiz, icnt, nsiz;
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
                B.addEdge(u, id);
                do {
                    p = st[ssiz--];
                    B.addEdge(id, p);
                } while(p != v);
            }
        }
    }
}
int id[maxv], len[maxv], d[maxv], p[maxv], son[maxv],
    n;
int buildTree(int u) {
    id[u] = ++icnt;
    int siz = 1, msiz = 0;
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        p[v] = u;
        d[v] = d[u] + 1;
        len[v] = len[u] + (v <= n);
        int vsiz = buildTree(v);
        siz += vsiz;
        if(vsiz > msiz)
            msiz = vsiz, son[u] = v;
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
bool cmp(int a, int b) {
    return id[a] < id[b];
}
int S[maxv];
int calc() {
    int k = read();
    for(int i = 1; i <= k; ++i)
        S[i] = read();
    std::sort(S + 1, S + k + 1, cmp);
    int top = 1, res = -k;
    st[1] = S[1];
    for(int i = 2; i <= k; ++i) {
        int u = S[i];
        int lca = getLCA(u, st[top]);
        while(top > 1 && d[st[top - 1]] > d[lca]) {
            res += len[st[top]] - len[st[top - 1]];
            --top;
        }
        if(d[st[top]] > d[lca]) {
            res += len[st[top]] - len[lca];
            --top;
        }
        if(top == 0 || d[st[top]] < d[lca])
            st[++top] = lca;
        st[++top] = u;
    }
    res += len[st[top]] - len[p[st[1]]];
    return res;
}
void foo() {
    A.reset();
    B.reset();
    icnt = ssiz = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(top, 0, sizeof(top));
    memset(son, 0, sizeof(son));
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
    icnt = 0;
    len[1] = 1;
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    int q = read();
    for(int i = 1; i <= q; ++i) {
        write(calc());
        IO::putc('\n');
    }
}
int main() {
    IO::init();
    int t = read();
    for(int i = 1; i <= t; ++i)
        foo();
    IO::uninit();
    return 0;
}
