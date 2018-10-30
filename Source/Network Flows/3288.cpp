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
const int size = 5050, esiz = size + 3005 * 2;
struct Edge {
    int to, nxt, f, w;
} E[2 * esiz];
int last[size], cnt;
void addEdgeImpl(int u, int v, int f, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f,
    E[cnt].w = w;
    last[u] = cnt;
}
void addEdge(int u, int v, int f, int w) {
    addEdgeImpl(u, v, f, w);
    addEdgeImpl(v, u, 0, -w);
}
int q[size], dis[size], eid[size];
bool flag[size];
bool SPFA(int siz, int S, int T) {
    memset(dis + 1, 0x3f, sizeof(int) * siz);
    int b = 0, e = 1;
    q[b] = S, flag[S] = true, dis[S] = 0;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f && dis[v] > dis[u] + E[i].w) {
                dis[v] = dis[u] + E[i].w;
                eid[v] = i;
                if(!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if(e == size)
                        e = 0;
                }
            }
        }
    }
    return dis[T] != 0x3f3f3f3f;
}
int MCMF(int siz, int S, int T) {
    int res = 0;
    while(SPFA(siz, S, T)) {
        int p = T, cf = 1 << 30;
        while(p != S) {
            int e = eid[p];
            cf = std::min(cf, E[e].f);
            p = E[e ^ 1].to;
        }
        p = T;
        while(p != S) {
            int e = eid[p];
            E[e].f -= cf, E[e ^ 1].f += cf;
            p = E[e ^ 1].to;
        }
        res += dis[T] * cf;
    }
    printf("%d\n", res);
    return res;
}
struct Info {
    int u, v, a, b, c, d;
} A[3005];
double check(int k, int n, int m) {
    memset(last + 1, 0, sizeof(int) * (n + 2));
    cnt = 1;
    int S = n + 1, T = n + 2;
    for(int i = 0; i < m; ++i) {
        if(A[i].u != S) {
            addEdge(A[i].u, A[i].v, 1 << 20, A[i].b);
            addEdge(A[i].v, A[i].u, A[i].c, A[i].a);
        } else
            addEdge(S, A[i].v, k, 0);
    }
    return static_cast<double>(-MCMF(n + 2, S, T)) / k;
}
int main() {
    int n = read();
    int m = read();
    for(int i = 0; i < m; ++i) {
        A[i].u = read();
        A[i].v = read();
        A[i].a = read();
        A[i].b = read();
        A[i].c = read();
        A[i].d = read();
        A[i].a -= A[i].d;
        A[i].b += A[i].d;
    }
    int l = 1, r = 1 << 20;
    while(l + 6 < r) {
        int lm = (l * 2 + r) / 3, rm = (l + r * 2) / 3;
        double lans = check(lm, n, m),
               rans = check(rm, n, m);
        if(lans < rans)
            l = lm;
        else
            r = rm;
    }
    double ans = 0.0;
    for(int i = l; i <= r; ++i)
        ans = std::max(ans, check(i, n, m));
    printf("%.2lf\n", ans);
    return 0;
}
