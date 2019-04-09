#include <algorithm>
#include <cstdio>
#include <random>
namespace IO {
    char in[1 << 23];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
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
int p[size], d[size], son[size], siz[size];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p[u]) {
            p[v] = u, d[v] = d[u] + 1;
            buildTree(v);
            siz[u] += siz[v];
            if(siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}
int id[size], top[size], icnt = 0;
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
int S[size], TS[size], cts = 0;
int& load(int x) {
    if(TS[x] != cts)
        TS[x] = cts, S[x] = 0;
    return S[x];
}
void add(int x, int op) {
    while(x <= icnt) {
        load(x) += op;
        x += x & -x;
    }
}
void addChain(int u, int v, int op) {
    add(id[u], op);
    add(id[v], op);
    int lca = getLCA(u, v);
    add(id[lca], -op);
    if(p[lca])
        add(id[p[lca]], -op);
}
int query(int x) {
    int res = 0;
    while(x) {
        res += load(x);
        x -= x & -x;
    }
    return res;
}
int queryChain(int u) {
    return query(id[u] + siz[u] - 1) -
        query(id[u] - 1);
}
struct Event {
    int op, u, v, w;
} A[size * 2];
int X[size * 2], ans[size * 2];
void solve(int l, int r, int b, int e) {
    if(b > e)
        return;
    if(l == r) {
        for(int i = b; i <= e; ++i)
            if(A[i].op == 2)
                ans[A[i].v] = l;
    } else {
        int m = (l + r) >> 1;
        ++cts;
        int cur = 0;
        auto lambda = [&cur, m](const Event& e) {
            switch(e.op) {
                case 0: {
                    if(e.w > m) {
                        ++cur;
                        addChain(e.u, e.v, 1);
                        return false;
                    }
                } break;
                case 1: {
                    if(e.w > m) {
                        --cur;
                        addChain(e.u, e.v, -1);
                        return false;
                    }
                } break;
                case 2: {
                    return queryChain(e.u) == cur;
                } break;
            }
            return true;
        };
        int pos = std::stable_partition(
                      A + b, A + e + 1, lambda) -
            A;
        solve(l, m, b, pos - 1);
        solve(m + 1, r, pos, e);
    }
}
int main() {
    IO::init();
    int n = read();
    int m = read();
    std::random_device reng;
    int rt = reng() % n + 1;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    buildTree(rt);
    top[rt] = rt;
    buildChain(rt);
    int siz = 0, ocnt = 0;
    for(int i = 1; i <= m; ++i) {
        A[i].op = read();
        switch(A[i].op) {
            case 0: {
                A[i].u = read();
                A[i].v = read();
                A[i].w = read();
                X[++siz] = A[i].w;
            } break;
            case 1: {
                int t = read();
                A[i] = A[t];
                A[i].op = 1;
            } break;
            case 2: {
                A[i].u = read();
                A[i].v = ++ocnt;
            } break;
        }
    }
    std::sort(X + 1, X + siz + 1);
    siz = std::unique(X + 1, X + siz + 1) - (X + 1);
    for(int i = 1; i <= m; ++i)
        if(A[i].op < 2)
            A[i].w = std::lower_bound(
                         X + 1, X + siz + 1, A[i].w) -
                X;
    solve(0, siz, 1, m);
    X[0] = -1;
    for(int i = 1; i <= ocnt; ++i)
        printf("%d\n", X[ans[i]]);
    return 0;
}
