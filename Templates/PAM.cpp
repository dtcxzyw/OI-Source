#include <algorithm>
#include <cstdio>
const int size = 300005;
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
struct PAM {
    struct Node {
        int len, nxt[26], fail, cnt;
    } T[size];
    char buf[size];
    int last, siz, n;
    PAM() {
        T[0].len = 0;
        T[0].fail = 1;
        T[1].len = -1;
        last = 0;
        siz = 1;
        n = 0;
        buf[0] = -1;
    }
    int getFail(int p, int c) const {
        while(buf[n - 1 - T[p].len] != c)
            p = T[p].fail;
        return p;
    }
    void extend(int c) {
        buf[++n] = c;
        int p = getFail(last, c);
        if(!T[p].nxt[c]) {
            int u = ++siz;
            T[u].len = T[p].len + 2;
            T[u].fail =
                T[getFail(T[p].fail, c)].nxt[c];
            T[p].nxt[c] = u;
        }
        last = T[p].nxt[c];
        ++T[last].cnt;
    }
    Int64 solve() {
        Int64 ans = 0;
        for(int i = siz; i >= 1; --i) {
            T[T[i].fail].cnt += T[i].cnt;
            ans = std::max(ans, asInt64(T[i].cnt) *
                               T[i].len);
        }
        return ans;
    }
} pam;
int main() {
    int c;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        pam.extend(c - 'a');
        c = getchar();
    }
    printf("%lld\n", pam.solve());
    return 0;
}
