#include <bitset>
#include <iostream>
#include <vector>
typedef std::bitset<1000> Bit;
const int size = 505;
struct Edge {
    int to, nxt;
    Bit w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, const Bit& w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
Bit dis[size];
void buildTree(int u, int p) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            dis[v] = dis[u] ^ E[i].w;
            buildTree(v, u);
        }
    }
}
int fa[size];
int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}
struct Info {
    int u, v;
    Bit w;
    Info() {}
    Info(int u, int v, const Bit& w)
        : u(u), v(v), w(w) {}
} A[3 * size];
std::vector<int> eid[size << 3];
void insert(int l, int r, int id, int nl, int nr,
            int e) {
    if(nl <= l && r <= nr)
        eid[id].push_back(e);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert(l, m, id << 1, nl, nr, e);
        if(m < nr)
            insert(m + 1, r, id << 1 | 1, nl, nr, e);
    }
}
struct Base {
    Bit A[1000];
    void insert(Bit x) {
        for(int i = 999; i >= 0; --i)
            if(x[i]) {
                if(A[i].any())
                    x ^= A[i];
                else {
                    A[i] = x;
                    return;
                }
            }
    }
    Bit query() {
        Bit res = 0;
        for(int i = 999; i >= 0; --i)
            if(!res[i])
                res ^= A[i];
        return res;
    }
};
void query(int l, int r, int id, const Base& src) {
    Base cur = src;
    for(int i = 0; i < eid[id].size(); ++i) {
        int e = eid[id][i];
        cur.insert(dis[A[e].u] ^ dis[A[e].v] ^ A[e].w);
    }
    if(l == r) {
        Bit res = cur.query();
        bool flag = true;
        for(int i = 999; i >= 0; --i) {
            if(res[i]) {
                flag = false;
                for(; i >= 0; --i)
                    std::cout << res[i];
                std::cout << std::endl;
                break;
            }
        }
        if(flag)
            std::cout << '0' << std::endl;
    } else {
        int m = (l + r) >> 1;
        query(l, m, id << 1, cur);
        query(m + 1, r, id << 1 | 1, cur);
    }
}
int ref[size * 2], beg[size * 2];
int main() {
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, p;
    std::cin >> n >> m >> p;
    ++p;
    int ecnt = 0;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        Bit w;
        std::cin >> u >> v >> w;
        int fu = find(u), fv = find(v);
        if(fu != fv) {
            fa[fu] = fv;
            addEdge(u, v, w);
            addEdge(v, u, w);
        } else {
            A[++ecnt] = Info(u, v, w);
            insert(1, p, 1, 1, p, ecnt);
        }
    }
    buildTree(1, 0);
    int gid = 0;
    for(int t = 2; t <= p; ++t) {
        char op[10];
        std::cin >> op;
        switch(op[1]) {
            case 'd': {
                int id = ++gid;
                ref[id] = ++ecnt;
                int u, v;
                Bit w;
                std::cin >> u >> v >> w;
                A[ecnt] = Info(u, v, w);
                beg[id] = t;
            } break;
            case 'a': {
                int k;
                std::cin >> k;
                insert(1, p, 1, beg[k], t - 1, ref[k]);
                ref[k] = 0;
            } break;
            case 'h': {
                int k;
                Bit w;
                std::cin >> k >> w;
                insert(1, p, 1, beg[k], t - 1, ref[k]);
                int id = ref[k], u = A[id].u,
                    v = A[id].v;
                ref[k] = ++ecnt;
                beg[k] = t;
                A[ecnt] = Info(u, v, w);
            } break;
        }
    }
    for(int i = 1; i <= gid; ++i)
        if(ref[i])
            insert(1, p, 1, beg[i], p, ref[i]);
    Base empty;
    query(1, p, 1, empty);
    return 0;
}
