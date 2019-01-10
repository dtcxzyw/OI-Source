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
const int size = 505, maxv = size * size, inf = 1
    << 30;
struct Edge {
    int to, nxt, f;
} E[2 * (3 * size * size + size)];
int last[maxv], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
int S, T, siz, gap[maxv], q[maxv], d[maxv];
void BFS() {
    gap[1] = 1, q[0] = T, d[T] = 1;
    int b = 0, e = 1;
    while(b < e) {
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
int mini(int a, int b) {
    return a < b ? a : b;
}
int now[maxv];
int aug(int u, int mf) {
    if(u == T || mf == 0)
        return mf;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[u] == d[v] + 1 &&
           (k = aug(v, mini(mf, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, mf -= k;
            if(!mf)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = siz + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP() {
    BFS();
    memcpy(now + 1, last + 1, sizeof(int) * siz);
    int res = 0;
    while(d[S] <= siz)
        res += aug(S, inf);
    return res;
}
int main() {
    int n = read();
    siz = n;
    S = ++siz, T = ++siz;
    int sum = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            int w = read(), id = ++siz;
            addEdge(i, id, inf);
            addEdge(j, id, inf);
            sum += w;
            addEdge(id, T, w);
        }
    for(int i = 1; i <= n; ++i)
        addEdge(S, i, read());
    printf("%d\n", sum - ISAP());
    return 0;
}
