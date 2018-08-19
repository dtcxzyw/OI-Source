#include <cstdio>
const int size = 100005, maxS = size * 2;
struct SAM {
    struct State {
        int len, link, cnt, id, nxt[26];
    } st[maxS];
    int siz, last;
    SAM() {
        siz = last = 1;
    }
    void extend(int c) {
        int id = ++siz;
        st[id].len = st[last].len + 1;
        int p = last;
        while(p && !st[p].nxt[c]) {
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
} sam;
char buf[size];
int end[size], ans[size];
int main() {
    int n, tot = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        int c;
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        sam.last = 1;
        while('a' <= c && c <= 'z') {
            int x = c - 'a';
            sam.extend(x);
            buf[++tot] = x;
            c = getchar();
        }
        end[i] = tot;
    }
    int cur = 1;
    for(int i = 1; i <= n; ++i)
        for(int u = 1; cur <= end[i]; ++cur) {
            u = sam.st[u].nxt[buf[cur]];
            int v = u;
            while(v && sam.st[v].id != i) {
                sam.st[v].id = i;
                ++sam.st[v].cnt;
                v = sam.st[v].link;
            }
        }
    cur = 1;
    for(int i = 1; i <= n; ++i) {
        int id = i + n;
        for(int u = 1; cur <= end[i]; ++cur) {
            u = sam.st[u].nxt[buf[cur]];
            int v = u;
            while(v && sam.st[v].id != id) {
                sam.st[v].id = id;
                if(sam.st[v].cnt == 1)
                    ans[i] +=
                        sam.st[v].len - sam.st[sam.st[v].link].len;
                v = sam.st[v].link;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
