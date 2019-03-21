#include <cstdio>
const int maxS = 405;
struct SAM {
    struct Node {
        int nxt[26], link, len;
    } T[maxS];
    int last, siz;
    SAM() : last(1), siz(1) {}
    int extend(int ch) {
        int id = ++siz;
        T[id].len = T[last].len + 1;
        int p = last;
        while(p && !T[p].nxt[ch]) {
            T[p].nxt[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].nxt[ch];
            if(T[p].len + 1 == T[q].len)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq].len = T[p].len + 1;
                while(p && T[p].nxt[ch] == q) {
                    T[p].nxt[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        last = id;
        return T[T[id].link].len -
            T[T[T[id].link].link].len;
    }
} sam;
char buf[maxS];
int main() {
    int n;
    scanf("%d%s", &n, buf + 1);
    for(int i = 1; i <= n; ++i)
        printf("%d\n", sam.extend(buf[i] - 'a'));
    return 0;
}
