#include <algorithm>
#include <cstdio>
#include <map>
namespace IO {
    char in[1 << 22];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 20], *S = out;
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
void print(int x) {
    if(x >= 10)
        print(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 200005;
int minv[size << 2], mex[size];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
const int inf = 1 << 30;
void build(int l, int r, int id) {
    if(l == r)
        minv[id] = mex[l];
    else {
        int m = (l + r) >> 1;
        minv[id] = inf;
        build(ls);
        build(rs);
    }
}
void color(int l, int r, int id, int nl, int nr,
           int val) {
    if(nl <= l && r <= nr)
        minv[id] = std::min(minv[id], val);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            color(ls, nl, nr, val);
        if(m < nr)
            color(rs, nl, nr, val);
    }
}
int query(int l, int r, int id, int p) {
    int res = minv[id];
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            res = std::min(res, query(ls, p));
        else
            res = std::min(res, query(rs, p));
    }
    return res;
}
int A[size], nxt[size];
struct Query {
    int l, r, id;
    bool operator<(const Query& rhs) const {
        return l < rhs.l;
    }
} Q[size];
bool flag[size];
int ans[size];
int main() {
    IO::init();
    int n = read();
    int m = read();
    int cur = 0;
    for(int i = 1; i <= n; ++i) {
        A[i] = read();
        if(A[i] <= n)
            flag[A[i]] = true;
        while(flag[cur])
            ++cur;
        mex[i] = cur;
    }
    build(1, n, 1);
    std::map<int, int> last;
    for(int i = n; i >= 1; --i) {
        int& p = last[A[i]];
        nxt[i] = (p ? p : n + 1);
        p = i;
    }
    for(int i = 1; i <= m; ++i) {
        Q[i].l = read();
        Q[i].r = read();
        Q[i].id = i;
    }
    std::sort(Q + 1, Q + m + 1);
    for(int i = 1, j = 1; i <= n; ++i) {
        while(j <= m && Q[j].l == i) {
            ans[Q[j].id] = query(1, n, 1, Q[j].r);
            ++j;
        }
        color(1, n, 1, i, nxt[i] - 1, A[i]);
    }
    for(int i = 1; i <= m; ++i) {
        print(ans[i]);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
