#include <cstdio>
typedef long long Int64;
const int size = 400005, maxS = 2 * size;
struct SAM {
    struct Node {
        int link, len, nxt[26], right[2];
    } T[maxS];
    int last, siz;
    SAM() : last(1), siz(1) {}
    void extend(int ch, int sid) {
        int v = T[last].nxt[ch];
        if(v && T[last].len + 1 == T[v].len) {
            last = v;
            T[v].right[sid] = 1;
            return;
        }
        int p = last, id = ++siz;
        T[id].len = T[p].len + 1;
        T[id].right[sid] = 1;
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
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                T[cq].right[0] = T[cq].right[1] = 0;
                while(p && T[p].nxt[ch] == q) {
                    T[p].nxt[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        last = id;
    }
    void insert(int id) {
        int c;
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        while('a' <= c && c <= 'z') {
            extend(c - 'a', id);
            c = getchar();
        }
    }
    int cnt[size], q[maxS];
    Int64 count() {
        int n = T[last].len;
        for(int i = 1; i <= siz; ++i)
            ++cnt[T[i].len];
        for(int i = 1; i <= n; ++i)
            cnt[i] += cnt[i - 1];
        for(int i = 1; i <= siz; ++i)
            q[cnt[T[i].len]--] = i;
        for(int i = siz; i >= 1; --i) {
            int u = q[i], p = T[u].link;
            T[p].right[0] += T[u].right[0];
            T[p].right[1] += T[u].right[1];
        }
        Int64 res = 0;
        for(int i = 1; i <= siz; ++i) {
            Int64 cnt = T[i].len - T[T[i].link].len;
            res += cnt * T[i].right[0] * T[i].right[1];
        }
        return res;
    }
} sam;
int main() {
    sam.insert(0);
    sam.last = 1;
    sam.insert(1);
    printf("%lld\n", sam.count());
    return 0;
}
