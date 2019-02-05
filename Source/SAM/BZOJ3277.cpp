#include <algorithm>
#include <cstdio>
typedef long long Int64;
const int size = 100005;
struct SAM {
    struct Node {
        int ch[26], len, link, cnt, lid;
    } T[size * 2];
    int siz, last;
    SAM() : siz(1), last(1) {}
    int extend(int ch, int sid) {
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
        return id;
    }
    int cnt[size * 2], q[size * 2], d[size * 2];
    void cook(int k) {
        for(int i = 1; i <= siz; ++i)
            ++d[T[i].link];
        int qcnt = 0;
        for(int i = 1; i <= siz; ++i)
            if(d[i] == 0)
                q[++qcnt] = i;
        for(int i = 1; i <= qcnt; ++i) {
            int u = q[i];
            if(--d[T[u].link] == 0)
                q[++qcnt] = T[u].link;
        }
        for(int i = siz; i >= 1; --i) {
            int u = q[i];
            if(u != 1 && T[u].cnt >= k &&
               T[T[u].link].cnt < k)
                throw;
            cnt[u] = cnt[T[u].link] +
                (T[u].cnt >= k ?
                     T[u].len - T[T[u].link].len :
                     0);
        }
    }
} sam;
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i) {
        sam.last = 1;
        int c;
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        while('a' <= c && c <= 'z') {
            addEdge(i, sam.extend(c - 'a', i));
            c = getchar();
        }
    }
    sam.cook(k);
    for(int i = 1; i <= n; ++i) {
        Int64 res = 0;
        for(int j = last[i]; j; j = E[j].nxt)
            res += sam.cnt[E[j].to];
        printf("%lld ", res);
    }
    return 0;
}
