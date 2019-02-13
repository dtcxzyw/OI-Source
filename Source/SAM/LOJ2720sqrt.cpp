#include <cstdio>
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
int maxi(int a, int b) {
    return a > b ? a : b;
}
int mini(int a, int b) {
    return a < b ? a : b;
}
const int size = 1500005, maxS = size * 2;
struct Node {
    int l, r;
} T[maxS / 3 * 40];
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
int query(int l, int r, int id, int nr) {
    if(id == 0)
        return 0;
    if(l == r)
        return l;
    int m = (l + r) >> 1;
    if(nr <= m)
        return query(l, m, T[id].l, nr);
    int ans = query(m + 1, r, T[id].r, nr);
    return ans ? ans : query(l, m, T[id].l, nr);
}
typedef long long Int64;
struct SAM {
    struct Node {
        int c[26], len, link, lid, rt, lp, rp;
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
    int pos[size], d[size], q[maxS];
    void buildRight(int n) {
        for(int i = 1; i <= n; ++i) {
            int id = pos[i];
            T[id].rt = insert(1, n, i);
            T[id].lp = T[id].rp = i;
        }
        for(int i = 1; i <= siz; ++i)
            ++d[T[i].len];
        for(int i = 1; i <= n; ++i)
            d[i] += d[i - 1];
        for(int i = 1; i <= siz; ++i)
            q[d[T[i].len]--] = i;
        for(int i = siz; i >= 1; --i) {
            int id = q[i];
            int p = T[id].link;
            T[p].rt = merge(T[p].rt, T[id].rt);
            T[p].lp = mini(T[p].lp, T[id].lp);
            T[p].rp = maxi(T[p].rp, T[id].rp);
        }
    }
    void calc(int p, int id, int l, int r, bool full,
              int n, Int64& res) {
        while(p != 1) {
            if(T[p].lid == id)
                break;
            T[p].lid = id;
            res += T[p].len - T[T[p].link].len;
            if(T[p].rt) {
                if(full) {
                    res -= T[p].len - T[T[p].link].len;
                    break;
                } else if(l <= T[p].rp &&
                          r >= T[p].lp) {
                    int maxr = T[p].rp <= r ?
                        T[p].rp :
                        query(1, n, T[p].rt, r);
                    int len =
                        mini(T[p].len, maxr - l + 1);
                    if(len > T[T[p].link].len)
                        res -= len - T[T[p].link].len;
                    if(len == T[p].len)
                        break;
                }
            }
            p = T[p].link;
        }
    }
} sam;
char buf[size];
int main() {
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    int c, cnt = 0;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        sam.pos[++cnt] = sam.extend(c - 'a');
        c = getchar();
    }
    sam.buildRight(cnt);
    int n = read();
    for(int i = 1; i <= n; ++i) {
        int len = 0;
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        while('a' <= c && c <= 'z') {
            buf[++len] = c;
            c = getchar();
        }
        int l = read();
        int r = read();
        bool full = (l == 1 && r == cnt);
        Int64 res = 0;
        sam.last = 1;
        for(int j = 1; j <= len; ++j)
            sam.pos[j] = sam.extend(buf[j] - 'a');
        for(int j = 1; j <= len; ++j)
            sam.calc(sam.pos[j], i, l, r, full, cnt,
                     res);
        printf("%lld\n", res);
    }
    return 0;
}
