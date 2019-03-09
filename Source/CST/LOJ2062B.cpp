#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
namespace IO {
    const int size = 1 << 23;
    char in[size];
    void init() {
        setvbuf(stdin, 0, _IONBF, 0);
        setvbuf(stdout, 0, _IONBF, 0);
        fread(in, 1, size, stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[size], *S = out;
    void putc(char ch) {
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
    } E[size * 3];
    int last[maxv], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].nxt = last[u], E[cnt].to = v;
        last[u] = cnt;
    }
} A, B;
int p[size], dfn[size], icnt = 0, nsiz;
bool ring[size];
void DFS(int u) {
    dfn[u] = ++icnt;
    for(int i = A.last[u]; i; i = A.E[i].nxt) {
        int v = A.E[i].to;
        if(v == p[u])
            continue;
        if(dfn[v]) {
            if(dfn[v] < dfn[u]) {
                int id = ++nsiz;
                for(int j = u; j != v; j = p[j])
                    B.addEdge(id, j), ring[j] = true;
                B.addEdge(v, id), ring[v] = true;
            }
        } else {
            ring[u] = false;
            p[v] = u;
            DFS(v);
            if(!ring[u])
                B.addEdge(u, v);
        }
    }
}
int S[2][size], siz;
void add(int* A, int x) {
    while(x <= siz) {
        ++A[x];
        x += x & -x;
    }
}
void sub(int* A, int x) {
    while(x <= siz) {
        --A[x];
        x += x & -x;
    }
}
int query(int* A, int x) {
    int res = 0;
    while(x) {
        res += A[x];
        x -= x & -x;
    }
    return res;
}
int C[size];
void add(int u) {
    if(u) {
        ++C[u];
        int col = C[u] & 1;
        add(S[col], u);
        if(C[u] > 1)
            sub(S[col ^ 1], u);
    }
}
void sub(int u) {
    if(u) {
        --C[u];
        int col = C[u] & 1;
        sub(S[col ^ 1], u);
        if(C[u])
            add(S[col], u);
    }
}
int X[size], son[maxv], idc[maxv], L[maxv], R[maxv],
    pcnt = 0, n;
int buildTree(int u) {
    idc[++pcnt] = (u <= n ? X[u] : 0);
    L[u] = pcnt;
    int siz = 1, msiz = 0;
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        int vsiz = buildTree(v);
        siz += vsiz;
        if(vsiz > msiz)
            msiz = vsiz, son[u] = v;
    }
    R[u] = pcnt;
    return siz;
}
struct Query {
    int id, y, ty;
    Query(int id, int y, int ty)
        : id(id), y(y), ty(ty) {}
};
std::vector<Query> Q[size];
int ans[size];
void solve(int u, bool clear) {
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        if(v != son[u])
            solve(v, true);
    }
    bool needQ = (u <= n && Q[u].size());
    if(clear && !needQ) {
        if(son[u])
            solve(son[u], true);
    } else {
        if(son[u])
            solve(son[u], false);
        for(int i = B.last[u]; i; i = B.E[i].nxt) {
            int v = B.E[i].to;
            if(v == son[u])
                continue;
            for(int j = L[v]; j <= R[v]; ++j)
                add(idc[j]);
        }
        if(u <= n)
            add(X[u]);
        if(u <= n) {
            for(int i = 0; i < Q[u].size(); ++i) {
                Query q = Q[u][i];
                ans[q.id] = query(S[q.ty], q.y);
            }
        }
        if(clear) {
            for(int i = L[u]; i <= R[u]; ++i)
                sub(idc[i]);
        }
    }
}
int Y[size];
int main() {
    IO::init();
    n = read();
    int m = read();
    for(int i = 1; i <= n; ++i)
        X[i] = read();
    memcpy(Y + 1, X + 1, sizeof(int) * n);
    std::sort(Y + 1, Y + n + 1);
    siz = std::unique(Y + 1, Y + n + 1) - (Y + 1);
    for(int i = 1; i <= n; ++i)
        X[i] = std::lower_bound(Y + 1, Y + siz + 1,
                                X[i]) -
            Y;
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        A.addEdge(u, v);
        A.addEdge(v, u);
    }
    nsiz = n;
    DFS(1);
    buildTree(1);
    int q = read();
    for(int i = 1; i <= q; ++i) {
        int ty = read();
        int x = read();
        int y = std::upper_bound(Y + 1, Y + siz + 1,
                                 read()) -
            Y - 1;
        if(y)
            Q[x].push_back(Query(i, y, ty));
    }
    solve(1, false);
    for(int i = 1; i <= q; ++i) {
        write(ans[i]);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
