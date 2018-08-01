#include <cstdio>
const int size = 200005, maxS = size * 2;
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
    int cnt[size], q[maxS];
    void pre() {
        for (int i = 1; i <= siz; ++i) ++cnt[st[i].len];
        int n = st[last].len;
        for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
        for (int i = siz; i >= 1; --i) q[cnt[st[i].len]--] = i;
        for (int i = siz; i >= 1; --i) {
            int u = q[i];
            st[st[u].link].cnt += st[u].cnt;
        }
        st[1].cnt = 1;
    }
} s1, s2;
char buf[size];
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
Int64 DFS(int u1, int u2) {
    Int64 res = asInt64(s1.st[u1].cnt) * s2.st[u2].cnt;
    for (int i = 0; i < 26; ++i) {
        int v1 = s1.st[u1].nxt[i], v2 = s2.st[u2].nxt[i];
        if (v1 && v2)
            res += DFS(v1, v2);
    }
    return res;
}
int main() {
    scanf("%s", buf);
    for (int i = 0; buf[i]; ++i) s1.extend(buf[i] - 'a');
    s1.pre();
    scanf("%s", buf);
    for (int i = 0; buf[i]; ++i) s2.extend(buf[i] - 'a');
    s2.pre();
    printf("%lld\n", DFS(1, 1) - 1);
    return 0;
}
