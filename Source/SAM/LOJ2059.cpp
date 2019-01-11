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
const int size = 100005, maxS = size * 2;
struct SAM {
    struct Node {
        int len, link, nxt[26];
    } T[maxS];
    int last, siz;
    SAM() : last(1), siz(1) {}
    int extend(int ch) {
        int p = last, id = ++siz;
        T[id].len = T[last].len + 1;
        while(p && !T[p].nxt[ch]) {
            T[p].nxt[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].nxt[ch];
            if(T[q].len == T[p].len + 1)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                while(p && T[p].nxt[ch] == q) {
                    T[p].nxt[ch] = cq;
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
struct Node {
    int ls, rs;
} T[maxS * 20];
int icnt = 0;
int build(int l, int r, int pos) {
    int id = ++icnt;
    if(l != r) {
        int m = (l + r) >> 1;
        if(pos <= m)
            T[id].ls = build(l, m, pos);
        else
            T[id].rs = build(m + 1, r, pos);
    }
    return id;
}
int merge(int u, int v) {
    if(u && v) {
        int id = ++icnt;
        T[id].ls = merge(T[u].ls, T[v].ls);
        T[id].rs = merge(T[u].rs, T[v].rs);
        return id;
    }
    return u | v;
}
bool find(int l, int r, int id, int nl, int nr) {
    if(id == 0)
        return false;
    if(nl <= l && r <= nr)
        return true;
    int m = (l + r) >> 1;
    if(nl <= m && find(l, m, T[id].ls, nl, nr))
        return true;
    if(m < nr && find(m + 1, r, T[id].rs, nl, nr))
        return true;
    return false;
}
int n, p[20][maxS], pos[size], root[maxS], q[maxS],
    cnt[size];
void build() {
    for(int i = 1; i <= sam.siz; ++i)
        ++cnt[sam.T[i].len];
    for(int i = 1; i <= n; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = 1; i <= sam.siz; ++i)
        q[cnt[sam.T[i].len]--] = i;
    for(int i = 1; i <= n; ++i)
        root[pos[i]] = build(1, n, i);
    for(int i = sam.siz; i >= 1; --i) {
        int u = q[i], fa = sam.T[u].link;
        root[fa] = merge(root[fa], root[u]);
    }
    for(int i = 1; i <= sam.siz; ++i)
        p[0][i] = sam.T[i].link;
    for(int i = 1; i < 20; ++i)
        for(int j = 1; j <= sam.siz; ++j)
            p[i][j] = p[i - 1][p[i - 1][j]];
}
bool check(int len, int l, int r, int u) {
    for(int i = 19; i >= 0; --i)
        if(sam.T[p[i][u]].len >= len)
            u = p[i][u];
    return find(1, n, root[u], l, r);
}
char buf[size];
int mini(int a, int b) {
    return a < b ? a : b;
}
int main() {
    n = read();
    int m = read();
    for(int i = 1; i <= n; ++i)
        buf[i] = getchar();
    int rev = n + 1;
    for(int i = n; i >= 1; --i)
        pos[rev - i] = sam.extend(buf[i] - 'a');
    build();
    while(m--) {
        int b = rev - read();
        int a = rev - read();
        int d = rev - read();
        int c = rev - read();
        int l = 1, r = mini(b - a, d - c) + 1, ans = 0;
        while(l <= r) {
            int m = (l + r) >> 1;
            if(check(m, a + m - 1, b, pos[d]))
                ans = m, l = m + 1;
            else
                r = m - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
