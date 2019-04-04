#include <algorithm>
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
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int d[size], p[size], son[size], siz[size];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u]) {
            p[v] = u;
            d[v] = d[u] + 1;
            buildTree(v);
            siz[u] += siz[v];
            if(siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}
int top[size], icnt = 0, id[size], w[size], idw[size];
void buildChain(int u) {
    id[u] = ++icnt;
    idw[icnt] = w[u];
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
    int siz, c[2];
} T[size * 35];
int ncnt = 0;
int insert(int src, int x, int d = 30) {
    int id = ++ncnt;
    T[id] = T[src];
    ++T[id].siz;
    if(d >= 0) {
        int& c = T[id].c[(x >> d) & 1];
        c = insert(c, x, d - 1);
    }
    return id;
}
int query(int a, int b, int base, int d = 30) {
    if(d == -1)
        return 0;
    int bit = 1 ^ ((base >> d) & 1);
    int bsiz = T[T[b].c[bit]].siz - T[T[a].c[bit]].siz;
    if(bsiz)
        return 1 << d | query(T[a].c[bit], T[b].c[bit],
                              base, d - 1);
    return query(T[a].c[bit ^ 1], T[b].c[bit ^ 1],
                 base, d - 1);
}
int root[size];
int queryChain(int u, int v, int base) {
    int ans = 0;
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]])
            std::swap(u, v);
        ans = std::max(ans, query(root[id[top[u]] - 1],
                                  root[id[u]], base));
        u = p[top[u]];
    }
    if(d[u] < d[v])
        std::swap(u, v);
    ans = std::max(ans, query(root[id[v] - 1],
                              root[id[u]], base));
    return ans;
}
int main() {
    int n = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        w[i] = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    for(int i = 1; i <= n; ++i)
        root[i] = insert(root[i - 1], idw[i]);
    while(q--) {
        int t = read();
        int u = read();
        int v = read();
        if(t == 1) {
            printf("%d\n",
                   query(root[id[u] - 1],
                         root[id[u] + siz[u] - 1], v));
        } else
            printf("%d\n", queryChain(u, v, read()));
    }
    return 0;
}
