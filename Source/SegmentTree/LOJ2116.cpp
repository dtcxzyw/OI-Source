#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long Int64;
#define asInt64 static_cast<Int64>
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
const int size = 150005;
int A[size], B[size], SC[size], siz;
void add(int u) {
    while(u <= siz) {
        ++SC[u];
        u += u & -u;
    }
}
Int64 query(int u) {
    int res = 0;
    while(u) {
        res += SC[u];
        u -= u & -u;
    }
    return res;
}
Int64 SD[size];
void addDep(int u, Int64 d) {
    while(u <= siz) {
        SD[u] += d;
        u += u & -u;
    }
}
Int64 queryDep(int u) {
    Int64 res = 0;
    while(u) {
        res += SD[u];
        u -= u & -u;
    }
    return res;
}
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int p[size], d[size], son[size], ew[size], sew[size];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u]) {
            d[v] = d[u] + E[i].w;
            p[v] = u;
            ew[v] = E[i].w;
            int vsiz = buildTree(v);
            siz += vsiz;
            if(vsiz > msiz)
                msiz = vsiz, son[u] = v;
        }
    }
    return siz;
}
int id[size], top[size], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
    sew[icnt] = ew[u];
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
struct Node {
    Int64 sum;
    int l, r, tag, ts;
} T[size * 40];
int tcnt = 0, cts = 0;
int cloneNode(int src) {
    if(T[src].ts == cts)
        return src;
    int id = ++tcnt;
    T[id] = T[src];
    T[id].ts = cts;
    return id;
}
int nl, nr;
int modify(int l, int r, int src) {
    int id = cloneNode(src);
    if(nl <= l && r <= nr) {
        T[id].sum += sew[r] - sew[l - 1];
        ++T[id].tag;
    } else {
        int m = (l + r) >> 1;
        if(nl <= m)
            T[id].l = modify(l, m, T[id].l);
        if(m < nr)
            T[id].r = modify(m + 1, r, T[id].r);
        T[id].sum = T[T[id].l].sum + T[T[id].r].sum +
            T[id].tag * asInt64(sew[r] - sew[l - 1]);
    }
    return id;
}
Int64 res;
void query(int l, int r, int b, int e) {
    if(T[e].sum == T[b].sum)
        return;
    if(nl <= l && r <= nr)
        res += T[e].sum - T[b].sum;
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            query(l, m, T[b].l, T[e].l);
        if(m < nr)
            query(m + 1, r, T[b].r, T[e].r);
        res += asInt64(sew[std::min(nr, r)] -
                       sew[std::max(nl, l) - 1]) *
            (T[e].tag - T[b].tag);
    }
}
int modifyChain(int u, int rt) {
    while(top[u]) {
        nl = id[top[u]], nr = id[u];
        rt = modify(1, icnt, rt);
        u = p[top[u]];
    }
    return rt;
}
Int64 queryChain(int u, int b, int e) {
    res = 0;
    while(top[u]) {
        nl = id[top[u]], nr = id[u];
        query(1, icnt, b, e);
        u = p[top[u]];
    }
    return res;
}
int ord[size], root[size];
bool cmp(int a, int b) {
    return A[a] < A[b];
}
int main() {
    int n = read();
    int q = read();
    int mod = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    memcpy(B + 1, A + 1, sizeof(int) * n);
    std::sort(B + 1, B + n + 1);
    siz = std::unique(B + 1, B + n + 1) - (B + 1);
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    for(int i = 1; i <= n; ++i) {
        A[i] = std::lower_bound(B + 1, B + siz + 1,
                                A[i]) -
            B;
        add(A[i]);
        addDep(A[i], d[i]);
        ord[i] = i;
    }
    for(int i = 1; i <= n; ++i)
        sew[i] += sew[i - 1];
    std::sort(ord + 1, ord + n + 1, cmp);
    A[0] = -1;
    for(int i = 1; i <= n; ++i) {
        int u = ord[i];
        int ca = A[u];
        if(ca != A[ord[i - 1]]) {
            ++cts;
            root[ca] = root[ca - 1];
        }
        root[ca] = modifyChain(u, root[ca]);
    }
    Int64 lastAns = 0;
    for(int i = 1; i <= q; ++i) {
        int u = read();
        int l = (read() + lastAns) % mod;
        int r = (read() + lastAns) % mod;
        if(l > r)
            std::swap(l, r);
        int lp =
            std::lower_bound(B + 1, B + siz + 1, l) -
            B - 1;
        int rp =
            std::upper_bound(B + 1, B + siz + 1, r) -
            B - 1;
        Int64 ans = d[u] * (query(rp) - query(lp)) +
            (queryDep(rp) - queryDep(lp)) -
            2 * queryChain(u, root[lp], root[rp]);
        printf("%lld\n", ans);
        lastAns = ans;
    }
    return 0;
}
