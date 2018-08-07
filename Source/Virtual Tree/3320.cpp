#include <algorithm>
#include <cstdio>
#include <set>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
typedef long long Int64;
const int size = 100005;
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int icnt = 0, A[size * 2][18], L[size] = {}, d[size];
Int64 len[size];
void DFS(int u) {
    A[++icnt][0] = u;
    L[u] = icnt;
    for (int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if (!L[v]) {
            d[v] = d[u] + 1;
            len[v] = len[u] + E[i].w;
            DFS(v);
            A[++icnt][0] = u;
        }
    }
}
int choose(int u, int v) {
    return d[u] < d[v] ? u : v;
}
void buildST() {
    for (int i = 1; i < 18; ++i) {
        int off = 1 << (i - 1), end = icnt - (1 << i) + 1;
        for (int j = 1; j <= end; ++j)
            A[j][i] = choose(A[j][i - 1], A[j + off][i - 1]);
    }
}
int ilg2(int x) {
    return 31 - __builtin_clz(x);
}
int getLca(int u, int v) {
    int l = L[u], r = L[v];
    if (l > r) std::swap(l, r);
    int p = ilg2(r - l + 1);
    return choose(A[l][p], A[r - (1 << p) + 1][p]);
}
Int64 getDis(int u, int v) {
    return len[u] + len[v] - (len[getLca(u, v)] << 1);
}
struct Comparer {
    bool operator()(int a, int b) const {
        return L[a] < L[b];
    }
};
typedef std::set<int, Comparer> Tree;
typedef Tree::iterator IterT;
int prev(const Tree &tree, IterT it) {
    return it == tree.begin() ? *tree.rbegin() : *(--it);
}
int next(const Tree &tree, IterT it) {
    ++it;
    return *(it == tree.end() ? tree.begin() : it);
}
bool flag[size] = {};
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    DFS(1);
    buildST();
    Tree tree;
    Int64 res = 0;
    while (m--) {
        int u = read();
        flag[u] ^= 1;
        IterT it = tree.insert(u).first;
        if (tree.size() >= 2) {
            int l = prev(tree, it), r = next(tree, it);
            Int64 delta = getDis(l, u) + getDis(u, r) - getDis(l, r);
            if (flag[u])
                res += delta;
            else
                res -= delta;
        }
        if (!flag[u]) tree.erase(it);
        printf("%lld\n", res);
    }
    return 0;
}
