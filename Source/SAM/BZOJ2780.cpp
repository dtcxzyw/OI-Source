#include <cstdio>
const int size = 100005;
struct SAM {
    struct Node {
        int ch[26], link, len, lid, cnt;
    } T[size * 2];
    int siz, last;
    SAM() : siz(1), last(1) {}
    void extend(int ch, int sid) {
        int id = ++siz;
        T[id].len = T[last].len + 1;
        int p = last;
        while(p && !T[p].ch[ch]) {
            T[p].ch[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].ch[ch];
            if(T[p].len + 1 == T[q].len)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                while(p && T[p].ch[ch] == q) {
                    T[p].ch[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        p = id;
        while(p && T[p].lid != sid) {
            T[p].lid = sid;
            ++T[p].cnt;
            p = T[p].link;
        }
        last = id;
    }
} sam;
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) {
        sam.last = 1;
        int c;
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        while('a' <= c && c <= 'z') {
            sam.extend(c - 'a', i);
            c = getchar();
        }
    }
    for(int i = 1; i <= q; ++i) {
        int c;
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        int p = 1;
        while('a' <= c && c <= 'z') {
            p = sam.T[p].ch[c - 'a'];
            c = getchar();
        }
        printf("%d\n", sam.T[p].cnt);
    }
    return 0;
}
