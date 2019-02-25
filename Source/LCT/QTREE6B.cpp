#include <algorithm>
#include <cstdio>
#include <vector>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 100005;
struct Node {
    Node *p, *c[2];
    int siz, isiz;
} T[2][size];
typedef Node* Ptr;
#define ls (u->c[0])
#define rs (u->c[1])
bool isRoot(Ptr u) {
    Ptr p = u->p;
    return !p || (p->c[0] != u && p->c[1] != u);
}
int getPos(Ptr u) {
    Ptr p = u->p;
    return p->c[1] == u;
}
void connect(Ptr u, Ptr p, int c) {
    if(u)
        u->p = p;
    p->c[c] = u;
}
void update(Ptr u) {
    u->siz = (ls ? ls->siz : 0) + u->isiz +
        (rs ? rs->siz : 0);
}
void rotate(Ptr u) {
    int ku = getPos(u);
    Ptr p = u->p;
    Ptr pp = p->p;
    Ptr t = u->c[ku ^ 1];
    u->p = pp;
    if(!isRoot(p))
        pp->c[getPos(p)] = u;
    connect(p, u, ku ^ 1);
    connect(t, p, ku);
    update(p);
    update(u);
}
void splay(Ptr u) {
    while(!isRoot(u)) {
        Ptr p = u->p;
        if(!isRoot(p))
            rotate(getPos(p) == getPos(u) ? p : u);
        rotate(u);
    }
}
void access(Ptr u) {
    Ptr v = 0;
    do {
        splay(u);
        if(rs)
            u->isiz += rs->siz;
        rs = v;
        if(rs)
            u->isiz -= rs->siz;
        update(u);
        v = u;
        u = u->p;
    } while(u);
}
void link(Ptr u, Ptr fu) {
    access(fu);
    splay(fu);
    splay(u);
    u->p = fu;
    fu->isiz += u->siz;
    fu->siz += u->siz;
}
void cut(Ptr u, Ptr fu) {
    access(u);
    splay(fu);
    fu->c[1] = u->p = 0;
    update(fu);
}
bool col[size];
std::vector<int> G[size];
int fa[size];
int DFS(int u, int p) {
    int siz = 1;
    for(int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if(v != p)
            siz += DFS(v, u);
    }
    fa[u] = p;
    T[0][u].p = T[0] + p;
    T[0][u].siz = T[0][u].isiz = siz;
    T[1][u].siz = T[1][u].isiz = 1;
    return siz;
}
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    T[0][n + 1].siz = T[0][n + 1].isiz =
        1 + DFS(1, n + 1);
    T[1][n + 1].siz = T[1][n + 1].isiz = 1;
    int q = read();
    for(int i = 0; i < q; ++i) {
        int op = read();
        int u = read();
        if(op) {
            cut(T[col[u]] + u, T[col[u]] + fa[u]);
            col[u] ^= 1;
            link(T[col[u]] + u, T[col[u]] + fa[u]);
        } else {
            Ptr up = T[col[u]] + u;
            access(up);
            splay(up);
            while(up->c[0])
                up = up->c[0];
            splay(up);
            printf("%d\n", up->c[1]->siz);
        }
    }
    return 0;
}
