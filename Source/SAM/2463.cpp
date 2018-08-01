#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 1005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link;
        std::map<int, int> nxt;
    } st[maxS];
    int siz, last;
    SAM() {
        siz = last = 1;
    }
    void extend(int c) {
        int id = ++siz;
        st[id].len = st[last].len + 1;
        int p = last;
        while (p && !st[p].nxt.count(c)) {
            st[p].nxt[c] = id;
            p = st[p].link;
        }
        if (p) {
            int q = st[p].nxt[c];
            if (st[p].len + 1 == st[q].len)
                st[id].link = q;
            else {
                int cq = ++siz;
                st[cq] = st[q];
                st[cq].len = st[p].len + 1;
                while (p && st[p].nxt[c] == q) {
                    st[p].nxt[c] = cq;
                    p = st[p].link;
                }
                st[q].link = st[id].link = cq;
            }
        } else
            st[id].link = 1;
        last = id;
    }
    int cnt[size], q[maxS];
    void pre() {
        for (int i = 1; i <= siz; ++i) ++cnt[st[i].len];
        int n = st[last].len;
        for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
        for (int i = siz; i >= 1; --i) q[cnt[st[i].len]--] = i;
    }
} sam;
int maxl[maxS] = {}, minl[maxS];
int main() {
    int n = read();
    memset(minl, 0x3f, sizeof(minl));
    {
        int m = read();
        int last = read();
        while (--m) {
            int val = read();
            sam.extend(val - last);
            last = val;
        }
    }
    sam.pre();
    while (--n) {
        int m = read();
        int last = read(), p = 1, len = 0;
        memset(maxl + 1, 0, sizeof(int) * sam.siz);
        while (--m) {
            int val = read();
            int c = val - last;
            if (sam.st[p].nxt.count(c))
                p = sam.st[p].nxt[c], ++len;
            else {
                while (p && !sam.st[p].nxt.count(c)) p = sam.st[p].link;
                if (p) {
                    len = sam.st[p].len + 1;
                    p = sam.st[p].nxt[c];
                } else
                    p = 1, len = 0;
            }
            maxl[p] = std::max(maxl[p], len);
            last = val;
        }
        for (int i = sam.siz; i >= 1; --i) {
            int u = sam.q[i];
            minl[u] = std::min(minl[u], maxl[u]);
            int fu = sam.st[u].link;
            maxl[fu] = std::max(maxl[fu], std::min(maxl[u], sam.st[fu].len));
        }
    }
    int res = 0;
    for (int i = 1; i <= sam.siz; ++i)
        res = std::max(res, minl[i]);
    printf("%d\n", res + 1);
    return 0;
}
