#include <cstdio>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 500005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link, cnt, nxt[26];
    } st[maxS];
    int siz, last;
    SAM() {
        siz = last = 1;
    }
    void extend(int c) {
        int id = ++siz;
        st[id].len = st[last].len + 1;
        st[id].cnt = 1;
        int p = last;
        while (p && !st[p].nxt[c]) {
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
                st[cq].cnt = 0;
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
} sam;
struct Edge {
    int to, next;
} E[maxS];
int last[maxS] = {}, cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u];
    last[u] = cnt;
}
Int64 res;
int dp[maxS];
void DFS(int u) {
    dp[u] = sam.st[u].cnt;
    Int64 k = 2 * sam.st[u].len;
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        DFS(v);
        res -= k * dp[u] * dp[v];
        dp[u] += dp[v];
    }
}
int main() {
    int c, n = 0;
    do
        c = getchar();
    while (c < 'a' || c > 'z');
    while ('a' <= c && c <= 'z') {
        sam.extend(c - 'a');
        ++n;
        c = getchar();
    }
    for (int i = 1; i <= sam.siz; ++i) {
        int p = sam.st[i].link;
        if (p) addEdge(p, i);
    }
    res = asInt64(n - 1) * n * (n + 1) / 2;
    DFS(1);
    printf("%lld\n", res);
    return 0;
}
