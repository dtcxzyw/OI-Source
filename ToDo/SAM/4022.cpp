#include <algorithm>
#include <cstdio>
const int size = 1100005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link, nxt[2];
    } st[maxS];
    int siz;
    SAM() {
        siz = 1;
    }
    int extend(int c, int last) {
        int id = ++siz;
        st[id].len = st[last].len + 1;
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
                while (p && st[p].nxt[c] == q) {
                    st[p].nxt[c] = cq;
                    p = st[p].link;
                }
                st[q].link = st[id].link = cq;
            }
        } else
            st[id].link = 1;
        return id;
    }
} sam;
char buf[size];
int ch[size][2] = {}, icnt = 0;
void buildSAM(int u, int c, int p) {
    if (u) {
        int id = sam.extend(c, p);
        buildSAM(ch[u][0], 0, id);
        buildSAM(ch[u][1], 1, id);
    }
}
int len[size], dp[size], q[size];
bool check(int siz, int l) {
    int b = 0, e = 0;
    dp[0] = 0;
    for (int i = 1; i <= siz; ++i) {
        dp[i] = dp[i - 1];
        if (i >= l) {
            int off = i - l;
            while (b < e && dp[q[e - 1]] - q[e - 1] <= dp[off] - off) --e;
            q[e++] = off;
            int minp = i - len[i - 1];
            while (b < e && q[b] < minp) ++b;
            if (b < e) dp[i] = std::max(dp[i], dp[q[b]] + i - q[b]);
        }
    }
    return dp[siz] * 10 >= siz * 9;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%s", buf);
        int p = 0;
        for (int i = 0; buf[i]; ++i) {
            int &u = ch[p][buf[i] - '0'];
            if (u == 0) u = ++icnt;
            p = u;
        }
    }
    buildSAM(ch[0][0], 0, 1);
    buildSAM(ch[0][1], 1, 1);
    while (n--) {
        scanf("%s", buf);
        int i, cur = 1, cnt = 0;
        for (i = 0; buf[i]; ++i) {
            int c = buf[i] - '0';
            if (sam.st[cur].nxt[c])
                ++cnt, cur = sam.st[cur].nxt[c];
            else {
                while (cur && !sam.st[cur].nxt[c]) cur = sam.st[cur].link;
                if (cur) {
                    cnt = sam.st[cur].len + 1;
                    cur = sam.st[cur].nxt[c];
                } else
                    cur = 1, cnt = 0;
            }
            len[i] = cnt;
        }
        int siz = i;
        int l = 1, r = siz, ans = 0;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (check(siz, m))
                ans = m, l = m + 1;
            else
                r = m - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
