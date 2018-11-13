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
const int size = 100005, psiz = size << 3;
struct Edge {
    int to, nxt, w;
} E[size * 40];
int last[psiz], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
int iid[size << 2], oid[size << 2], pid[size],
    icnt = 0;
void build(int l, int r, int id) {
    if(l == r) {
        pid[l] = iid[id] = oid[id] = ++icnt;
    } else {
        iid[id] = ++icnt;
        oid[id] = ++icnt;
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        addEdge(iid[id], iid[id << 1], 0);
        addEdge(iid[id], iid[id << 1 | 1], 0);
        addEdge(oid[id << 1], oid[id], 0);
        addEdge(oid[id << 1 | 1], oid[id], 0);
    }
}
typedef void (*Func)(int u);
int nl, nr, p, w;
void funcIn(int u) {
    addEdge(p, iid[u], w);
}
void funcOut(int u) {
    addEdge(oid[u], p, w);
}
template <Func func>
void insert(int l, int r, int id) {
    if(nl <= l && r <= nr)
        func(id);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert<func>(ls);
        if(m < nr)
            insert<func>(rs);
    }
}
typedef long long Int64;
Int64 dis[psiz];
int q[psiz];
struct Info {
    int u;
    Int64 dis;
    Info(int u, Int64 dis) : u(u), dis(dis) {}
    bool operator<(const Info& rhs) const {
        return dis > rhs.dis;
    }
};
void SSSP(int s) {
    memset(dis + 1, 0x3f, sizeof(Int64) * icnt);
    dis[s] = 0;
    std::priority_queue<Info> heap;
    heap.push(Info(s, 0));
    while(heap.size()) {
        int u = heap.top().u;
        Int64 cd = heap.top().dis;
        heap.pop();
        if(dis[u] != cd)
            continue;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            Int64 nd = cd + E[i].w;
            if(dis[v] > nd) {
                dis[v] = nd;
                heap.push(Info(v, nd));
            }
        }
    }
}
int main() {
    int n = read();
    int q = read();
    int s = read();
    build(1, n, 1);
    while(q--) {
        int t = read();
        if(t == 1) {
            int u = read();
            int v = read();
            int w = read();
            addEdge(pid[u], pid[v], w);
        } else {
            p = pid[read()];
            nl = read();
            nr = read();
            w = read();
            if(t == 2)
                insert<funcIn>(1, n, 1);
            else
                insert<funcOut>(1, n, 1);
        }
    }
    SSSP(pid[s]);
    for(int i = 1; i <= n; ++i) {
        int u = pid[i];
        Int64 d = dis[u];
        if(d == 0x3f3f3f3f3f3f3f3f)
            d = -1;
        printf("%lld ", d);
    }
    return 0;
}
