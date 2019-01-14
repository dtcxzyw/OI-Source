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
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 1000005;
int d[size], L[size];
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
    int p[size], icnt = 0, A[size * 2][21];
    void DFS(int u) {
        L[u] = ++icnt;
        A[icnt][0] = u;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(v != p[u]) {
                d[v] = d[u] + 1;
                p[v] = u;
                DFS(v);
                A[++icnt][0] = u;
            }
        }
    }
    int choose(int a, int b) {
        return d[a] < d[b] ? a : b;
    }
    void build() {
        for(int i = 1; i <= 20; ++i) {
            int off = 1 << (i - 1),
                end = icnt - (1 << i) + 1;
            for(int j = 1; j <= end; ++j)
                A[j][i] = choose(A[j][i - 1],
                                 A[j + off][i - 1]);
        }
    }
    int getHighest(int x) {
        for(int i = 1; i <= 16; i <<= 1)
            x |= x >> i;
        return x ^ (x >> 1);
    }
    const unsigned int fac = 0x077CB531U;
    unsigned int LUT[32];
    int ilg2(int n) {
        unsigned int x = getHighest(n);
        return LUT[(x * fac) >> 27];
    }
    void init(int n) {
        for(int i = 1; i < n; ++i) {
            int u = read();
            int v = read();
            addEdge(u, v);
            addEdge(v, u);
        }
        DFS(1);
        build();
        for(int i = 0; i <= 20; ++i) {
            unsigned int x = 1U << i;
            LUT[(x * fac) >> 27] = i;
        }
    }
    int getLCA(int u, int v) {
        int l = L[u], r = L[v];
        if(l > r)
            std::swap(l, r);
        int p = ilg2(r - l + 1);
        return choose(A[l][p], A[r - (1 << p) + 1][p]);
    }
}
struct Edge {
    int to, nxt, w;
} E[size];
int last[size], cnt, ts[size], cts;
int getLast(int u) {
    if(ts[u] != cts)
        last[u] = 0, ts[u] = cts;
    return last[u];
}
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = getLast(u),
    E[cnt].w = d[v] - d[u];
    last[u] = cnt;
}
const int inf = 1 << 25;
struct Res {
    int maxl, minl, siz;
    Res(bool flag)
        : maxl(flag ? 0 : -inf), minl(flag ? 0 : inf),
          siz(flag) {}
    void update(const Res& child) {
        maxl = std::max(maxl, child.maxl);
        minl = std::min(minl, child.minl);
        siz += child.siz;
    }
};
int maxl, minl, n;
Int64 sum;
bool flag[size];
Res DFS(int u) {
    Res res(flag[u]);
    for(int i = getLast(u); i; i = E[i].nxt) {
        int v = E[i].to, w = E[i].w;
        Res vr = DFS(v);
        vr.maxl += w, vr.minl += w;
        maxl = std::max(maxl, res.maxl + vr.maxl);
        minl = std::min(minl, res.minl + vr.minl);
        sum += asInt64(w) * vr.siz * (n - vr.siz);
        res.update(vr);
    }
    return res;
}
bool cmp(int a, int b) {
    return L[a] < L[b];
}
int A[size], st[size];
void foo() {
    n = read();
    cnt = 0;
    for(int i = 0; i < n; ++i) {
        A[i] = read();
        flag[A[i]] = true;
    }
    std::sort(A, A + n, cmp);
    int top = 1;
    st[top] = A[0];
    for(int i = 1; i < n; ++i) {
        int u = A[i];
        int lca = Graph::getLCA(u, st[top]);
        while(top > 1 && d[st[top - 1]] > d[lca]) {
            addEdge(st[top - 1], st[top]);
            --top;
        }
        if(d[lca] < d[st[top]]) {
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
    maxl = -inf, minl = inf, sum = 0;
    DFS(st[1]);
    printf("%lld %d %d\n", sum, minl, maxl);
    for(int i = 0; i < n; ++i)
        flag[A[i]] = false;
    ++cts;
}
int main() {
    int n = read();
    Graph::init(n);
    int q = read();
    while(q--)
        foo();
    return 0;
}
