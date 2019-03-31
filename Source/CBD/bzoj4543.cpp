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
const int size = 100005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int d[size], son[size];
void pre(int u, int p) {
    d[u] = 1;
    int md = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            pre(v, u);
            d[u] = std::max(d[u], d[v] + 1);
            if(md < d[v])
                md = d[v], son[u] = v;
        }
    }
}
int F[size], G[2 * size], fcnt = 0, gcnt = 0, ans = 0;
void DFS(int u, int p, int* fu, int* gu) {
    if(son[u])
        DFS(son[u], u, fu + 1, gu - 1);
    fu[0] = 1, ans += gu[0];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && v != son[u]) {
            int *fv = F + fcnt, *gv = G + gcnt + d[v];
            fcnt += d[v], gcnt += 2 * d[v];
            DFS(v, u, fv, gv);
            for(int j = 1; j < d[v]; ++j)
                ans += fu[j - 1] * gv[j];
            for(int j = 0; j < d[v]; ++j)
                ans += fv[j] * gu[j + 1];
            for(int j = 1; j < d[v]; ++j)
                gu[j - 1] += gv[j];
            for(int j = 1; j <= d[v]; ++j) {
                gu[j] += fu[j] * fv[j - 1];
                fu[j] += fv[j - 1];
            }
        }
    }
}
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    pre(1, 0);
    fcnt += d[1], gcnt += 2 * d[1];
    DFS(1, 0, F, G + d[1]);
    printf("%d\n", ans);
    return 0;
}
