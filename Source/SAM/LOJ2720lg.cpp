#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int mini(int a, int b) {
    return a < b ? a : b;
}
const int size = 500005, maxS = size * 2;
typedef long long Int64;
namespace SegTree {
    struct Node {
        int l, r;
    } T[maxS * 40];
    int tcnt = 0;
    int insert(int l, int r, int p) {
        int id = ++tcnt;
        if(l != r) {
            int m = (l + r) >> 1;
            if(p <= m)
                T[id].l = insert(l, m, p);
            else
                T[id].r = insert(m + 1, r, p);
        }
        return id;
    }
    int merge(int u, int v) {
        if(u && v) {
            int id = ++tcnt;
            T[id].l = merge(T[u].l, T[v].l);
            T[id].r = merge(T[u].r, T[v].r);
            return id;
        }
        return u | v;
    }
    bool query(int l, int r, int id, int nl, int nr) {
        if(id == 0)
            return false;
        if(nl <= l && r <= nr)
            return true;
        int m = (l + r) >> 1;
        return (nl <= m &&
                query(l, m, T[id].l, nl, nr)) ||
            (m < nr &&
             query(m + 1, r, T[id].r, nl, nr));
    }
}  // namespace SegTree
struct SAM {
    struct Node {
        int c[26], len, link, pos;
    } T[maxS];
    int siz, last;
    SAM() : siz(1), last(1) {}
    void reset() {
        memset(T + 1, 0, sizeof(Node) * siz);
        siz = last = 1;
    }
    int extend(int ch, int pos = 0) {
        int id = ++siz;
        T[id].len = T[last].len + 1;
        T[id].pos = pos;
        int p = last;
        while(p && !T[p].c[ch]) {
            T[p].c[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].c[ch];
            if(T[p].len + 1 == T[q].len)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                while(p && T[p].c[ch] == q) {
                    T[p].c[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        last = id;
        return id;
    }
} S, T;
int pos[size], root[maxS], d[size], q[maxS];
void buildRight(int n) {
    for(int i = 1; i <= n; ++i)
        root[pos[i]] = SegTree::insert(1, n, i);
    for(int i = 1; i <= S.siz; ++i)
        ++d[S.T[i].len];
    for(int i = 1; i <= n; ++i)
        d[i] += d[i - 1];
    for(int i = 1; i <= S.siz; ++i)
        q[d[S.T[i].len]--] = i;
    for(int i = S.siz; i >= 1; --i) {
        int id = q[i];
        int p = S.T[id].link;
        root[p] = SegTree::merge(root[p], root[id]);
    }
}
char buf[size];
int mlen[size];
int main() {
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    int c, cnt = 0;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        pos[++cnt] = S.extend(c - 'a');
        c = getchar();
    }
    buildRight(cnt);
    int n = read();
    for(int i = 1; i <= n; ++i) {
        T.reset();
        int tlen = 0;
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        Int64 res = 0;
        while('a' <= c && c <= 'z') {
            int ch = c - 'a';
            buf[++tlen] = ch;
            int id = T.extend(ch, tlen);
            res += T.T[id].len - T.T[T.T[id].link].len;
            c = getchar();
        }
        int l = read();
        int r = read();
        bool full = (l == 1 && r == cnt);
        int p = 1, len = 0;
        for(int i = 1; i <= tlen; ++i) {
            int ch = buf[i];
            while(true) {
                int son = S.T[p].c[ch];
                if(son &&
                   (full ||
                    SegTree::query(1, cnt, root[son],
                                   l + len, r))) {
                    ++len;
                    p = son;
                    break;
                }
                if(len == 0)
                    break;
                --len;
                int np = S.T[p].link;
                if(len == S.T[np].len)
                    p = np;
            }
            mlen[i] = len;
        }
        for(int i = 1; i <= T.siz; ++i) {
            int p = T.T[i].link,
                len =
                    mini(T.T[i].len, mlen[T.T[i].pos]);
            if(len > T.T[p].len)
                res -= len - T.T[p].len;
        }
        printf("%lld\n", res);
    }
    return 0;
}
