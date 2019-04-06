#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxS = 1200005, maxQ = 3000005;
namespace LCT {
    struct Node {
        int c[2], p, val, tag;
    } T[maxS];
#define ls T[u].c[0]
#define rs T[u].c[1]
    int isRoot(int u) {
        int p = T[u].p;
        return T[p].c[0] != u && T[p].c[1] != u;
    }
    int getPos(int u) {
        int p = T[u].p;
        return T[p].c[1] == u;
    }
    void connect(int u, int p, int c) {
        T[u].p = p;
        T[p].c[c] = u;
    }
    void rotate(int u) {
        int p = T[u].p;
        int ku = getPos(u);
        int pp = T[p].p;
        int t = T[u].c[ku ^ 1];
        T[u].p = pp;
        if(!isRoot(p))
            T[pp].c[getPos(p)] = u;
        connect(t, p, ku);
        connect(p, u, ku ^ 1);
    }
    void color(int u, int v) {
        T[u].val += v;
        T[u].tag += v;
    }
    void pushDown(int u) {
        if(T[u].tag) {
            color(ls, T[u].tag);
            color(rs, T[u].tag);
            T[u].tag = 0;
        }
    }
    void push(int u) {
        if(!isRoot(u))
            push(T[u].p);
        pushDown(u);
    }
    void splay(int u) {
        push(u);
        while(!isRoot(u)) {
            int p = T[u].p;
            if(!isRoot(p))
                rotate(getPos(p) == getPos(u) ? p : u);
            rotate(u);
        }
    }
    void access(int u) {
        int v = 0;
        do {
            splay(u);
            rs = v;
            v = u;
            u = T[u].p;
        } while(u);
    }
    void link(int u, int fu) {
        access(fu);
        splay(fu);
        T[u].p = fu;
        color(fu, T[u].val);
    }
    void cut(int u) {
        access(u);
        splay(u);
        color(ls, -T[u].val);
        T[ls].p = 0;
        ls = 0;
    }
}
namespace SAM {
    struct Node {
        int ch[26], link, len;
    } T[maxS];
    int siz = 1, last = 1;
    void extendImpl(int ch) {
        int id = ++siz;
        T[id].len = T[last].len + 1;
        LCT::T[id].val = 1;
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
                LCT::cut(q);
                LCT::link(cq, T[cq].link);
                while(p && T[p].ch[ch] == q) {
                    T[p].ch[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
                LCT::link(q, cq);
            }
        } else
            T[id].link = 1;
        LCT::link(id, T[id].link);
        last = id;
    }
    void extend(const char* str) {
        while(*str) {
            extendImpl(*str - 'A');
            ++str;
        }
    }
    int query(const char* str) {
        int cur = 1;
        while(cur && *str) {
            cur = T[cur].ch[*str - 'A'];
            ++str;
        }
        if(cur) {
            LCT::splay(cur);
            return LCT::T[cur].val;
        }
        return 0;
    }
}
char buf[maxQ], op[7];
void decode(int mask) {
    int len = strlen(buf);
    for(int i = 0; i < len; ++i) {
        mask = (mask * 131 + i) % len;
        std::swap(buf[i], buf[mask]);
    }
}
int main() {
    int q;
    scanf("%d%s", &q, buf);
    SAM::extend(buf);
    int mask = 0;
    for(int i = 1; i <= q; ++i) {
        scanf("%s%s", op, buf);
        decode(mask);
        if(*op == 'A')
            SAM::extend(buf);
        else {
            int res = SAM::query(buf);
            mask ^= res;
            printf("%d\n", res);
        }
    }
    return 0;
}
