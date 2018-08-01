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
const int size = 300005, maxS = size * 4;
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
                st[cq].link = st[q].link;
                st[cq].len = st[p].len + 1;
                st[cq].nxt = st[q].nxt;
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
    void solve(int n) {
        int u = 1;
        while (n--) {
            std::map<int, int>::iterator it = st[u].nxt.begin();
            u = it->second;
            printf("%d ", it->first);
        }
    }
} sam;
int A[size];
int main() {
    int n = read();
    for (int i = 0; i < n; ++i) A[i] = read();
    for (int k = 0; k < 2; ++k)
        for (int i = 0; i < n; ++i)
            sam.extend(A[i]);
    sam.solve(n);
    return 0;
}
