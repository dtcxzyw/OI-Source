// P4051
#include <cstdio>
const int size = 100005, maxS = size * 4, esiz = 95;
struct SAM {
    struct State {
        int len, link, nxt[esiz], jmp, jdis;
        bool mark;
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
    int len() const {
        return st[last].len;
    }
    void jump(int u) {
        int p, dis = 0;
        for(p = u; st[p].jmp; p = st[p].jmp)
            dis += st[p].jdis;
        if(dis) {
            int res = p;
            for(p = u; st[p].jmp;) {
                int old = st[p].jdis;
                st[p].jdis = dis;
                dis -= old;
                int nxt = st[p].jmp;
                st[p].jmp = res;
                p = nxt;
            }
        }
    }
    int top, *sa;
    void DFS(int u, int d) {
        if(st[u].mark)
            sa[++top] = d;
        for(int i = 0; i < esiz; ++i) {
            int v = st[u].nxt[i];
            if(v) {
                jump(v);
                if(st[v].jmp)
                    DFS(st[v].jmp, d - 1 - st[v].jdis);
                else
                    DFS(v, d - 1);
            }
        }
    }
    void buildSA(int* buf) {
        for(int p = last; p; p = st[p].link)
            st[p].mark = true;
        for(int i = 1; i <= siz; ++i)
            if(!st[i].mark) {
                int c = 0, p;
                for(int j = 0; j < esiz && c <= 1; ++j) {
                    int v = st[i].nxt[j];
                    if(v) {
                        p = v;
                        ++c;
                    }
                }
                if(c == 1)
                    st[i].jmp = p, st[i].jdis = 1;
            }
        sa = buf;
        top = 0;
        DFS(1, len() + 1);
    }
} sam;
char buf[size];
int SA[2 * size];
int main() {
    gets(buf);
    for(int i = 0; buf[i]; ++i)
        sam.extend(buf[i] - ' ');
    int len = sam.len();
    for(int i = 0; buf[i]; ++i)
        sam.extend(buf[i] - ' ');
    sam.buildSA(SA);
    for(int i = 1; i <= sam.top; ++i)
        if(SA[i] <= len) {
            int p = SA[i] - 2;
            if(p == -1)
                p += len;
            putchar(buf[p]);
        }
    putchar('\n');
    return 0;
}
