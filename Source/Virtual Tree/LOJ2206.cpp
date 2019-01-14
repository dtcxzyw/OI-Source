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
const int size = 300005, inf = 1 << 28;
int d[size], id[size], p[size][20], siz[size];
namespace Graph {
    struct Edge {
        int to, nxt;
    } E[size * 2];
    int last[size], cnt = 0;
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
    int icnt = 0;
    void DFS(int u) {
        id[u] = ++icnt;
        siz[u] = 1;
        for(int i = 1; i < 20; ++i)
            p[u][i] = p[p[u][i - 1]][i - 1];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(v != p[u][0]) {
                d[v] = d[u] + 1;
                p[v][0] = u;
                DFS(v);
                siz[u] += siz[v];
            }
        }
    }
    int getLCA(int u, int v) {
        if(d[u] < d[v])
            std::swap(u, v);
        int delta = d[u] - d[v];
        for(int i = 0; i < 20; ++i)
            if(delta & (1 << i))
                u = p[u][i];
        if(u == v)
            return u;
        for(int i = 19; i >= 0; --i)
            if(p[u][i] != p[v][i])
                u = p[u][i], v = p[v][i];
        return p[u][0];
    }
    void init(int n) {
        for(int i = 1; i < n; ++i) {
            int u = read();
            int v = read();
            addEdge(u, v);
            addEdge(v, u);
        }
        DFS(1);
    }
}
struct Chain {
    int u, len;
    Chain() {}
    Chain(int u, int len) : u(u), len(len) {}
    Chain operator+(int w) const {
        return Chain(u, len + w);
    }
    bool operator<(const Chain& rhs) const {
        return len != rhs.len ? len < rhs.len :
                                u < rhs.u;
    }
} chain[size];
int C[size];
struct Edge {
    int to, nxt;
} E[size];
int last[size], lts[size], cnt, ts = 0;
int getLast(int u) {
    if(lts[u] != ts)
        lts[u] = ts, last[u] = 0;
    return last[u];
}
int jump(int u, int v) {
    int delta = d[v] - d[u] - 1;
    for(int i = 19; i >= 0; --i)
        if(delta & (1 << i))
            v = p[v][i];
    return v;
}
void addEdge(int u, int v) {
    C[u] = C[v] = 0;
    chain[u] = chain[v] = Chain(0, inf);
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = getLast(u);
    last[u] = cnt;
}
void DFSA(int u) {
    for(int i = getLast(u); i; i = E[i].nxt) {
        int v = E[i].to;
        DFSA(v);
        chain[u] = std::min(chain[u],
                            chain[v] + (d[v] - d[u]));
    }
}
void DFSB(int u, Chain fc) {
    chain[u] = std::min(chain[u], fc);
    for(int i = getLast(u); i; i = E[i].nxt) {
        int v = E[i].to;
        DFSB(v, chain[u] + (d[v] - d[u]));
    }
}
void DFSC(int u) {
    int rem = siz[u];
    for(int i = getLast(u); i; i = E[i].nxt) {
        int v = E[i].to;
        DFSC(v);
        rem -= siz[jump(u, v)];
    }
    C[chain[u].u] += rem;
}
void calcEdge(int u, int v) {
    if(chain[u].u == chain[v].u)
        C[chain[u].u] += siz[jump(u, v)] - siz[v];
    else {
        int delta = d[v] - d[u], x = v;
        Chain cu = chain[u] + delta, cv = chain[v];
        for(int i = 19; i >= 0; --i) {
            int off = 1 << i;
            if(delta >= off) {
                int cp = p[x][i];
                Chain nu = cu + -off, nv = cv + off;
                if(nv < nu)
                    cu = nu, cv = nv, delta -= off,
                    x = cp;
            }
        }
        C[chain[u].u] += siz[jump(u, v)] - siz[x];
        C[chain[v].u] += siz[x] - siz[v];
    }
}
void DFSD(int u) {
    for(int i = getLast(u); i; i = E[i].nxt) {
        int v = E[i].to;
        calcEdge(u, v);
        DFSD(v);
    }
}
int st[size], A[size], B[size];
bool cmp(int a, int b) {
    return id[a] < id[b];
}
void foo() {
    ++ts, cnt = 0;
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    memcpy(B + 1, A + 1, sizeof(int) * n);
    std::sort(A + 1, A + n + 1, cmp);
    int top = 1;
    st[top] = A[1];
    for(int i = 2; i <= n; ++i) {
        int u = A[i], lca = Graph::getLCA(u, st[top]);
        while(top > 1 && d[st[top - 1]] > d[lca]) {
            addEdge(st[top - 1], st[top]);
            --top;
        }
        if(d[st[top]] > d[lca]) {
            addEdge(lca, st[top]);
            --top;
        }
        if(top == 0 || d[st[top]] < d[lca])
            st[++top] = lca;
        st[++top] = u;
    }
    while(top > 1) {
        addEdge(st[top - 1], st[top]);
        --top;
    }
    for(int i = 1; i <= n; ++i) {
        int u = A[i];
        chain[u] = Chain(u, 0);
    }
    DFSA(st[1]);
    DFSB(st[1], Chain(0, inf));
    DFSC(st[1]);
    Chain res = chain[st[1]];
    C[res.u] += siz[1] - siz[st[1]];
    DFSD(st[1]);
    for(int i = 1; i <= n; ++i) {
        int u = B[i];
        printf("%d ", C[u]);
    }
    putchar('\n');
}
int main() {
    int n = read();
    Graph::init(n);
    int q = read();
    while(q--)
        foo();
    return 0;
}
