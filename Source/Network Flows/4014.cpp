#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 205, S = 0;
int T;
struct Edge {
    int to, nxt, f, w;
} E[2 * (size + 100 * 100)];
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
int dis[size], eid[size], q[size];
bool flag[size] = {};
template <typename Comparer>
bool SPFA(int siz) {
    memset(dis, Comparer::mask, sizeof(int) * siz);
    q[0] = S, dis[S] = 0, flag[S] = true;
    int b = 0, e = 1;
    while (b != e) {
        int u = q[b++];
        flag[u] = false;
        if (b == size) b = 0;
        for (int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            int cd = dis[u] + E[i].w;
            if (E[i].f && Comparer::cmp(dis[v], cd)) {
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
    return dis[T] != Comparer::inf;
}
const int inf = 1 << 30;
template <typename Comparer>
int MCMF(int siz) {
    int res = 0;
    while (SPFA<Comparer>(siz)) {
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
struct CmpMin {
    static const int mask = 0x3f;
    static const int inf = 0x3f3f3f3f;
    static bool cmp(int a, int b) {
        return a > b;
    }
};
struct CmpMax {
    static const int mask = 0xc0;
    static const int inf = 0xc0c0c0c0;
    static bool cmp(int a, int b) {
        return a < b;
    }
};
int main() {
    int n = read();
    T = 2 * n + 1;
    for (int i = 1; i <= n; ++i) {
        addEdge(S, i, 1, 0);
        addEdge(i + n, T, 1, 0);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            addEdge(i, j + n, 1, read());
    printf("%d\n", MCMF<CmpMin>(T + 1));
    for (int i = 2; i <= cnt; ++i)
        if (i & 1)
            E[i].f = 0;
        else
            E[i].f += E[i ^ 1].f;
    printf("%d\n", MCMF<CmpMax>(T + 1));
    return 0;
}
