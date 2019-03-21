#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
namespace IO {
    char in[1 << 26];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 23], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
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
void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 200005;
namespace SSSP {
    struct Edge {
        int to, nxt, w;
    } E[size * 4];
    int last[size], cnt;
    void reset(int n) {
        memset(last + 1, 0, sizeof(int) * n);
        cnt = 0;
    }
    void addEdge(int u, int v, int w) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u],
        E[cnt].w = w;
        last[u] = cnt;
    }
    struct Node {
        int u, d;
        Node(int u, int d) : u(u), d(d) {}
        bool operator<(const Node& rhs) const {
            return d > rhs.d;
        }
    };
    int dis[size * 2];
    void SSSP(int n) {
        memset(dis + 1, 0x7f, sizeof(int) * n);
        std::priority_queue<Node> heap;
        dis[1] = 0;
        heap.push(Node(1, 0));
        while(heap.size()) {
            int u = heap.top().u;
            int ud = heap.top().d;
            heap.pop();
            if(ud != dis[u])
                continue;
            for(int i = last[u]; i; i = E[i].nxt) {
                int v = E[i].to;
                int dv = ud + E[i].w;
                if(dv < dis[v]) {
                    dis[v] = dv;
                    heap.push(Node(v, dv));
                }
            }
        }
    }
}
namespace Tree {
    struct Edge {
        int to, nxt;
    } E[size * 2];
    int last[size * 2], cnt;
    void reset(int n) {
        cnt = 0;
        memset(last + 1, 0, sizeof(int) * n);
    }
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
    int p[size * 2][20], A[size * 2];
    void DFS(int u) {
        for(int i = 1; i < 20; ++i)
            p[u][i] = p[p[u][i - 1]][i - 1];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            p[v][0] = u;
            DFS(v);
        }
    }
    int query(int u, int a) {
        for(int i = 19; i >= 0; --i) {
            int cp = p[u][i];
            if(A[cp] > a)
                u = cp;
        }
        return u;
    }
}
struct Edge {
    int u, v, a;
    bool operator<(const Edge& rhs) const {
        return a > rhs.a;
    }
} E[size * 2];
int fa[size], rk[size], rt[size];
int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}
int merge(int u, int v) {
    if(rk[u] < rk[v]) {
        fa[u] = v;
        return v;
    }
    fa[v] = u;
    if(rk[u] == rk[v])
        ++rk[u];
    return u;
}
void foo() {
    int n = read();
    int m = read();
    SSSP::reset(n);
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        int w = read();
        int a = read();
        SSSP::addEdge(u, v, w);
        SSSP::addEdge(v, u, w);
        E[i].u = u, E[i].v = v, E[i].a = a;
    }
    SSSP::SSSP(n);
    std::sort(E + 1, E + m + 1);
    int icnt = n;
    memset(fa + 1, 0, sizeof(int) * n);
    memset(rt + 1, 0, sizeof(int) * n);
    memset(rk + 1, 0, sizeof(int) * n);
    Tree::reset(2 * n);
    for(int i = 1, ecnt = n - 1; i <= m; ++i) {
        int u = find(E[i].u), v = find(E[i].v);
        if(u != v) {
            int id = ++icnt;
            int nrt = merge(u, v);
            u = (rt[u] ? rt[u] : u);
            v = (rt[v] ? rt[v] : v);
            rt[nrt] = id;
            Tree::A[id] = E[i].a;
            SSSP::dis[id] =
                std::min(SSSP::dis[u], SSSP::dis[v]);
            Tree::addEdge(id, u);
            Tree::addEdge(id, v);
            if(--ecnt == 0)
                break;
        }
    }
    Tree::DFS(icnt);
    int q = read();
    int k = read();
    int s = read();
    int lastAns = 0;
    for(int i = 1; i <= q; ++i) {
        int v = (read() + lastAns - 1) % n + 1;
        int a = (static_cast<long long>(read()) +
                 lastAns) %
            (s + 1);
        int p = Tree::query(v, a);
        int res = SSSP::dis[p];
        write(res);
        IO::putc('\n');
        if(k)
            lastAns = res;
    }
}
int main() {
    freopen("return.in", "r", stdin);
    freopen("return.out", "w", stdout);
    IO::init();
    int t = read();
    for(int i = 1; i <= t; ++i)
        foo();
    IO::uninit();
    return 0;
}
