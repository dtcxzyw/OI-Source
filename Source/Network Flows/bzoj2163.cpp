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
const int size = 20005;
struct Edge {
    int to, nxt, f, w;
} E[(size * 3 + 100005) * 2];
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
int dis[size], q[size], S, T;
bool flag[size];
bool SPFA() {
    memset(dis + 1, 0x3f, sizeof(int) * T);
    int b = 0, e = 1;
    dis[T] = 0, q[b] = T, flag[T] = true;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to, dv = dis[u] - E[i].w;
            if(E[i ^ 1].f && dv < dis[v]) {
                dis[v] = dv;
                if(!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if(e == size)
                        e = 0;
                }
            }
        }
    }
    return dis[S] != 0x3f3f3f3f;
}
int now[size];
bool vis[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    vis[u] = true;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v] && dis[u] == dis[v] + E[i].w &&
           (k = DFS(v, std::min(E[i].f, f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            f -= k, res += k;
            if(f == 0)
                break;
        }
    }
    if(res)
        vis[u] = false;
    return res;
}
int MCMF() {
    int res = 0;
    while(SPFA()) {
        memset(vis + 1, 0, sizeof(bool) * T);
        memcpy(now + 1, last + 1, sizeof(int) * T);
        int sf = 0, cf;
        while((cf = DFS(S, 1 << 30)))
            sf += cf;
        res += dis[S] * sf;
    }
    return res;
}
int main() {
    int n = read();
    int m = read();
    S = 2 * n + 1, T = S + 1;
    for(int i = 1; i <= n; ++i) {
        int f = read();
        addEdge(S, i + n, f, 1);
        addEdge(i + n, T, f, 0);
        addEdge(S, i, f, 0);
    }
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v + n, w, 0);
    }
    printf("%d\n", MCMF());
    return 0;
}
