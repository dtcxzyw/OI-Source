#include <algorithm>
#include <climits>
#include <cstdio>
#include <map>
#include <set>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 200005;
typedef Int64 SumT;
const Int64 inf = 1LL << 62;
struct Maxv {
    SumT w;
    int id;
    Maxv() {}
    Maxv(SumT w, int id) : w(w), id(id) {}
    bool operator<(const Maxv& rhs) const {
        return w == rhs.w ? id > rhs.id : w < rhs.w;
    }
};
Maxv operator+(SumT sum, const Maxv& val) {
    return Maxv(sum + val.w, val.id);
}
struct Node {
    int c[2], p;
    Int64 sum, ew, pw;
    Maxv lmaxv, rmaxv;
    std::set<Maxv> imaxv;
    bool rev;
} T[size];
#define ls T[u].c[0]
#define rs T[u].c[1]
void pushDown(int u) {
    if(T[u].rev) {
        std::swap(ls, rs);
        std::swap(T[u].lmaxv, T[u].rmaxv);
        T[ls].rev ^= 1;
        T[rs].rev ^= 1;
        T[u].rev = false;
    }
}
void update(int u) {
    pushDown(ls);
    pushDown(rs);
    T[u].sum = T[ls].sum + T[rs].sum + T[u].ew;
    Maxv imaxv = T[u].imaxv.size() ?
        *T[u].imaxv.rbegin() :
        Maxv(-inf, 0);
    T[u].lmaxv = std::max(
        T[ls].lmaxv, T[ls].sum +
            std::max(T[u].ew +
                         std::max(imaxv, T[rs].lmaxv),
                     Maxv(T[u].pw, u)));
    T[u].rmaxv = std::max(
        T[rs].rmaxv, T[rs].sum +
            std::max(T[u].ew +
                         std::max(imaxv, T[ls].rmaxv),
                     Maxv(T[u].pw, u)));
}
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
    int kp = getPos(p);
    int pp = T[p].p;
    int t = T[u].c[ku ^ 1];
    T[u].p = pp;
    if(!isRoot(p))
        T[pp].c[kp] = u;
    connect(p, u, ku ^ 1);
    connect(t, p, ku);
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
            rotate(getPos(u) == getPos(p) ? p : u);
        rotate(u);
    }
}
void access(int u) {
    int v = 0;
    do {
        splay(u);
        if(v)
            T[u].imaxv.erase(T[v].lmaxv);
        if(rs) {
            pushDown(rs);
            T[u].imaxv.insert(T[rs].lmaxv);
        }
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
    T[v].imaxv.insert(T[u].lmaxv);
    update(v);
}
std::map<Int64, int> eid;
Int64 encode(Int64 a, Int64 b) {
    if(a > b)
        std::swap(a, b);
    return a << 32 | b;
}
int main() {
    int n = read();
    int q = read();
    T[0].lmaxv = T[0].rmaxv = Maxv(-inf, n + 1);
    for(int i = 1; i <= n; ++i) {
        T[i].pw = read();
        update(i);
    }
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int id = n + i;
        eid[encode(u, v)] = id;
        T[id].ew = -read(), T[id].pw = -inf;
        update(id);
        link(u, id);
        link(v, id);
    }
    int last = 1;
    while(q--) {
        if(read() == 1) {
            int u = read();
            access(u);
            splay(u);
            T[u].pw = read();
            update(u);
        } else {
            int id = eid[encode(read(), read())];
            access(id);
            splay(id);
            T[id].ew = -read();
            update(id);
        }
        access(last);
        splay(last);
        Int64 bak = T[last].pw;
        T[last].pw = -inf;
        update(last);
        int now = T[last].rmaxv.id;
        T[last].pw = bak;
        update(last);
        printf("%d ", now);
        last = now;
    }
    return 0;
}
