#include <algorithm>
#include <cstdio>
const int size = 500005;
struct SAM {
    struct State {
        int nxt[26], link, len, right;
    } S[size];
    int siz, last;
    SAM() : siz(1), last(1) {}
    void extend(int c) {
        int id = ++siz;
        S[id].len = S[last].len + 1;
        S[id].right = 1;
        int p = last;
        while(p && !S[p].nxt[c]) {
            S[p].nxt[c] = id;
            p = S[p].link;
        }
        if(p) {
            int q = S[p].nxt[c];
            if(S[p].len + 1 == S[q].len)
                S[id].link = q;
            else {
                int cq = ++siz;
                S[cq] = S[q];
                S[cq].len = S[p].len + 1;
                S[cq].right = 0;
                while(p && S[p].nxt[c] == q) {
                    S[p].nxt[c] = cq;
                    p = S[p].link;
                }
                S[q].link = S[id].link = cq;
            }
        } else
            S[id].link = 1;
        last = id;
    }
    int in[size], q[size], ans[size / 2];
    void solve() {
        for(int i = 1; i <= siz; ++i)
            ++in[S[i].link];
        int qsiz = 0;
        for(int i = 1; i <= siz; ++i)
            if(!in[i])
                q[++qsiz] = i;
        for(int i = 1; i <= qsiz; ++i) {
            int u = q[i];
            if(--in[S[u].link] == 0)
                q[++qsiz] = S[u].link;
        }
        for(int i = 1; i <= qsiz; ++i) {
            int u = q[i];
            ans[S[u].len] =
                std::max(ans[S[u].len], S[u].right);
            S[S[u].link].right += S[u].right;
        }
        int n = S[last].len;
        for(int i = n; i >= 2; --i)
            ans[i - 1] = std::max(ans[i - 1], ans[i]);
        for(int i = 1; i <= n; ++i)
            printf("%d\n", ans[i]);
    }
} sam;
int main() {
    int c;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        sam.extend(c - 'a');
        c = getchar();
    }
    sam.solve();
    return 0;
}
