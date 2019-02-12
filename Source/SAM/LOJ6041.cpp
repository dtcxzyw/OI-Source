#include <algorithm>
#include <cstdio>
const int size = 100005, maxS = size * 2;
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
struct SAM {
    struct Node {
        int c[2], len, link;
    } T[maxS];
    int siz, last;
    SAM() : siz(1), last(1) {}
    int extend(int ch) {
        int id = ++siz;
        T[id].len = T[last].len + 1;
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
} sam;
namespace SegTree {
    int maxv[size << 2], off;
    void init(int n) {
        off = 1;
        while(off - 2 < n)
            off <<= 1;
    }
    void modify(int p, int val) {
        p += off;
        while(p) {
            maxv[p] = std::max(maxv[p], val);
            p >>= 1;
        }
    }
    int query(int l, int r) {
        int res = 0;
        for(l += off - 1, r += off + 1; l ^ r ^ 1;
            l >>= 1, r >>= 1) {
            if(~l & 1)
                res = std::max(res, maxv[l ^ 1]);
            if(r & 1)
                res = std::max(res, maxv[r ^ 1]);
        }
        return res;
    }
}  // namespace SegTree
namespace LCT {
    struct Node {
        int c[2], p, tag, val;
    } T[maxS];
    int isRoot(int u) {
        int p = T[u].p;
        return T[p].c[0] != u && T[p].c[1] != u;
    }
    int getPos(int u) {
        int p = T[u].p;
        return T[p].c[1] == u;
    }
    void connect(int u, int p, int c) {
        T[u].p = p;
        T[p].c[c] = u;
    }
#define ls T[u].c[0]
#define rs T[u].c[1]
    void pushDown(int u) {
        if(T[u].tag) {
            T[ls].val = T[ls].tag = T[u].tag;
            T[rs].val = T[rs].tag = T[u].tag;
            T[u].tag = 0;
        }
    }
    void rotate(int u) {
        int ku = getPos(u);
        int p = T[u].p;
        int kp = getPos(p);
        int pp = T[p].p;
        int t = T[u].c[ku ^ 1];
        T[u].p = pp;
        if(!isRoot(p))
            T[pp].c[kp] = u;
        connect(p, u, ku ^ 1);
        connect(t, p, ku);
    }
    void push(int u) {
        if(!isRoot(u))
            push(T[u].p);
        pushDown(u);
    }
    void splay(int u) {
        push(u);
        while(!isRoot(u)) {
            int p = T[u].p;
            if(!isRoot(p))
                rotate(getPos(u) == getPos(p) ? p : u);
            rotate(u);
        }
    }
    void access(int u) {
        int v = 0;
        do {
            splay(u);
            if(T[u].val)
                SegTree::modify(T[u].val,
                                sam.T[u].len);
            rs = v;
            v = u;
            u = T[u].p;
        } while(u);
    }
#undef ls
#undef rs
}  // namespace LCT
struct Query {
    int l, r, id;
    bool operator<(const Query& rhs) const {
        return r < rhs.r;
    }
} Q[size];
int ans[size], pos[size];
int main() {
    int n = read();
    int m = read();
    int c, cnt = 0;
    do
        c = getchar();
    while(c < '0' || c > '1');
    while('0' <= c && c <= '1') {
        pos[++cnt] = sam.extend(c - '0');
        c = getchar();
    }
    for(int i = 1; i <= sam.siz; ++i)
        LCT::T[i].p = sam.T[i].link;
    for(int i = 1; i <= m; ++i) {
        Q[i].l = read();
        Q[i].r = read();
        Q[i].id = i;
    }
    std::sort(Q + 1, Q + m + 1);
    SegTree::init(n);
    for(int i = 1, qp = 1; i <= n && qp <= m; ++i) {
        int cp = pos[i];
        LCT::access(cp);
        while(qp <= m && Q[qp].r == i) {
            ans[Q[qp].id] =
                SegTree::query(Q[qp].l, Q[qp].r);
            ++qp;
        }
        LCT::splay(cp);
        LCT::Node& np = LCT::T[cp];
        np.tag = np.val = i;
    }
    for(int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
