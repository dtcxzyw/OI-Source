#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 100005;
struct PAM {
    struct Node {
        int nxt[26], fail, len;
    } T[size];
    char buf[size];
    int siz, n, last;
    void reset() {
        memset(T, 0, sizeof(Node) * (siz + 1));
        T[0].len = 0;
        T[0].fail = 1;
        T[1].len = -1;
        buf[0] = -1;
        siz = 1, n = last = 0;
    }
    int getFail(int p, int ch) {
        while(buf[n - 1 - T[p].len] != ch)
            p = T[p].fail;
        return p;
    }
    int insert(int ch) {
        buf[++n] = ch;
        int p = getFail(last, ch);
        if(!T[p].nxt[ch]) {
            int id = ++siz;
            T[id].fail =
                T[getFail(T[p].fail, ch)].nxt[ch];
            T[id].len = T[p].len + 2;
            T[p].nxt[ch] = id;
        }
        last = T[p].nxt[ch];
        return T[last].len;
    }
} pam;
char buf[size];
int X[size], Y[size];
int main() {
    scanf("%s", buf + 1);
    int n = strlen(buf + 1);
    pam.reset();
    for(int i = 1; i <= n; ++i)
        X[i] = pam.insert(buf[i] - 'a');
    pam.reset();
    for(int i = n; i >= 1; --i)
        Y[i] = pam.insert(buf[i] - 'a');
    int ans = 0;
    for(int i = 2; i <= n; ++i)
        ans = std::max(ans, X[i - 1] + Y[i]);
    printf("%d\n", ans);
    return 0;
}
