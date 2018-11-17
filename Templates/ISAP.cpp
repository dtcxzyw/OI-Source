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
const int size = 10005;
struct Edge {
    int to, nxt, f;
} E[size * 20];
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
int d[size], q[size], gap[size], S, T, n;
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
        d[S] = n + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP() {
    BFS();
    memcpy(now + 1, last + 1, sizeof(int) * n);
    int res = 0;
    while(d[S] <= n)
        res += aug(S, 1 << 30);
    return res;
}
int main() {
    n = read();
    int m = read();
    S = read();
    T = read();
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
    }
    printf("%d\n", ISAP());
    return 0;
}
