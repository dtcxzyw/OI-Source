#include <cstdio>
namespace IO {
    const int size = 1 << 22;
    char in[size];
    void init() {
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
int iabs(int x) {
    return x >= 0 ? x : -x;
}
int getOp() {
    int c;
    do
        c = IO::getc();
    while(c != 'i' && c != 'u');
    return c;
}
const int size = 100005;
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int p[size], son[size], siz[size], d[size];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        d[v] = d[u] + 1;
        buildTree(v);
        siz[u] += siz[v];
        if(siz[son[u]] < siz[v])
            son[u] = v;
    }
}
int id[size], top[size], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
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
int sum[size << 2], tag[size << 2];
void color(int l, int r, int id, int col) {
    sum[id] = (col ? r - l + 1 : 0);
    tag[id] = col + 1;
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void push(int l, int r, int id) {
    if(tag[id]) {
        int m = (l + r) >> 1, col = tag[id] - 1;
        color(ls, col);
        color(rs, col);
        tag[id] = 0;
    }
}
void modify(int l, int r, int id, int nl, int nr,
            int col) {
    if(sum[id] == (col ? r - l + 1 : 0))
        return;
    if(nl <= l && r <= nr)
        color(l, r, id, col);
    else {
        push(l, r, id);
        int m = (l + r) >> 1;
        if(nl <= m)
            modify(ls, nl, nr, col);
        if(m < nr)
            modify(rs, nl, nr, col);
        sum[id] = sum[id << 1] + sum[id << 1 | 1];
    }
}
int query(int l, int r, int id, int x) {
    if(sum[id] == 0)
        return 0;
    if(sum[id] == r - l + 1)
        return 1;
    push(l, r, id);
    int m = (l + r) >> 1;
    return x <= m ? query(ls, x) : query(rs, x);
}
int main() {
    IO::init();
    int n = read();
    for(int i = 2; i <= n; ++i) {
        p[i] = read() + 1;
        addEdge(p[i], i);
    }
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    int q = read();
    for(int i = 1; i <= q; ++i) {
        int op = getOp();
        int x = read() + 1;
        int old = sum[1];
        if(op == 'i') {
            if(!query(1, n, 1, id[x]))
                while(x) {
                    modify(1, n, 1, id[top[x]], id[x],
                           1);
                    x = p[top[x]];
                }
        } else
            modify(1, n, 1, id[x], id[x] + siz[x] - 1,
                   0);
        write(iabs(sum[1] - old));
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
