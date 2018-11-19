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
const int size = 100050, vsiz = 50, mod = 998244353;
#define asInt64(x) static_cast<long long>(x)
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
bool flag[size], vis[size];
struct Info {
    int u, v;
} VE[vsiz];
int ecnt = 0;
bool DFS(int u, int p) {
    vis[u] = true;
    int siz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            if(vis[v]) {
                flag[u] = true;
                if(u < v) {
                    VE[ecnt].u = u, VE[ecnt].v = v;
                    ++ecnt;
                }
            } else
                siz += DFS(v, u);
        }
    }
    if(siz >= 2)
        flag[u] = true;
    return siz | flag[u];
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
struct Vec {
    int x, y;
    Vec() {}
    Vec(int x, int y) : x(x), y(y) {}
    Vec operator+(const Vec& rhs) const {
        return Vec(add(x, rhs.x), add(y, rhs.y));
    }
    void operator*=(long long k) {
        x = x * k % mod, y = y * k % mod;
    }
    void operator*=(const Vec& rhs) {
        x = x * asInt64(rhs.x) % mod,
        y = y * asInt64(rhs.y) % mod;
    }
} k[size][2];
long long dot(const Vec& a, const Vec& b) {
    return (asInt64(a.x) * b.x + asInt64(a.y) * b.y) %
        mod;
}
struct VT {
    struct Edge {
        int to, nxt;
        Vec a, b;
    } E[vsiz];
    int last[size], cnt;
    VT() : cnt(0) {}
    void addEdge(int u, int v, const Vec& a,
                 const Vec& b) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u],
        E[cnt].a = a, E[cnt].b = b;
        last[u] = cnt;
    }
} vt;
int dp[size][2];
int build(int u) {
    vis[u] = true;
    int link = 0;
    dp[u][0] = dp[u][1] = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int lv = build(v);
            if(lv) {
                if(flag[u])
                    vt.addEdge(u, lv,
                               k[v][0] + k[v][1],
                               k[v][0]);
                else
                    k[u][0] = k[v][0] + k[v][1],
                    k[u][1] = k[v][0], link = lv;
            } else {
                dp[u][0] = dp[u][0] *
                    asInt64(dp[v][0] + dp[v][1]) % mod;
                dp[u][1] =
                    dp[u][1] * asInt64(dp[v][0]) % mod;
            }
        }
    }
    if(flag[u])
        k[u][0] = Vec(1, 0), k[u][1] = Vec(0, 1),
        link = u;
    else
        k[u][0] *= dp[u][0], k[u][1] *= dp[u][1];
    return link;
}
int d[size];
void preDepth(int u) {
    for(int i = vt.last[u]; i; i = vt.E[i].nxt) {
        int v = vt.E[i].to;
        d[v] = d[u] + 1;
        preDepth(v);
    }
}
bool cho[size][2];
Vec solve(int u) {
    Vec res(cho[u][1] ? 0 : dp[u][0],
            cho[u][0] ? 0 : dp[u][1]);
    for(int i = vt.last[u]; i; i = vt.E[i].nxt) {
        int v = vt.E[i].to;
        Vec dpv = solve(v);
        res *= Vec(dot(dpv, vt.E[i].a),
                   dot(dpv, vt.E[i].b));
    }
    return res;
}
int main() {
    int n = read();
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    DFS(1, 0);
    memset(vis + 1, 0, sizeof(bool) * n);
    flag[1] = true;
    build(1);
    preDepth(1);
    for(int i = 0; i < ecnt; ++i)
        if(d[VE[i].u] > d[VE[i].v])
            std::swap(VE[i].u, VE[i].v);
    int end = 1 << ecnt, ans = 0;
    for(int i = 0; i < end; ++i) {
        for(int j = 0; j < ecnt; ++j)
            if(i & (1 << j))
                cho[VE[j].u][1] = cho[VE[j].v][0] =
                    true;
            else
                cho[VE[j].u][0] = true;
        Vec res = solve(1);
        ans = add(ans, add(res.x, res.y));
        for(int j = 0; j < ecnt; ++j)
            if(i & (1 << j))
                cho[VE[j].u][1] = cho[VE[j].v][0] =
                    false;
            else
                cho[VE[j].u][0] = false;
    }
    printf("%d\n", ans);
    return 0;
}
