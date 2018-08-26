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
const int size = 105, S = 0, inf = 0x3f3f3f3f;
int T;
struct Edge {
    int to, nxt, f, w;
} E[2 * size * size];
int last[size], cnt = 1;
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
bool SPFA(int siz) {
    memset(dis, 0x3f, sizeof(int) * siz);
    q[0] = S, dis[S] = 0, flag[S] = true;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        flag[u] = false;
        if(b == size)
            b = 0;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            int cd = dis[u] + E[i].w;
            if(E[i].f && dis[v] > cd) {
                dis[v] = cd;
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
    return dis[T] != inf;
}
int MCMF(int siz) {
    int res = 0;
    while(SPFA(siz)) {
        int p = T, mf = inf;
        while(p != S) {
            int e = eid[p];
            mf = std::min(mf, E[e].f);
            p = E[e ^ 1].to;
        }
        p = T;
        while(p != S) {
            int e = eid[p];
            E[e].f -= mf, E[e ^ 1].f += mf;
            p = E[e ^ 1].to;
        }
        res += mf * dis[T];
    }
    return res;
}
int A[size];
int main() {
    int n = read();
    T = n + 1;
    for(int i = 1; i <= n; ++i) {
        addEdge(S, i, inf, 1);
        int k = read();
        A[i] -= k;
        while(k--) {
            int v = read();
            ++A[v];
            addEdge(i, v, inf, 0);
        }
    }
    for(int i = 1; i <= n; ++i)
        if(A[i] > 0)
            addEdge(S, i, A[i], 0);
        else if(A[i] < 0)
            addEdge(i, T, -A[i], 0);
    printf("%d\n", MCMF(T + 1));
    return 0;
}
