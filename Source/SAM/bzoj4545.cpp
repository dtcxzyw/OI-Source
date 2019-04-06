#include <cstdio>
const int size = 200005;
namespace LCT {
    struct Node {
        int c[2], p, val, tag;
    } T[size];
#define ls T[u].c[0]
#define rs T[u].c[1]
    bool isRoot(int u) {
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
        int ku = getPos(u);
        int p = T[u].p;
        int t = T[u].c[ku ^ 1];
        int pp = T[p].p;
        T[u].p = pp;
        if(!isRoot(p))
            T[pp].c[getPos(p)] = u;
        connect(t, p, ku);
        connect(p, u, ku ^ 1);
    }
    void color(int u, int val) {
        T[u].val += val;
        T[u].tag += val;
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
        T[u].p = fu;
        access(fu);
        splay(fu);
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
typedef long long Int64;
namespace SAM {
    struct Node {
        int ch[3], len, link;
    } T[size];
    int siz = 1;
    Int64 sum = 0;
    int extend(int p, int ch) {
        int id = ++siz;
        T[id].len = T[p].len + 1;
        LCT::T[id].val = 1;
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
                LCT::link(cq, T[cq].link);
                T[id].link = T[q].link = cq;
                LCT::cut(q);
                LCT::link(q, cq);
                while(p && T[p].ch[ch] == q) {
                    T[p].ch[ch] = cq;
                    p = T[p].link;
                }
            }
        } else
            T[id].link = 1;
        LCT::link(id, T[id].link);
        sum += T[id].len - T[T[id].link].len;
        return id;
    }
    int query(const char* str) {
        int cur = 1;
        while(cur && *str) {
            cur = T[cur].ch[*str - 'a'];
            ++str;
        }
        if(cur) {
            LCT::splay(cur);
            return LCT::T[cur].val;
        }
        return 0;
    }
}
struct Edge {
    int to, nxt, c;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int c) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].c = c;
    last[u] = cnt;
}
int node[size];
void DFS(int u) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!node[v]) {
            node[v] = SAM::extend(node[u], E[i].c);
            DFS(v);
        }
    }
}
void extend(int rt, int siz) {
    for(int i = 1; i < siz; ++i) {
        int u, v;
        char c;
        scanf("%d%d %c", &u, &v, &c);
        c -= 'a';
        addEdge(u, v, c);
        addEdge(v, u, c);
    }
    DFS(rt);
}
char buf[size];
int main() {
    node[1] = 1;
    int id, n;
    scanf("%d%d", &id, &n);
    extend(1, n);
    int m;
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        int op;
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("%lld\n", SAM::sum);
                break;
            case 2: {
                int rt, siz;
                scanf("%d%d", &rt, &siz);
                extend(rt, siz);
            } break;
            case 3: {
                scanf("%s", buf);
                printf("%d\n", SAM::query(buf));
            } break;
        }
    }
    return 0;
}
