#include <cstdio>
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
const int size = 100005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link;
        std::map<int, int> nxt;
    } st[maxS];
    int siz, last;
    SAM() {
        siz = last = 1;
    }
    int extend(int c) {
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
        return st[id].len - st[st[id].link].len;
    }
} sam;
int main() {
    int n = read();
    long long ans = 0;
    while (n--) {
        ans += sam.extend(read());
        printf("%lld\n", ans);
    }
    return 0;
}
