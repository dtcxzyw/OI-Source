#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 2000005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int siz[size], p[size], d[size], son[size];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(p[u] == v)
            continue;
        p[v] = u, d[v] = d[u] + 1;
        buildTree(v);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]])
            son[u] = v;
    }
}
int top[size], id[size], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
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
int getLCA(int u, int v) {
    while(top[u] != top[v]) {
        if(d[top[u]] < d[top[v]])
            std::swap(u, v);
        u = p[top[u]];
    }
    return d[u] < d[v] ? u : v;
}
void addImpl(int* S, int x, int n, int val) {
    while(x <= n) {
        S[x] += val;
        x += x & -x;
    }
}
int queryImpl(int* S, int x) {
    int res = 0;
    while(x) {
        res += S[x];
        x -= x & -x;
    }
    return res;
}
int A[size], B[size];
void add(int x, int n, int val) {
    addImpl(A, x, n, val);
    addImpl(B, x, n, val * x);
}
int query(int x) {
    return (x + 1) * queryImpl(A, x) - queryImpl(B, x);
}
int query(int l, int r) {
    return query(r) - query(l - 1);
}
int queryChain(int u, int v) {
    int res = 0;
    while(top[u] != top[v]) {
        res += query(id[top[v]], id[v]);
        v = p[top[v]];
    }
    res += query(id[u] + 1, id[v]);
    return res;
}
int st[100], P[15], X[15][2], cp[size], val[size];
bool cmp(int a, int b) {
    return id[a] < id[b];
}
bool colA[size], colB[size];
void link(int p, int u) {
    cp[u] = p;
    val[u] = queryChain(p, u);
    colA[u] = colB[u] = false;
}
int solve() {
    int k = read();
    for(int i = 0; i < k; ++i) {
        X[i][0] = read();
        X[i][1] = read();
    }
    int c = k * 2;
    memcpy(P, X, sizeof(int) * c);
    std::sort(P, P + c, cmp);
    int top = 1;
    st[top] = P[0];
    for(int i = 1; i < c; ++i) {
        int u = P[i];
        int lca = getLCA(st[top], u);
        while(top > 1 && d[st[top - 1]] > d[lca]) {
            link(st[top - 1], st[top]);
            --top;
        }
        if(d[st[top]] > d[lca]) {
            link(lca, st[top]);
            --top;
        }
        if(top == 0 || d[st[top]] < d[lca])
            st[++top] = lca;
        st[++top] = u;
    }
    while(top > 1) {
        link(st[top - 1], st[top]);
        --top;
    }
    cp[st[top]] = 0;
    val[st[top]] = query(id[st[top]], id[st[top]]);
    colA[st[top]] = colB[st[top]] = false;
    int res = 0;
    for(int i = 0; i < k; ++i) {
        int u = X[i][0], v = X[i][1];
        while(u != v) {
            if(d[u] < d[v])
                std::swap(u, v);
            if(!colA[u]) {
                res += val[u];
                if(colB[u])
                    res -= query(id[u], id[u]);
                colA[u] = true;
            }
            u = cp[u];
        }
        if(!colB[u] && !colA[u]) {
            res += query(id[u], id[u]);
            colB[u] = true;
        }
    }
    return res;
}
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    int q = read();
    for(int t = 1; t <= q; ++t) {
        if(read())
            printf("%d\n", solve() & 2147483647);
        else {
            int u = read();
            int delta = read();
            add(id[u], n, delta);
            add(id[u] + siz[u], n, -delta);
        }
    }
    return 0;
}
