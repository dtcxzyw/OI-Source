#include <algorithm>
#include <cstdio>
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
const int size = 300005, maxv = 2 * size;
struct G {
    struct Edge {
        int to, nxt;
    } E[size * 4];
    int last[maxv], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} A, B;
int dfn[size], fa[size], ncnt, ts = 0;
bool ring[size], fac[maxv];
void DFS(int u) {
    dfn[u] = ++ts;
    for(int i = A.last[u]; i; i = A.E[i].nxt) {
        int v = A.E[i].to;
        if(fa[u] == v)
            continue;
        if(dfn[v]) {
            if(dfn[v] < dfn[u]) {
                int id = ++ncnt;
                fac[id] = true;
                for(int j = u; j != v; j = fa[j]) {
                    ring[j] = true;
                    fac[j] = false;
                    B.addEdge(id, j);
                }
                B.addEdge(v, id);
                fac[v] = ring[v] = true;
            }
        } else {
            fa[v] = u;
            ring[u] = false;
            DFS(v);
            if(!ring[u]) {
                fac[u] = fac[v] = true;
                B.addEdge(u, v);
            }
        }
    }
}
int son[maxv], d[maxv], p[maxv];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        d[v] = d[u] + 1, p[v] = u;
        int vsiz = buildTree(v);
        siz += vsiz;
        if(vsiz > msiz)
            msiz = vsiz, son[u] = v;
    }
    return siz;
}
int top[maxv], id[maxv], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = B.last[u]; i; i = B.E[i].nxt) {
        int v = B.E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
const int mod = 998244353;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int S[maxv];
void modify(int x, int val) {
    while(x <= icnt) {
        S[x] = add(S[x], val);
        x += x & -x;
    }
}
int query(int x) {
    int res = 0;
    while(x) {
        res = add(res, S[x]);
        x -= x & -x;
    }
    return res;
}
int tag[maxv];
int main() {
    int n = read();
    int m = read();
    int q = read();
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        A.addEdge(u, v);
        A.addEdge(v, u);
    }
    ncnt = n;
    DFS(1);
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    for(int i = 1; i <= q; ++i)
        if(read()) {
            int u = read();
            int res = tag[u];
            if(fac[u])
                res = add(res, query(id[u]));
            else
                res = add(res, query(id[p[u]]));
            printf("%d\n", res);
        } else {
            int u = read();
            int v = read();
            int w = read() % mod;
            if(w < 0)
                w += mod;
            int nw = w ? mod - w : 0;
            while(top[u] != top[v]) {
                if(d[top[u]] < d[top[v]])
                    std::swap(u, v);
                modify(id[top[u]], w);
                modify(id[u] + 1, nw);
                u = p[top[u]];
            }
            if(d[u] < d[v])
                std::swap(u, v);
            modify(id[v], w);
            modify(id[u] + 1, nw);
            if(fac[v]) {
                if(v > n) {
                    int pv = p[v];
                    tag[pv] = add(tag[pv], w);
                }
            } else
                tag[v] = add(tag[v], w);
        }
    return 0;
}
