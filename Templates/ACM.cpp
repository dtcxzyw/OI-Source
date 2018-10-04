// P3121
#include <cstdio>
const int size = 100005;
struct Node {
    int nxt[26], fail, len;
    bool mark;
} T[size];
void insert() {
    static int icnt = 0;
    int p = 0, c;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        int& id = T[p].nxt[c - 'a'];
        if(id == 0) {
            id = ++icnt;
            T[id].len = T[p].len + 1;
        }
        p = id;
        c = getchar();
    }
    T[p].mark = true;
}
int q[size];
void cook() {
    int b = 0, e = 0;
    for(int i = 0; i < 26; ++i)
        if(T[0].nxt[i])
            q[e++] = T[0].nxt[i];
    while(b != e) {
        int u = q[b++];
        for(int i = 0; i < 26; ++i) {
            int& v = T[u].nxt[i];
            if(v) {
                T[v].fail = T[T[u].fail].nxt[i];
                q[e++] = v;
            } else
                v = T[T[u].fail].nxt[i];
        }
    }
}
char buf[size];
struct LNode {
    int ch, st, pre, nxt;
} L[size];
int main() {
    int c;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    int siz = 0;
    L[0].nxt = 1;
    while('a' <= c && c <= 'z') {
        ++siz;
        L[siz].ch = c - 'a';
        L[siz].pre = siz - 1;
        L[siz].nxt = siz + 1;
        c = getchar();
    }
    int n;
    scanf("%d", &n);
    while(n--)
        insert();
    cook();
    int pt = 0, pl = 1, end = siz + 1;
    while(pl != end) {
        pt = T[pt].nxt[L[pl].ch];
        if(T[pt].mark) {
            int step = T[pt].len, epos = L[pl].nxt;
            while(step--)
                pl = L[pl].pre;
            L[pl].nxt = epos;
            L[epos].pre = pl;
            pt = L[pl].st;
            pl = epos;
        } else {
            L[pl].st = pt;
            pl = L[pl].nxt;
        }
    }
    pl = L[0].nxt;
    while(pl != end) {
        putchar('a' + L[pl].ch);
        pl = L[pl].nxt;
    }
    putchar('\n');
    return 0;
}
