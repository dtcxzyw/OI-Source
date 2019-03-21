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
const int size = 305;
struct Edge {
    int to, nxt, f;
} E[size * size];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
int d[size], q[size], gap[size], S, T;
void BFS() {
    q[0] = T, ++gap[1], d[T] = 1;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(!d[v]) {
                d[v] = d[u] + 1;
                ++gap[d[v]];
                q[e++] = v;
            }
        }
    }
}
int now[size];
int aug(int u, int mf) {
    if(u == T || mf == 0)
        return mf;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[u] == d[v] + 1 &&
           (k = aug(v, std::min(mf, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, mf -= k;
            if(!mf)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = T + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP(int n) {
    BFS();
    memcpy(now + 1, last + 1, sizeof(int) * n);
    int res = 0;
    while(d[S] <= n)
        res += aug(S, 1 << 30);
    return res;
}
int X[size], Y[size];
bool flag[size][size];
int main() {
    int n = read();
    int m = read();
    int k = read();
    S = n + m + 1, T = S + 1;
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        X[i] = read();
        addEdge(S, i, X[i]);
        res += X[i];
    }
    for(int i = 1; i <= m; ++i) {
        Y[i] = read();
        addEdge(n + i, T, Y[i]);
        res += Y[i];
    }
    for(int i = 1; i <= k; ++i) {
        int x = read();
        int y = read();
        flag[x][y] = true;
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            if(!flag[i][j])
                addEdge(i, n + j, 1);
    res -= ISAP(T);
    if(res < 0 || res > n * m - k)
        puts("IIllIIll1！");
    else
        printf("%d\n", res);
    return 0;
}
