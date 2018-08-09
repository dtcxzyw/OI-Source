//TODO:3783
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
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
template <int maxn>
struct GA {
    struct Edge {
        int to, nxt;
    } E[2 * maxn];
    int last[maxn], cnt;
    void reset(int siz) {
        cnt = 0;
        memset(last + 1, 0, sizeof(int) * siz);
    }
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
};
const int tsiz = 20005;
GA<tsiz> ga;
int icnt, A[tsiz * 2][18], L[tsiz], d[tsiz];
void DFS(int u) {
    A[++icnt][0] = u;
    L[u] = icnt;
    for (int i = ga.last[u]; i; i = ga.E[i].nxt) {
        int v = ga.E[i].to;
        if (!L[v]) {
            d[v] = d[u] + 1;
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
template <int maxn>
struct GB {
    struct Edge {
        int to, nxt, w, d;
    } E[maxn];
    int last[maxn], cnt;
    void reset(int siz) {
        cnt = 0;
        memset(last + 1, 0, sizeof(int) * siz);
    }
    void addEdge(int u, int v, int w, int d) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w, E[cnt].d = d;
        last[u] = cnt;
    }
};
const int size = 50005;
GB<size> gb;
Int64 dis[size];
Int64 getDis(std::map<Int64, Int64> &t, Int64 u) {
    std::map<Int64, Int64>::iterator it = t.find(u);
    if (it != t.end())
        return it->second;
    else
        return 0x3f3f3f3f3f3f3f3f;
}
struct Node {
    Int64 u, dis;
    Node(Int64 u, Int64 s, Int64 dis) : u(u << 32 | s), dis(dis) {}
    void decode(int &uid, int &s) const {
        uid = u >> 32;
        s = u & ((1LL << 32) - 1);
    }
    bool operator<(const Node &rhs) const {
        return dis > rhs.dis;
    }
};
void SSSP(int n) {
    memset(dis + 1, 0x3f, sizeof(Int64) * n);
    std::map<Int64, Int64> sdis;
    std::priority_queue<Node> heap;
    heap.push(Node(1, 0, 0));
    sdis[1LL << 32] = 0;
    dis[1] = 0;
    while (heap.size()) {
        Node node = heap.top();
        heap.pop();
        if (getDis(sdis, node.u) != node.dis) continue;
        int u, s;
        node.decode(u, s);
        for (int i = gb.last[u]; i; i = gb.E[i].nxt) {
            int v = gb.E[i].to;
            Int64 cd = node.dis + gb.E[i].w + d[getLca(s, gb.E[i].d)];
            Node vn(v, gb.E[i].d, cd);
            if (getDis(sdis, vn.u) > cd) {
                dis[v] = std::min(dis[v], cd);
                heap.push(vn);
                sdis[vn.u] = cd;
            }
        }
    }
}
void foo() {
    int n = read();
    int m = read();
    int k = read();
    gb.reset(n);
    while (m--) {
        int u = read();
        int v = read();
        int w = read();
        int d = read();
        gb.addEdge(u, v, w, d);
    }
    ga.reset(k);
    icnt = 0;
    memset(L + 1, 0, sizeof(int) * k);
    while (--k) {
        int u = read();
        int v = read();
        int c = read();
        ga.addEdge(u, v);
        ga.addEdge(v, u);
    }
    d[1] = 0;
    DFS(1);
    buildST();
    SSSP(n);
    for (int i = 2; i <= n; ++i)
        printf("%lld\n", dis[i]);
}
int main() {
    int t = read();
    while (t--) foo();
    return 0;
}
