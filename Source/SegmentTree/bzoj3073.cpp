#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
namespace IO {
    const int size = 1 << 22;
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
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
void write(int val) {
    if(val >= 10)
        write(val / 10);
    IO::putc('0' + val % 10);
}
const int size = 500005, maxS = size << 2,
          maxv = maxS * 2;
struct Edge {
    int to, nxt;
} E[size * 85];
int last[maxv], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v << 1 | w, E[cnt].nxt = last[u];
    last[u] = cnt;
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
int lid[size], iid[maxS], oid[maxS], pcnt = 0;
void build(int l, int r, int id) {
    if(l == r)
        lid[l] = iid[id] = oid[id] = ++pcnt;
    else {
        iid[id] = ++pcnt;
        oid[id] = ++pcnt;
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        addEdge(iid[id], iid[id << 1], 0);
        addEdge(iid[id], iid[id << 1 | 1], 0);
        addEdge(oid[id << 1], oid[id], 0);
        addEdge(oid[id << 1 | 1], oid[id], 0);
    }
}
std::pair<int, int> A[2][100], *ptr;
void scan(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        *(ptr++) = std::make_pair(iid[id], oid[id]);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            scan(ls, nl, nr);
        if(m < nr)
            scan(rs, nl, nr);
    }
}
int dis[maxv], q[maxv];
bool flag[maxv];
void SSSP(int s) {
    memset(dis + 1, 0x3f, sizeof(int) * pcnt);
    int b = 0, e = 1;
    q[0] = s, dis[s] = 0;
    while(b != e) {
        int u = q[b++];
        if(b == maxv)
            b = 0;
        if(flag[u])
            continue;
        flag[u] = true;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to >> 1, w = E[i].to & 1;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if(w) {
                    q[e++] = v;
                    if(e == maxv)
                        e = 0;
                } else {
                    if(--b == -1)
                        b = maxv - 1;
                    q[b] = v;
                }
            }
        }
    }
}
int main() {
    IO::init();
    int n = read();
    int m = read();
    int p = read();
    build(1, n, 1);
    for(int i = 1; i <= m; ++i) {
        int a = read();
        int b = read();
        ptr = A[0];
        scan(1, n, 1, a, b);
        int sizA = ptr - A[0];
        int c = read();
        int d = read();
        ptr = A[1];
        scan(1, n, 1, c, d);
        int sizB = ptr - A[1];
        for(int j = 0; j < sizA; ++j) {
            int iu = A[0][j].first,
                ou = A[0][j].second;
            for(int k = 0; k < sizB; ++k) {
                int iv = A[1][k].first;
                int ov = A[1][k].second;
                addEdge(ou, iv, 1);
                addEdge(ov, iu, 1);
            }
        }
    }
    SSSP(lid[p]);
    for(int i = 1; i <= n; ++i) {
        write(dis[lid[i]]);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
