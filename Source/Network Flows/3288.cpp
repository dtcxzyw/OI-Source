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
const int size = 5005;
typedef double FT;
struct Edge {
    int to, nxt, w;
} E[6005];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
FT dis[size], ck;
bool flag[size], vis[size];
bool SPFA(int u) {
    vis[u] = flag[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        FT cd = dis[u] + E[i].w + ck;
        if(cd < dis[v]) {
            dis[v] = cd;
            if(flag[v] || SPFA(v))
                return true;
        }
    }
    flag[u] = false;
    return false;
}
bool check(FT k, int n) {
    ck = k;
    memset(vis + 1, 0, sizeof(bool) * n);
    memset(flag + 1, 0, sizeof(bool) * n);
    for(int i = 1; i <= n; ++i)
        if(!vis[i]) {
            if(SPFA(i))
                return true;
        }
    return false;
}
int main() {
    int n = read();
    int m = read();
    int S = n + 1;
    for(int i = 0; i < m; ++i) {
        int u = read();
        int v = read();
        int a = read();
        int b = read();
        int c = read();
        int d = read();
        if(u != S) {
            if(c)
                addEdge(v, u, a - d);
            addEdge(u, v, b + d);
        }
    }
    n += 2;
    FT l = 0.0, r = 1e5;
    while(r - l > 1e-4) {
        FT mid = (l + r) * 0.5;
        if(check(mid, n))
            l = mid;
        else
            r = mid;
    }
    printf("%.2lf\n", l);
    return 0;
}
