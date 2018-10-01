#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
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
#define asInt64(x) static_cast<Int64>(x)
const int size = 200005, maxM = 400005;
struct Edge {
    int to, next, w;
} E[maxM * 2];
int last[size], cnt;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u], E[cnt].w = w;
    last[u] = cnt;
}
void initGraph(int n) {
    cnt = 0;
    memset(last, 0, sizeof(int) * (n + 1));
}
struct Node {
    int id;
    Int64 dis;
    Node(int id, Int64 dis) : id(id), dis(dis) {}
    bool operator<(const Node& rhs) const {
        return dis > rhs.dis;
    }
};
Int64 dis[size * 2];
void SSSP(int n) {
    std::priority_queue<Node> heap;
    memset(dis, 0x3f, sizeof(Int64) * (n + 1));
    dis[1] = 0;
    heap.push(Node(1, 0));
    while(heap.size()) {
        int u = heap.top().id;
        Int64 ud = heap.top().dis;
        heap.pop();
        if(dis[u] == ud) {
            for(int i = last[u]; i; i = E[i].next) {
                int v = E[i].to;
                Int64 vd = ud + E[i].w;
                if(vd < dis[v]) {
                    dis[v] = vd;
                    heap.push(Node(v, vd));
                }
            }
        }
    }
}
struct Info {
    int u, v, a;
    bool operator<(const Info& rhs) const {
        return a > rhs.a;
    }
};
class Tree {
private:
    struct Edge {
        int to, next;
    } TE[size * 2];
    int tlast[size * 2], tcnt;
    int fa[size * 2];
    void addEdge(int u, int v) {
        fa[v] = u;
        ++tcnt;
        TE[tcnt].to = v, TE[tcnt].next = tlast[u];
        tlast[u] = tcnt;
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    int p[size * 2][20], a[size * 2], h[size * 2],
        hend;
    void DFS(int u) {
        for(int i = 1; i <= hend; ++i)
            p[u][i] = p[p[u][i - 1]][i - 1];
        for(int i = tlast[u]; i; i = TE[i].next) {
            int v = TE[i].to;
            p[v][0] = u;
            DFS(v);
        }
    }

public:
    void init(Info* A, int n, int m) {
        int siz = sizeof(int) * (2 * n + 1);
        memset(fa, 0, siz);
        memset(tlast, 0, siz);
        memset(h, 0, sizeof(int) * (n + 1));
        tcnt = 0;
        std::sort(A, A + m);
        int icnt = n, end = 2 * n - 1;
        a[0] = -1;
        for(int i = 0; i < m; ++i) {
            int fu = find(A[i].u), fv = find(A[i].v);
            if(fu != fv) {
                int id = ++icnt;
                a[id] = A[i].a;
                dis[id] = std::min(dis[fu], dis[fv]);
                addEdge(id, fu);
                addEdge(id, fv);
                h[id] = std::max(h[fu], h[fv]) + 1;
                if(icnt == end)
                    break;
            }
        }
        hend = 0;
        while((1 << (hend + 1)) < h[icnt] + 1)
            ++hend;
        DFS(icnt);
    }
    Int64 query(int u, int k) {
        for(int i = hend; i >= 0; --i) {
            int fu = p[u][i];
            if(a[fu] > k)
                u = fu;
        }
        return dis[u];
    }
} T;
Info A[maxM];
void foo() {
    int n = read();
    int m = read();
    initGraph(n);
    for(int i = 0; i < m; ++i) {
        int u = read();
        int v = read();
        int l = read();
        int a = read();
        addEdge(u, v, l);
        addEdge(v, u, l);
        A[i].u = u, A[i].v = v, A[i].a = a;
    }
    SSSP(n);
    T.init(A, n, m);
    int q = read();
    int k = read();
    int s = read();
    Int64 lastAns = 0;
    while(q--) {
        int v = (read() + lastAns - 1) % n + 1;
        int p = (read() + lastAns) % (s + 1);
        Int64 res = T.query(v, p);
        printf("%lld\n", res);
        if(k)
            lastAns = res;
    }
}
int main() {
    int t = read();
    while(t--)
        foo();
    return 0;
}
