#include <cstdio>
#include <cstring>
const int size = 500005, maxS = size * 2;
typedef long long Int64;
#define asInt64 static_cast<Int64>
struct SAM {
    struct Node {
        int c[26], len, link;
    } T[maxS];
    int siz, last, sum[maxS];
    SAM() : siz(1), last(1) {}
    void extend(int ch) {
        int id = ++siz;
        T[id].len = T[last].len + 1;
        int p = last;
        while(p && !T[p].c[ch]) {
            T[p].c[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].c[ch];
            if(T[q].len == T[p].len + 1)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                while(p && T[p].c[ch] == q) {
                    T[p].c[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        last = id;
        sum[id] = 1;
    }
    int cnt[size], q[maxS];
    Int64 count(int len) {
        for(int i = 1; i <= siz; ++i)
            ++cnt[T[i].len];
        for(int i = 1; i <= len; ++i)
            cnt[i] += cnt[i - 1];
        for(int i = 1; i <= siz; ++i)
            q[cnt[T[i].len]--] = i;
        Int64 res = 0;
        for(int i = siz; i >= 1; --i) {
            int u = q[i], cu = sum[u];
            res +=
                asInt64(T[u].len - T[T[u].link].len) *
                cu * (cu - 1) / 2;
            sum[T[u].link] += cu;
        }
        return res;
    }
} sam;
char str[size];
int main() {
    scanf("%s", str);
    int len = strlen(str);
    for(int i = len - 1; i >= 0; --i)
        sam.extend(str[i] - 'a');
    Int64 res =
        asInt64(len - 1) * len * (len + 1) / 2 -
        2 * sam.count(len);
    printf("%lld\n", res);
    return 0;
}
