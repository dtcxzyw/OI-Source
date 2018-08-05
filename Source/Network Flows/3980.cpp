#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
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
const int size = 1005, S = 0, inf = INT_MAX;
int T;
struct Edge {
    int to, nxt, f, w;
} E[2 * (size + 10000)];
int last[size] = {}, cnt = 1;
void addEdgeImpl(int u, int v, int f, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f, E[cnt].w = w;
    last[u] = cnt;
}
void addEdge(int u, int v, int f, int w) {
    addEdgeImpl(u, v, f, w);
    addEdgeImpl(v, u, 0, -w);
}
Int64 dis[size];
int eid[size], q[size];
bool flag[size] = {};
bool SPFA(int siz) {
    memset(dis, 0x3f, sizeof(Int64) * siz);
    q[0] = S, dis[S] = 0, flag[S] = true;
    int b = 0, e = 1;
    while (b != e) {
        int u = q[b++];
        flag[u] = false;
        if (b == size) b = 0;
        for (int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            Int64 cd = dis[u] + E[i].w;
            if (E[i].f && dis[v] > cd) {
                dis[v] = cd;
                eid[v] = i;
                if (!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if (e == size) e = 0;
                }
            }
        }
    }
    return dis[T] != 0x3f3f3f3f3f3f3f3f;
}
Int64 MCMF(int siz) {
    Int64 res = 0;
    while (SPFA(siz)) {
        int p = T, mf = inf;
        while (p != S) {
            int e = eid[p];
            mf = std::min(mf, E[e].f);
            p = E[e ^ 1].to;
        }
        p = T;
        while (p != S) {
            int e = eid[p];
            E[e].f -= mf, E[e ^ 1].f += mf;
            p = E[e ^ 1].to;
        }
        res += mf * dis[T];
    }
    return res;
}
int main() {
    int n = read();
    int m = read();
    T = n + 1;
    addEdge(S, 1, inf, 0);
    for (int i = 1; i <= n; ++i)
        addEdge(i, i + 1, inf - read(), 0);
    for (int i = 1; i <= m; ++i) {
        int s = read();
        int t = read();
        int c = read();
        addEdge(s, t + 1, inf, c);
    }
    printf("%lld\n", MCMF(T + 1));
    return 0;
}
