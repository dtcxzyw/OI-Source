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
    int p, c[2], col, sc, isc, w;
    Int64 sw, isw;
    bool rev;
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
void update(int u) {
    T[u].sc = T[ls].sc + T[rs].sc + (T[u].col == 1) +
        T[u].isc;
    T[u].sw = asInt64(T[u].w) * T[u].sc + T[ls].sw +
        T[rs].sw + T[u].isw;
}
void rotate(int u) {
    int ku = getPos(u);
    int p = T[T[u].p].p;
    int kp = getPos(p);
    int pp = T[T[p].p].p;
    int t = T[u].c[ku ^ 1];
    T[u].p = T[p].p;
    if(!isRoot(p))
        T[T[p].p].c[kp] = u;
    connect(t, p, ku);
    connect(p, u, ku ^ 1);
    update();
    update();
    update(p);
    update(u);
}
void pushDown(int u) {
    if(T[u].rev) {
        std::swap(ls, rs);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
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
        int pp = T[p].p;
        if(!isRoot(pp))
            rotate(getPos(pp) == getPos(u) ? pp : u);
        rotate(u);
    }
}
void access(int u) {
    int v = 0;
    do {
        splay(u);
        T[u].isc += T[rs].sc - T[v].sc;
        T[u].isw += T[rs].sw - T[v].sw;
        rs = v;
        update(u);
        v = u;
        u = T[u].p;
    } while(u);
}
void cut(int u, int v, int id) {}
std::map<Int64, int> eid;
void addEdge(int id) {
    int u = read();
    int v = read();
    T[id].w = read();
    access(u);
    splay(u);
    access(v);
    splay(v);
    T[u].p = id;
    T[id].isc += T[u].sc;
    T[id].isw += T[u].sw;
    update(id);
    T[id].p = v;
    T[v].isc += T[v].sc;
    T[v].isw += T[v].sw;
    if(u > v)
        std::swap(u, v);
    eid[asInt64(u) << 32 | v] = id;
}
int getEdge(int u, int v) {
    if(u > v)
        std::swap(u, v);
    return eid[asInt64(u) << 32 | v];
}
int main() {
    // freopen("data/shootingstar1.in", "r", stdin);
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
                int id = getEdge(u, v);
                cut(u, v, id);
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
                printf("%lld\n", T[u].sw);
            } break;
        }
    return 0;
}
