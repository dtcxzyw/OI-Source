#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int maxn = 105, size = 2 * maxn, S = 0, inf = 0x3f3f3f3f;
int T;
struct Edge {
    int to, nxt, f, w;
} E[maxn * maxn];
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
    int m = read();
    int s2i = 2 * n + 1;
    int s2o = s2i + 1;
    addEdge(s2i, s2o, m, 0);
    T = s2o + 1;
    for(int i = 1; i <= n; ++i) {
        int v = read();
        A[i + n] += v;
        A[i] -= v;
        addEdge(s2o, i, inf, 0);
        addEdge(i + n, s2i, inf, 0);
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            int w = read();
            if(w != -1)
                addEdge(i + n, j, inf, w);
        }
    }
    for(int i = 1; i < T; ++i)
        if(A[i] > 0)
            addEdge(S, i, A[i], 0);
        else if(A[i] < 0)
            addEdge(i, T, -A[i], 0);
    printf("%d\n", MCMF(T + 1));
    return 0;
}
