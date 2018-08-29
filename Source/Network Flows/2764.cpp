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
const int size = 305, S = 0;
int T;
struct Edge {
    int to, nxt, f;
} E[15000];
int last[size] = {}, cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
const int inf = 1 << 30;
int d[size], q[size];
bool BFS(int siz) {
    memset(d, 0, sizeof(int) * siz);
    int b = 0, e = 1;
    q[0] = S;
    d[S] = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f && d[v] == 0) {
                d[v] = d[u] + 1;
                q[e++] = v;
            }
        }
    }
    return d[T];
}
int n, now[size], nxt[size];
bool flag[size] = {};
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] == d[u] + 1 &&
           (k = DFS(v, std::min(E[i].f, f)))) {
            if(u <= n && v > n) {
                nxt[u] = v - n;
                flag[v - n] = true;
            }
            E[i].f -= k;
            E[i ^ 1].f += k;
            f -= k;
            res += k;
            if(f == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
int dinic(int siz) {
    int res = 0;
    while(BFS(siz)) {
        memcpy(now, last, sizeof(int) * siz);
        res += DFS(S, inf);
    }
    return res;
}
int main() {
    n = read();
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        addEdge(u, v + n, inf);
    }
    T = 2 * n + 1;
    for(int i = 1; i <= n; ++i) {
        addEdge(S, i, 1);
        addEdge(i + n, T, 1);
    }
    int res = n - dinic(T + 1);
    for(int i = 1; i <= n; ++i) {
        if(flag[i])
            continue;
        int u = i;
        do {
            printf("%d ", u);
            u = nxt[u];
        } while(u);
        putchar('\n');
    }
    printf("%d\n", res);
    return 0;
}
