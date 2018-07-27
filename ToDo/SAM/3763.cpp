#include <cstdio>
#include <cstring>
const int size = 100005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link, cnt, nxt[4];
    } st[maxS];
    int siz, last;
    void reset() {
        siz = last = 1;
        memset(st, 0, sizeof(st));
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
    int cnt[size], q[maxS];
    void pre() {
        memset(cnt, 0, sizeof(int) * (siz + 1));
        for (int i = 1; i <= siz; ++i) ++cnt[st[i].len];
        int n = st[last].len;
        for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
        for (int i = siz; i >= 1; --i) q[cnt[st[i].len]--] = i;
        for (int i = siz; i >= 1; --i) {
            int u = q[i];
            st[st[u].link].cnt += st[u].cnt;
        }
    }
} sam;
char buf[size];
int remap[128], end, ans;
void DFS(int u, int len, int c) {
    if (c > 3) return;
    if (len == end)
        ans += sam.st[u].cnt;
    else {
        int ch = buf[len];
        ++len;
        for (int i = 0; i < 4; ++i) {
            int v = sam.st[u].nxt[i];
            if (v) DFS(v, len, c + (ch != i));
        }
    }
}
int main() {
    remap['A'] = 0;
    remap['T'] = 1;
    remap['C'] = 2;
    remap['G'] = 3;
    int t;
    scanf("%d", &t);
    while (t--) {
        sam.reset();
        scanf("%s", buf);
        for (int i = 0; buf[i]; ++i) sam.extend(remap[buf[i]]);
        sam.pre();
        scanf("%s", buf);
        for (end = 0; buf[end]; ++end) buf[end] = remap[buf[end]];
        ans = 0;
        DFS(1, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
