#include <algorithm>
#include <cstdio>
namespace IO {
    const int size = 1 << 23;
    char in[size], *IS = in;
    void init() {
        setvbuf(stdin, 0, _IONBF, 0);
        setvbuf(stdout, 0, _IONBF, 0);
        fread(in, 1, size, stdin);
    }
    char getc() {
        return *IS++;
    }
    char out[size], *OS = out;
    void putc(char ch) {
        *OS++ = ch;
    }
    void uninit() {
        fwrite(out, OS - out, 1, stdout);
    }
}
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
const int size = 100005;
typedef long long Int64;
const Int64 inf = 123456789123456789;
#define asInt64 static_cast<Int64>
void writeImpl(Int64 val) {
    if(val >= 10)
        writeImpl(val / 10);
    IO::putc('0' + val % 10);
}
void write(Int64 val) {
    if(val < 0)
        IO::putc('-'), val = -val;
    writeImpl(val);
    IO::putc('\n');
}
struct Line {
    Int64 k, b;
    Int64 operator()(Int64 x) const {
        return k * x + b;
    }
} L[size << 2];
Int64 minv[size << 2], xp[size];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void build(int l, int r, int id) {
    minv[id] = L[id].b = inf;
    if(l != r) {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
    }
}
void update(int l, int r, int id) {
    Line& A = L[id];
    minv[id] = std::min(
        A(A.k > 0 ? xp[l] : xp[r]),
        std::min(minv[id << 1], minv[id << 1 | 1]));
}
void color(int l, int r, int id, const Line& B);
void color(int l, int r, int id, Int64 lp, Int64 rp,
           Int64 la, Int64 ra, Int64 lb, Int64 rb,
           Line& A, const Line& B) {
    if(lb <= la && rb <= ra)
        A = B;
    else {
        int m = (l + r) >> 1;
        Int64 deltaA = A.b - B.b, deltaB = B.k - A.k;
        if(deltaB < 0)
            deltaA = -deltaA, deltaB = -deltaB;
        bool ilp = deltaA <= xp[m] * deltaB;
        if(ilp)
            color(ls, la < lb ? A : B);
        else
            color(rs, ra < rb ? A : B);
        if(ilp ? ra > rb : la > lb)
            A = B;
    }
    if(l == r)
        minv[id] = A(lp);
    else
        update(l, r, id);
}
void color(int l, int r, int id, const Line& B) {
    Int64 lp = xp[l], rp = xp[r];
    Line& A = L[id];
    Int64 la = A(lp), ra = A(rp), lb = B(lp),
          rb = B(rp);
    if(la <= lb && ra <= rb)
        return;
    color(l, r, id, lp, rp, la, ra, lb, rb, A, B);
}
void insert(int l, int r, int id, int nl, int nr,
            const Line& B) {
    Int64 lp = xp[l], rp = xp[r];
    Line& A = L[id];
    Int64 la = A(lp), ra = A(rp), lb = B(lp),
          rb = B(rp);
    if(la <= lb && ra <= rb)
        return;
    if(nl <= l && r <= nr)
        color(l, r, id, lp, rp, la, ra, lb, rb, A, B);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert(ls, nl, nr, B);
        if(m < nr)
            insert(rs, nl, nr, B);
        update(l, r, id);
    }
}
Int64 res;
void query(int l, int r, int id, int nl, int nr) {
    if(minv[id] >= res)
        return;
    if(nl <= l && r <= nr)
        res = minv[id];
    else {
        res = std::min(
            res, L[id](L[id].k > 0 ? xp[nl] : xp[nr]));
        int m = (l + r) >> 1;
        if(nl <= m)
            query(ls, nl, std::min(m, nr));
        if(m < nr)
            query(rs, std::max(nl, m + 1), nr);
    }
}
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int son[size], d[size], p[size];
Int64 len[size];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u]) {
            p[v] = u;
            d[v] = d[u] + 1;
            len[v] = len[u] + E[i].w;
            int vsiz = buildTree(v);
            siz += vsiz;
            if(vsiz > msiz)
                son[u] = v, msiz = vsiz;
        }
    }
    return siz;
}
int top[size], id[size], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
    xp[icnt] = len[u];
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
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
Int64 query(int n, int u, int v) {
    res = inf;
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]])
            std::swap(u, v);
        query(1, n, 1, id[top[u]], id[u]);
        u = p[top[u]];
    }
    if(d[u] > d[v])
        std::swap(u, v);
    query(1, n, 1, id[u], id[v]);
    return res;
}
void apply(int n, int s, int t, Line line) {
    Int64 base = len[s];
    line.b += line.k * base;
    line.k = -line.k;
    while(top[s] != top[t]) {
        insert(1, n, 1, id[top[s]], id[s], line);
        s = p[top[s]];
    }
    insert(1, n, 1, id[t], id[s], line);
}
int main() {
    IO::init();
    int n = read();
    int m = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    build(1, n, 1);
    for(int i = 1; i <= m; ++i) {
        int op = read();
        int s = read();
        int t = read();
        if(op == 1) {
            Line line;
            line.k = read();
            line.b = read();
            int lca = getLCA(s, t);
            apply(n, s, lca, line);
            line.b += line.k *
                (len[s] + len[t] - 2 * len[lca]);
            line.k = -line.k;
            apply(n, t, lca, line);
        } else
            write(query(n, s, t));
    }
    IO::uninit();
    return 0;
}
