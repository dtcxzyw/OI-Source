#include <algorithm>
#include <cstdio>
#include <map>
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
const int size = 20005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link, cnt;
        std::map<int, int> nxt;
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
        while(p && !st[p].nxt.count(c)) {
            st[p].nxt[c] = id;
            p = st[p].link;
        }
        if(p) {
            int q = st[p].nxt[c];
            if(st[p].len + 1 == st[q].len)
                st[id].link = q;
            else {
                int cq = ++siz;
                st[cq] = st[q];
                st[cq].len = st[p].len + 1;
                st[cq].cnt = 0;
                while(p && st[p].nxt[c] == q) {
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
        for(int i = 1; i <= siz; ++i)
            ++cnt[st[i].len];
        int n = st[last].len;
        for(int i = 1; i <= n; ++i)
            cnt[i] += cnt[i - 1];
        for(int i = siz; i >= 1; --i)
            q[cnt[st[i].len]--] = i;
        for(int i = siz; i >= 1; --i) {
            int u = q[i];
            st[st[u].link].cnt += st[u].cnt;
        }
        st[1].cnt = 1;
    }
    int solve(int k) {
        pre();
        int res = 0;
        for(int i = 1; i <= siz; ++i)
            if(st[i].cnt >= k)
                res = std::max(res, st[i].len);
        return res;
    }
} sam;
int main() {
    int n = read();
    int k = read();
    while(n--)
        sam.extend(read());
    printf("%d\n", sam.solve(k));
    return 0;
}
