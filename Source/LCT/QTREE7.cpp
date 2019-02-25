#include <algorithm>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 100005, inf = 1 << 30;
struct RemoveableHeap {
    std::priority_queue<int> A, B;
    void push(int x) {
        A.push(x);
    }
    void pop(int x) {
        B.push(x);
    }
    int top() {
        while(A.size() && B.size() &&
              A.top() == B.top())
            A.pop(), B.pop();
        return A.size() ? A.top() : -inf;
    }
};
struct Node {
    Node *p, *c[2];
    int maxv;
    RemoveableHeap imaxv;
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
    u->maxv =
        std::max(std::max((ls ? ls->maxv : -inf),
                          (rs ? rs->maxv : -inf)),
                 u->imaxv.top());
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
            u->imaxv.push(rs->maxv);
        rs = v;
        if(rs)
            u->imaxv.pop(rs->maxv);
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
    fu->imaxv.push(u->maxv);
    fu->maxv = std::max(fu->maxv, u->maxv);
}
void cut(Ptr u, Ptr fu) {
    access(u);
    splay(fu);
    fu->c[1] = u->p = 0;
    update(fu);
}
bool col[size];
std::vector<int> G[size];
int fa[size], w[size];
void DFS(int u, int p) {
    for(int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if(v != p)
            DFS(v, u);
    }
    fa[u] = p;
    int c = col[u];
    T[c][u].p = T[c] + p;
    T[0][u].imaxv.push(w[u]), T[1][u].imaxv.push(w[u]);
    update(T[0] + u), update(T[1] + u);
    T[c][p].imaxv.push(T[c][u].maxv);
}
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i = 1; i <= n; ++i)
        col[i] = read();
    for(int i = 1; i <= n; ++i)
        w[i] = read();
    DFS(1, n + 1);
    update(T[0] + n + 1);
    update(T[1] + n + 1);
    int q = read();
    for(int i = 0; i < q; ++i) {
        int op = read();
        int u = read();
        switch(op) {
            case 0: {
                Ptr up = T[col[u]] + u;
                access(up);
                splay(up);
                while(up->c[0])
                    up = up->c[0];
                splay(up);
                printf("%d\n", up->c[1]->maxv);
            } break;
            case 1: {
                cut(T[col[u]] + u, T[col[u]] + fa[u]);
                col[u] ^= 1;
                link(T[col[u]] + u, T[col[u]] + fa[u]);
            } break;
            case 2: {
                int cw = read();
                int old = w[u];
                w[u] = cw;
                for(int c = 0; c < 2; ++c) {
                    Ptr up = T[c] + u;
                    access(up);
                    splay(up);
                    up->imaxv.pop(old);
                    up->imaxv.push(cw);
                    update(up);
                }
            } break;
        }
    }
    return 0;
}
