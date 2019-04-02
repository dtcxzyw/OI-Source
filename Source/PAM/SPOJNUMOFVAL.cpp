#include <cstdio>
const int size = 1005;
struct PAM {
    struct Node {
        int nxt[26], len, fail, cnt;
    } T[size];
    int siz, last, n;
    char buf[size];
    PAM() {
        T[0].len = 0;
        T[0].fail = 1;
        T[1].len = -1;
        siz = 1;
        last = n = 0;
        buf[0] = -1;
    }
    int getFail(int p, int ch) {
        while(buf[n - 1 - T[p].len] != ch)
            p = T[p].fail;
        return p;
    }
    void extend(int ch) {
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
        ++T[last].cnt;
    }
    int count() {
        int res = 0;
        for(int i = siz; i >= 2; --i) {
            int val = T[i].cnt;
            res += val;
            T[T[i].fail].cnt += val;
        }
        return res;
    }
} pam;
int main() {
    while(true) {
        int c = getchar();
        if('a' <= c && c <= 'z')
            pam.extend(c - 'a');
        else
            break;
    }
    printf("%d\n", pam.count());
    return 0;
}
