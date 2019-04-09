#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
namespace IO {
    char in[1 << 25];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 23], *S = out;
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
void writeImpl(int x) {
    if(x >= 10)
        writeImpl(x / 10);
    IO::putc('0' + x % 10);
}
void write(int x) {
    if(x != -1)
        writeImpl(x);
    else {
        IO::putc('-');
        IO::putc('1');
    }
    IO::putc('\n');
}
const int size = 100005, maxT = 2 * size,
          maxE = 500005, maxQ = 500005;
struct Node {
    int l, r, siz;
} T[size * 20];
int tcnt = 0;
int build(int l, int r, int p) {
    int id = ++tcnt;
    T[id].siz = 1;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = build(l, m, p);
        else
            T[id].r = build(m + 1, r, p);
    }
    return id;
}
int merge(int u, int v) {
    if(u && v) {
        T[u].siz += T[v].siz;
        T[u].l = merge(T[u].l, T[v].l);
        T[u].r = merge(T[u].r, T[v].r);
        return u;
    }
    return u | v;
}
int queryKth(int l, int r, int id, int k) {
    if(l == r)
        return l;
    else {
        int m = (l + r) >> 1, rsiz = T[T[id].r].siz;
        if(k > rsiz)
            return queryKth(l, m, T[id].l, k - rsiz);
        else
            return queryKth(m + 1, r, T[id].r, k);
    }
}
struct Edge {
    int to, nxt;
} E[maxT];
int last[maxT], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int p[maxT][20], root[maxT];
void DFS(int u) {
    for(int i = 1; i < 20; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        p[v][0] = u;
        DFS(v);
    }
}
int A[maxT];
int jump(int v, int x) {
    for(int i = 19; i >= 0; --i)
        if(A[p[v][i]] <= x)
            v = p[v][i];
    return v;
}
std::vector<std::pair<int, int> > Q[maxT];
int ans[maxQ], siz;
void solve(int u) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        solve(v);
        root[u] = merge(root[u], root[v]);
    }
    for(int i = 0; i < Q[u].size(); ++i) {
        int id = Q[u][i].first;
        int k = Q[u][i].second;
        ans[id] = (T[root[u]].siz >= k ?
                       queryKth(1, siz, root[u], k) :
                       0);
    }
}
int H[size], X[size], fa[maxT];
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
struct Info {
    int u, v, c;
    bool operator<(const Info& rhs) const {
        return c < rhs.c;
    }
} L[maxE];
int main() {
    IO::init();
    int n = read();
    int m = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        H[i] = read();
    memcpy(X + 1, H + 1, sizeof(int) * n);
    std::sort(X + 1, X + n + 1);
    siz = std::unique(X + 1, X + n + 1) - (X + 1);
    for(int i = 1; i <= n; ++i) {
        int pos = std::lower_bound(X + 1, X + siz + 1,
                                   H[i]) -
            X;
        root[i] = build(1, siz, pos);
    }
    for(int i = 0; i < m; ++i) {
        L[i].u = read();
        L[i].v = read();
        L[i].c = read();
    }
    std::sort(L, L + m);
    int icnt = n;
    A[0] = 1 << 30;
    for(int i = 0; i < m; ++i) {
        int u = find(L[i].u), v = find(L[i].v);
        if(u != v) {
            int id = ++icnt;
            fa[u] = fa[v] = id;
            A[id] = L[i].c;
            addEdge(id, u);
            addEdge(id, v);
        }
    }
    DFS(icnt);
    for(int i = 1; i <= q; ++i) {
        int u = read();
        int x = read();
        int k = read();
        int p = jump(u, x);
        Q[p].push_back(std::make_pair(i, k));
    }
    solve(icnt);
    X[0] = -1;
    for(int i = 1; i <= q; ++i)
        write(X[ans[i]]);
    IO::uninit();
    return 0;
}
