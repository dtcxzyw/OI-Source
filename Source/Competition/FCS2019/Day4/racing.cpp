#include <algorithm>
#include <cstdio>
#include <queue>
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
const int inf = 1 << 30;
struct Path {
    int u, d;
    Path(int u = -1, int d = -inf) : u(u), d(d) {}
    bool operator<(const Path& rhs) const {
        return d == rhs.d ? u < rhs.u : d < rhs.d;
    }
    bool operator==(const Path& rhs) const {
        return u == rhs.u && d == rhs.d;
    }
    Path operator+(int cd) const {
        return Path(u, d + cd);
    }
};
template <typename T>
struct RemoveableHeap {
    std::priority_queue<T> A, B;
    void push(T x) {
        A.push(x);
    }
    void pop(T x) {
        B.push(x);
    }
    T top() {
        while(A.size() && B.size() &&
              A.top() == B.top())
            A.pop(), B.pop();
        return A.size() ? A.top() : T();
    }
};
const int size = 70005;
struct Node {
    RemoveableHeap<Path> imw;
    Path mwl, mwr;
    int p, c[2], siz;
    bool rev;
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
    T[u].siz = T[ls].siz + T[rs].siz + 1;
    Path val = T[u].imw.top();
    T[u].mwl =
        std::max(T[ls].mwl, std::max(val, T[rs].mwl) +
                     (T[ls].siz + 1));
    T[u].mwr =
        std::max(T[rs].mwr, std::max(val, T[ls].mwr) +
                     (T[rs].siz + 1));
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
        T[u].imw.pop(T[v].mwl);
        pushDown(rs);
        T[u].imw.push(T[rs].mwl);
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
void link(int u, int v) {
    split(u, v);
    T[u].p = v;
    T[v].imw.push(T[u].mwl);
    update(v);
}
void cut(int u, int v) {
    split(u, v);
    T[u].p = T[v].c[0] = 0;
    update(v);
}
struct ScanLine {
    int op, u, v, t;
    ScanLine() {}
    ScanLine(int op, int u, int v, int t)
        : op(op), u(u), v(v), t(t) {}
    bool operator<(const ScanLine& rhs) const {
        return t < rhs.t;
    }
} L[size * 2];
struct Query {
    int v, id;
    bool operator<(const Query& rhs) const {
        return v < rhs.v;
    }
} Q[size];
void calc(int u, RemoveableHeap<int>& res, int op) {
    access(u);
    splay(u);
    u = T[u].mwr.u;
    access(u);
    splay(u);
    int val = T[u].mwr.d;
    if(val) {
        if(op == 1)
            res.push(val);
        else
            res.pop(val);
    }
}
int ans[size];
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        T[i].imw.push(Path(i, -1));
        update(i);
    }
    int lcnt = 0;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int l = read();
        int r = read();
        L[++lcnt] = ScanLine(1, u, v, l);
        L[++lcnt] = ScanLine(-1, u, v, r + 1);
    }
    std::sort(L + 1, L + lcnt + 1);
    for(int i = 1; i <= m; ++i) {
        Q[i].id = i;
        Q[i].v = read();
    }
    std::sort(Q + 1, Q + m + 1);
    RemoveableHeap<int> res;
    for(int i = 1, cl = 1; i <= m; ++i) {
        while(cl <= lcnt && L[cl].t <= Q[i].v) {
            if(L[cl].op == 1) {
                calc(L[cl].u, res, -1);
                calc(L[cl].v, res, -1);
                link(L[cl].u, L[cl].v);
                calc(L[cl].u, res, 1);
            } else {
                calc(L[cl].u, res, -1);
                cut(L[cl].u, L[cl].v);
                calc(L[cl].u, res, 1);
                calc(L[cl].v, res, 1);
            }
            ++cl;
        }
        ans[Q[i].id] = res.top();
    }
    for(int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
