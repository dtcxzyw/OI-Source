#include <algorithm>
#include <cstdio>
namespace IO {
    const int bsiz = 1 << 23;
    char in[bsiz], *ip = in;
    void init() {
        fread(in, bsiz, 1, stdin);
    }
    char getchar() {
        return *(ip++);
    }
    char out[bsiz], *op = out;
    void putchar(char ch) {
        *(op++) = ch;
    }
    void flush() {
        fwrite(out, op - out, 1, stdout);
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getchar();
    }
    return res;
}
void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putchar('0' + x % 10);
}
const int size = 100005, maxd = 16;
struct Node {
    int ch[2], siz;
} T[size * 20];
int icnt = 0, root[size];
void insert(int* src, int val) {
    for(int d = maxd; d >= -1; --d) {
        int id = ++icnt;
        T[id] = T[*src];
        ++T[id].siz;
        *src = id;
        if(d >= 0)
            src = &T[id].ch[(val >> d) & 1];
    }
}
int query(int b, int e, int val) {
    int res = 0;
    for(int d = maxd; d >= 0; --d) {
        int c = (val >> d) & 1, nc = c ^ 1;
        int dsiz =
            T[T[e].ch[nc]].siz - T[T[b].ch[nc]].siz;
        if(dsiz) {
            b = T[b].ch[nc], e = T[e].ch[nc];
            res |= 1 << d;
        } else
            b = T[b].ch[c], e = T[e].ch[c];
    }
    return res;
}
struct Operator {
    int op, l, r, id, v, b, e;
    // op=0:id,v,e
    // op=1:l,r,id,v,b,e
} Op[size];
int ans[size], q[size], sid[size];
bool cmp(int a, int b) {
    return Op[a].id < Op[b].id;
}
void solve(int l, int r, int b, int e) {
    if(l > r)
        return;
    icnt = 0;
    int qcnt = 0;
    for(int i = l; i <= r; ++i)
        if(Op[i].op == 0 && b <= Op[i].e &&
           Op[i].e <= e)
            q[qcnt++] = i;
    if(qcnt == 0)
        return;
    std::sort(q, q + qcnt, cmp);
    int scnt = 0;
    for(int i = 0; i < qcnt; ++i) {
        int cop = q[i];
        if(sid[scnt] != Op[cop].id) {
            sid[++scnt] = Op[cop].id;
            root[scnt] = root[scnt - 1];
        }
        insert(&root[scnt], Op[cop].v);
    }
    for(int i = l; i <= r; ++i)
        if(Op[i].op == 1 && Op[i].b <= b &&
           e <= Op[i].e) {
            int lp = std::lower_bound(sid + 1,
                                      sid + scnt + 1,
                                      Op[i].l) -
                sid - 1;
            int rp = std::upper_bound(sid + 1,
                                      sid + scnt + 1,
                                      Op[i].r) -
                sid - 1;
            int& res = ans[Op[i].id];
            res =
                std::max(res, query(root[lp], root[rp],
                                    Op[i].v));
        }
    if(b != e) {
        int m = (b + e) >> 1, cpos = l;
        for(int i = l; i <= r; ++i)
            if(Op[i].b <= m &&
               !(Op[i].b <= b && e <= Op[i].e))
                std::swap(Op[i], Op[cpos++]);
        solve(l, cpos - 1, b, m);
        cpos = l;
        for(int i = l; i <= r; ++i)
            if(m < Op[i].e &&
               !(Op[i].b <= b && e <= Op[i].e))
                std::swap(Op[i], Op[cpos++]);
        solve(l, cpos - 1, m + 1, e);
    }
}
int main() {
    IO::init();
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        root[i] = root[i - 1];
        insert(&root[i], read());
    }
    int d = 1, qid = 0;
    for(int i = 1; i <= m; ++i) {
        int op = read();
        if(op) {
            Op[i].op = 1;
            Op[i].l = read();
            Op[i].r = read();
            Op[i].id = ++qid;
            Op[i].v = read();
            ans[qid] = query(root[Op[i].l - 1],
                             root[Op[i].r], Op[i].v);
            Op[i].b = d - read() + 1;
        } else {
            if(i != 1)
                ++d;
            Op[i].op = 0;
            Op[i].id = read();
            Op[i].v = read();
            Op[i].b = d;
        }
        Op[i].e = d;
    }
    solve(1, m, 1, d);
    for(int i = 1; i <= qid; ++i) {
        write(ans[i]);
        IO::putchar('\n');
    }
    IO::flush();
    return 0;
}
