#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 100005, siz2 = size * 2;
struct Edge {
    int to, nxt;
} E[siz2];
int last[siz2], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int order[size], b[size], fa[siz2];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
struct Info {
    int u, v, w;
    bool operator<(const Info& rhs) const {
        return w > rhs.w;
    }
} A[siz2];
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const Int64 inf = 1LL << 62;
Int64 w[siz2], limit[size];
namespace Tarjan {
    int fa[siz2], rk[size], n;
    bool vis[siz2];
    int find(int x) {
        return fa[x] ? fa[x] = find(fa[x]) : x;
    }
    void update(int u, int v, int id) {
        if(vis[v] && !limit[id])
            limit[id] = w[find(v)];
    }
    void tarjan(int u) {
        vis[u] = true;
        if(u <= n) {
            int rku = rk[u];
            update(u, order[rku + 1], rku + 1);
            update(u, order[rku - 1], rku);
        }
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            tarjan(v);
            fa[v] = u;
        }
    }
};
void solve(int n) {
    Int64 cur = 0;
    int lp = order[1];
    if(b[lp] > 0)
        cur += b[lp];
    else
        puts("0");
    for(int i = 2; i <= n; ++i) {
        int u = order[i];
        cur = std::min(cur, limit[i]);
        lp = u;
        if(b[u] > 0)
            cur += b[u];
        else {
            Int64 k = std::min(cur, asInt64(-b[u]));
            printf("%lld\n", k);
            cur -= k;
        }
    }
}
int main() {
    int n = read();
    int m = read();
    int q = read();
    Tarjan::n = n;
    for(int i = 1; i <= n; ++i) {
        int id = read();
        order[i] = id;
        Tarjan::rk[id] = i;
    }
    for(int i = 0; i <= n; ++i)
        fa[i] = i;
    for(int i = 1; i <= n; ++i)
        b[i] = read();
    for(int i = 0; i < m; ++i) {
        A[i].u = read();
        A[i].v = read();
        A[i].w = read();
    }
    std::sort(A, A + m);
    int ecnt = n - 1, icnt = n;
    if(q >= 2) {
        ecnt -= q - 1;
        int rt = ++icnt;
        fa[rt] = rt;
        w[rt] = inf;
        while(q--) {
            int x = read();
            fa[x] = rt;
            addEdge(rt, x);
        }
    }
    for(int i = 0; i < m; ++i) {
        int fu = find(A[i].u), fv = find(A[i].v);
        if(fu != fv) {
            int id = ++icnt;
            w[id] = A[i].w;
            fa[fu] = fa[fv] = fa[id] = id;
            addEdge(id, fu);
            addEdge(id, fv);
            if(--ecnt == 0)
                break;
        }
    }
    Tarjan::tarjan(icnt);
    solve(n);
    return 0;
}
