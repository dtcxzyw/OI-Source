#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long Int64;
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
int iabs(int x) {
    return x >= 0 ? x : -x;
}
const int size = 2005;
struct Edge {
    int to, nxt, f, w;
} E[size * size];
int last[size], cnt = 1;
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
int S, T, q[size];
Int64 dis[size];
bool flag[size];
bool SPFA() {
    memset(dis, 0x3f, sizeof(dis));
    q[0] = T, dis[T] = 0, flag[T] = true;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            Int64 dv = dis[u] + E[i ^ 1].w;
            if(E[i ^ 1].f && dv < dis[v]) {
                dis[v] = dv;
                if(!flag[v]) {
                    flag[v] = true;
                    if(b != e && dis[q[b]] > dis[v]) {
                        if(--b == -1)
                            b += size;
                        q[b] = v;
                    } else {
                        q[e++] = v;
                        if(e == size)
                            e = 0;
                    }
                }
            }
        }
    }
    return dis[S] != 0x3f3f3f3f3f3f3f3f;
}
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    flag[u] = true;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!flag[v] && dis[v] + E[i].w == dis[u] &&
           (k = DFS(v, std::min(f, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    flag[u] = false;
    if(res == 0)
        dis[u] = -1;
    return res;
}
Int64 MCMF() {
    Int64 res = 0;
    while(SPFA()) {
        Int64 ds = dis[S];
        memcpy(now, last, sizeof(now));
        int cf, sf = 0;
        while((cf = DFS(S, 1 << 30)))
            sf += cf;
        res += sf * ds;
    }
    return res;
}
int A[size];
int main() {
    int n, w;
    scanf("%d%d", &n, &w);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &A[i]);
    S = 2 * n + 1;
    T = S + 1;
    for(int i = 1; i <= n; ++i) {
        addEdge(S, i, 1, 0);
        addEdge(S, n + i, 1, w);
        for(int j = i + 1; j <= n; ++j)
            addEdge(i, n + j, 1, iabs(A[i] - A[j]));
        addEdge(n + i, T, 1, 0);
    }
    printf("%lld\n", MCMF());
    return 0;
}
