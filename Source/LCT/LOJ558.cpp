#include <algorithm>
#include <cstdio>
#include <map>
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
int getOp() {
    int c;
    do
        c = getchar();
    while(c < 'A' || c > 'Z');
    return c;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 100005;
struct Node {
    Int64 sw, swl, swr, isw;
    int p, c[2], sc, isc, w;
    bool rev, col;
} T[size * 5];
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
        std::swap(T[u].swl, T[u].swr);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
void update(int u) {
    pushDown(ls);
    pushDown(rs);
    T[u].sc =
        T[ls].sc + T[rs].sc + T[u].isc + T[u].col;
    T[u].sw = T[ls].sw + T[rs].sw + T[u].w;
    T[u].swl = T[ls].swl + T[rs].swl + T[u].isw +
        (T[ls].sw + T[u].w) *
            (T[u].isc + T[u].col + T[rs].sc);
    T[u].swr = T[ls].swr + T[rs].swr + T[u].isw +
        (T[rs].sw + T[u].w) *
            (T[u].isc + T[u].col + T[ls].sc);
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
        pushDown(rs);
        T[u].isc += T[rs].sc - T[v].sc;
        T[u].isw += T[rs].swl - T[v].swl;
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
void split(int u, int v) {
    makeRoot(u);
    access(v);
    splay(v);
}
void cut(int u, int v) {
    split(u, v);
    T[v].c[0] = T[u].p = 0;
    update(v);
}
void link(int u, int v) {
    split(u, v);
    T[u].p = v;
    T[v].isc += T[u].sc;
    T[v].isw += T[u].swl;
    update(v);
}
std::map<Int64, int> eid;
Int64 encode(Int64 u, Int64 v) {
    if(u < v)
        std::swap(u, v);
    return u << 32 | v;
}
void addEdge(int id) {
    int u = read();
    int v = read();
    T[id].sw = T[id].w = read();
    link(u, id);
    link(v, id);
    eid[encode(u, v)] = id;
}
int main() {
    int n = read();
    int m = read();
    int k = read();
    int cid = n;
    while(m--)
        addEdge(++cid);
    while(k--)
        switch(getOp()) {
            case 'L':
                addEdge(++cid);
                break;
            case 'C': {
                int u = read();
                int v = read();
                int id = eid[encode(u, v)];
                cut(u, id);
                cut(v, id);
                eid.erase(encode(u, v));
            } break;
            case 'F': {
                int u = read();
                access(u);
                splay(u);
                T[u].col ^= 1;
                update(u);
            } break;
            case 'Q': {
                int u = read();
                access(u);
                splay(u);
                printf("%lld\n", T[u].swr);
            } break;
        }
    return 0;
}
