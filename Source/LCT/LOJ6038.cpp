#include <algorithm>
#include <cstdio>
#include <set>
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
void erase(std::multiset<int>& s, int w) {
    std::multiset<int>::iterator it = s.find(w);
    if(it != s.end())
        s.erase(it);
}
const int size = 800005;
struct Node {
    std::multiset<int> imw;
    int p, c[2], sw, mwl, mwr;
    bool rev, w;
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
void pushDown(int u) {
    if(T[u].rev) {
        std::swap(ls, rs);
        std::swap(T[u].mwl, T[u].mwr);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
void update(int u) {
    pushDown(ls);
    pushDown(rs);
    T[u].sw = T[ls].sw + T[rs].sw + T[u].w;
    int val = T[u].imw.size() ? *T[u].imw.rbegin() : 0;
    T[u].mwl =
        std::max(T[ls].mwl, std::max(val, T[rs].mwl) +
                     T[ls].sw + T[u].w);
    T[u].mwr =
        std::max(T[rs].mwr, std::max(val, T[ls].mwr) +
                     T[rs].sw + T[u].w);
}
void rotate(int u) {
    int ku = getPos(u);
    int p = T[u].p;
    int kp = getPos(p);
    int pp = T[p].p;
    int t = T[u].c[ku ^ 1];
    T[u].p = pp;
    if(!isRoot(p))
        T[pp].c[kp] = u;
    connect(t, p, ku);
    connect(p, u, ku ^ 1);
    update(p);
    update(u);
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
        erase(T[u].imw, T[v].mwl);
        pushDown(rs);
        T[u].imw.insert(T[rs].mwl);
        rs = v;
        update(u);
        v = u;
        u = T[u].p;
    } while(u);
}
void makeRoot(int u) {
    access(u);
    splay(u);
    T[u].rev ^= 1;
    pushDown(u);
}
void link(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
    T[u].p = v;
    T[v].imw.insert(T[u].mwl);
    update(v);
}
int main() {
    int t = read();
    int n = read();
    int q = read();
    int lastAns = 0, icnt = n;
    while(q--)
        if(read() == 1) {
            int u = read() ^ lastAns;
            int v = read() ^ lastAns;
            int id = ++icnt;
            T[id].w = true;
            update(id);
            link(u, id);
            link(v, id);
        } else {
            int u = read() ^ lastAns;
            access(u);
            splay(u);
            printf("%d\n", T[u].mwr);
            if(t)
                lastAns = T[u].mwr;
        }
    return 0;
}
