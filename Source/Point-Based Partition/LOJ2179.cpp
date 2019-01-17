#include <algorithm>
#include <cstdio>
namespace IO {
    char buf[1 << 23], *S, *T;
    void init() {
#ifdef ONLINE_JUDGE
        S = buf;
        T = buf + fread(buf, 1, sizeof(buf), stdin);
#endif
    }
    int getc() {
#ifdef ONLINE_JUDGE
        return *S++;
#else
        return getchar();
#endif
    }
}
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
const int size = 200005, inf = 1 << 29;
struct Edge {
    int to, nxt, c;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int c) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].c = c;
    last[u] = cnt;
}
int mtsiz, tsiz, nrt, siz[size];
bool flag[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !flag[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            msiz = std::max(msiz, siz[v]);
        }
    }
    msiz = std::max(msiz, tsiz - siz[u]);
    if(msiz < mtsiz)
        mtsiz = msiz, nrt = u;
}
int getRoot(int u, int csiz) {
    tsiz = csiz, mtsiz = inf;
    getRootImpl(u, 0);
    return nrt;
}
int L, R;
struct Node {
    int w, minv, ts;
} T1[size << 2], T2[size << 2], *T;
void loadNode(int u) {
    if(T[u].ts != T[0].ts)
        T[u].w = T[u].minv = -inf, T[u].ts = T[0].ts;
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
int p, val;
void modifyImpl(int l, int r, int id) {
    loadNode(id);
    if(T[id].minv >= val)
        return;
    T[id].w = std::max(T[id].w, val);
    if(l == r)
        T[id].minv = T[id].w;
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            modifyImpl(ls), loadNode(id << 1 | 1);
        else
            modifyImpl(rs), loadNode(id << 1);
        T[id].minv = std::min(T[id << 1].minv,
                              T[id << 1 | 1].minv);
    }
}
void modify(Node* tree, int pos, int w) {
    T = tree, p = pos, val = w;
    modifyImpl(1, R - 1, 1);
}
int res, nl, nr;
void queryImpl(int l, int r, int id) {
    loadNode(id);
    if(T[id].w <= res)
        return;
    if(nl <= l && r <= nr)
        res = T[id].w;
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            queryImpl(ls);
        if(m < nr)
            queryImpl(rs);
    }
}
int query(Node* tree, int l, int r, int limit) {
    T = tree, nl = l, nr = r, res = limit - 1;
    queryImpl(1, R - 1, 1);
    return res;
}
int w[size], heid, hc;
struct Info {
    int ecnt, sumc, col, eid;
    Info() {}
    Info(int ecnt, int sumc)
        : ecnt(ecnt), sumc(sumc), col(hc), eid(heid) {}
    bool operator<(const Info& rhs) const {
        return col == rhs.col ? eid < rhs.eid :
                                col < rhs.col;
    }
} A[size];
int ccnt;
void DFS(int u, int p, int ccol, int ecnt, int sumc,
         bool changed) {
    A[++ccnt] =
        Info(ecnt, sumc + (changed ? w[ccol] : 0));
    ++ecnt;
    if(ecnt <= R) {
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(!flag[v] && v != p) {
                bool diff = E[i].c != ccol;
                DFS(v, u, E[i].c, ecnt,
                    sumc + (changed && diff ? w[ccol] :
                                              0),
                    changed | diff);
            }
        }
    }
}
int ans = -(1 << 30);
void solveEid(int l, int r, int cw) {
    for(int i = l; i <= r; ++i) {
        int lv = std::max(L - A[i].ecnt, 1),
            rv = R - A[i].ecnt;
        if(rv >= 1) {
            int off = A[i].sumc + cw;
            ans =
                std::max(ans, off + query(T2, lv, rv,
                                          ans - off));
        }
    }
    for(int i = l; i <= r; ++i)
        if(A[i].ecnt < R)
            modify(T2, A[i].ecnt, A[i].sumc);
}
void solveCol(int l, int r) {
    int cw = w[A[l].col];
    for(int i = l; i <= r; ++i) {
        int lv = std::max(L - A[i].ecnt, 1),
            rv = R - A[i].ecnt;
        if(rv >= 1) {
            int off = A[i].sumc + cw;
            ans =
                std::max(ans, off + query(T1, lv, rv,
                                          ans - off));
        }
    }
    for(int i = l; i <= r; ++i)
        if(A[i].ecnt < R)
            modify(T1, A[i].ecnt, A[i].sumc + cw);
    ++T2[0].ts;
    for(int cr = l, cl = l; cr <= r; ++cr) {
        if(A[cr].eid != A[cr + 1].eid) {
            solveEid(cl, cr, cw);
            cl = cr + 1;
        }
    }
}
void solve(int u) {
    ccnt = 0, ++T1[0].ts;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!flag[v]) {
            hc = E[i].c, heid = i;
            DFS(v, u, hc, 1, 0, false);
        }
    }
    for(int i = 1; i <= ccnt; ++i)
        if(L <= A[i].ecnt && A[i].ecnt <= R)
            ans =
                std::max(ans, A[i].sumc + w[A[i].col]);
    std::sort(A + 1, A + ccnt + 1);
    A[ccnt + 1].col = A[ccnt + 1].eid = -1;
    for(int r = 1, l = 1; r <= ccnt; ++r) {
        if(A[r].col != A[r + 1].col) {
            solveCol(l, r);
            l = r + 1;
        }
    }
}
void divide(int u) {
    flag[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!flag[v])
            divide(getRoot(v, siz[v]));
    }
}
int main() {
    IO::init();
    int n = read();
    int m = read();
    L = read();
    R = read();
    for(int i = 1; i <= m; ++i)
        w[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int c = read();
        addEdge(u, v, c);
        addEdge(v, u, c);
    }
    divide(getRoot(1, n));
    printf("%d\n", ans);
    return 0;
}
