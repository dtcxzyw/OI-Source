//P3975
#include <cstdio>
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
    int cnt[size], q[maxS], dp[maxS];
    void pre(int t) {
        for (int i = 1; i <= siz; ++i) ++cnt[st[i].len];
        int n = st[last].len;
        for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
        for (int i = siz; i >= 1; --i) q[cnt[st[i].len]--] = i;
        if (t) {
            for (int i = siz; i >= 1; --i) {
                int u = q[i];
                st[st[u].link].cnt += st[u].cnt;
            }
            st[1].cnt = 1;
        } else
            for (int i = 1; i <= siz; ++i) st[i].cnt = 1;
        for (int i = siz; i >= 1; --i) {
            int u = q[i];
            dp[u] = st[u].cnt;
            for (int j = 0; j < 26; ++j)
                dp[u] += dp[st[u].nxt[j]];
        }
    }
    void query(int k) {
        if (dp[1] < k)
            puts("-1");
        else {
            int cur = 1;
            while (true) {
                if (k <= st[cur].cnt)
                    break;
                else {
                    k -= st[cur].cnt;
                    for (int j = 0; j < 26; ++j) {
                        int to = st[cur].nxt[j];
                        if (k <= dp[to]) {
                            cur = to;
                            putchar('a' + j);
                            break;
                        } else
                            k -= dp[to];
                    }
                }
            }
        }
    }
} sam;
char buf[size];
int main() {
    int t, k;
    scanf("%s%d%d", buf, &t, &k);
    for (int i = 0; buf[i]; ++i) sam.extend(buf[i] - 'a');
    sam.pre(t);
    sam.query(k + 1);
    return 0;
}
