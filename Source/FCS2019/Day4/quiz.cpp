#include <algorithm>
#include <cmath>
#include <cstdio>
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
typedef long long Int64;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int W[size], IW[size], L[size], R[size], icnt = 0;
void DFS(int u, int p) {
    L[u] = ++icnt;
    IW[icnt] = W[u];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p)
            DFS(v, u);
    }
    R[u] = icnt;
}
int bid[size];
struct Op {
    int l, r, t, id;
    bool operator<(const Op& rhs) const {
        if(bid[l] != bid[rhs.l])
            return l < rhs.l;
        if(bid[r] != bid[rhs.r])
            return r < rhs.r;
        return t < rhs.t;
    }
} A[size], B[size];
int n;
template <typename T>
struct BIT {
    T X[size];
    void build() {
        for(int i = 1; i <= n; ++i) {
            X[i] += IW[i];
            int j = i + (i & -i);
            if(j <= n)
                X[j] += X[i];
        }
    }
    void modify(int x, T op) {
        while(x <= n) {
            X[x] += op;
            x += x & -x;
        }
    }
    T query(int x) {
        T res = 0;
        while(x) {
            res += X[x];
            x -= x & -x;
        }
        return res;
    }
};
BIT<int> SA;
BIT<Int64> SB;
Int64 ans[size];
void modifyA(int u, int val, Int64& cur) {
    Int64 delta = val - W[u];
    W[u] = val;
    cur += SA.query(L[u]) * delta;
    SB.modify(L[u], delta);
}
void modifyB(int u, int op, Int64& cur) {
    SA.modify(L[u], op);
    SA.modify(R[u] + 1, -op);
    cur += op * (SB.query(R[u]) - SB.query(L[u] - 1));
}
int main() {
    n = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        W[i] = read();
    int rt = 0;
    for(int i = 1; i <= n; ++i) {
        int u = read();
        int v = read();
        if(u == 0)
            rt = v;
        else {
            addEdge(u, v);
            addEdge(v, u);
        }
    }
    DFS(rt, 0);
    SB.build();
    int bsiz = pow(n, 2.0 / 3.0) + 1;
    for(int i = 1; i <= n; ++i)
        bid[i] = i / bsiz;
    int cntA = 0, cntB = 0;
    for(int i = 1; i <= q; ++i) {
        int op = read();
        int l = read();
        int r = read();
        if(op == 1) {
            ++cntA;
            A[cntA].l = l, A[cntA].r = r;
        } else {
            ++cntB;
            B[cntB].l = l, B[cntB].r = r,
            B[cntB].t = cntA, B[cntB].id = cntB;
        }
    }
    std::sort(B + 1, B + cntB + 1);
    Int64 cur = 0;
    for(int i = 1, cl = 1, cr = 0, ct = 0; i <= cntB;
        ++i) {
        while(ct < B[i].t) {
            ++ct;
            int u = A[ct].l, val = A[ct].r;
            A[ct].id = W[u];
            modifyA(u, val, cur);
        }
        while(ct > B[i].t) {
            int u = A[ct].l, val = A[ct].id;
            modifyA(u, val, cur);
            --ct;
        }
        while(cr < B[i].r)
            modifyB(++cr, 1, cur);
        while(cr > B[i].r)
            modifyB(cr--, -1, cur);
        while(cl > B[i].l)
            modifyB(--cl, 1, cur);
        while(cl < B[i].l)
            modifyB(cl++, -1, cur);
        ans[B[i].id] = cur;
    }
    for(int i = 1; i <= cntB; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
