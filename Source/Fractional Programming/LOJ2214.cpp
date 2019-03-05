#include <csetjmp>
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
const int size = 5005;
struct Edge {
    int to, nxt, w;
} E[2 * size];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
typedef double FT;
const FT eps = 1e-3;
FT x, delta;
jmp_buf buf;
int vis[size];
FT dis[size];
void pre(int u, int d) {
    vis[u] = d;
    FT du = dis[u];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        FT dv = du + E[i].w + x;
        if(dv < dis[v]) {
            if(vis[v]) {
                delta =
                    (dis[v] - dv) / (d + 1 - vis[v]);
                longjmp(buf, 1);
            }
            dis[v] = dv;
            pre(v, d + 1);
            break;
        }
    }
    vis[u] = 0;
}
int D;
void DFS(int u, int d) {
    if(d == D)
        return;
    vis[u] = d;
    FT du = dis[u];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        FT dv = du + E[i].w + x;
        if(dv < dis[v]) {
            if(vis[v]) {
                delta =
                    (dis[v] - dv) / (d + 1 - vis[v]);
                longjmp(buf, 1);
            }
            dis[v] = dv;
            DFS(v, d + 1);
        }
    }
    vis[u] = 0;
}
bool iter(int n) {
    memset(dis + 1, 0, sizeof(double) * n);
    memset(vis + 1, 0, sizeof(int) * n);
    if(setjmp(buf)) {
        x += delta + 1e-4;
        return delta > eps;
    } else {
        for(int i = 1; i <= n; ++i)
            pre(i, 1);
        int end = n * 2;
        for(D = 1; D <= end; ++D)
            for(int i = 1; i <= n; ++i)
                DFS(i, 1);
        return false;
    }
}
int main() {
    int n = read();
    int m = read();
    int S = n + 1;
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        int a = read();
        int b = read();
        int c = read();
        int d = read();
        if(u != S) {
            if(c)
                addEdge(u, v, a - d);
            addEdge(v, u, b + d);
        }
    }
    x = 0.0;
    while(iter(n + 2))
        ;
    printf("%.2lf\n", x);
    return 0;
}
