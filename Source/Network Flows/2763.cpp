#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 10500, S = 0;
int T;
struct Edge {
    int to, nxt, f;
} E[6 * size];
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
    while (b != e) {
        int u = q[b++];
        for (int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if (E[i].f && d[v] == 0) {
                d[v] = d[u] + 1;
                q[e++] = v;
            }
        }
    }
    return d[T];
}
int now[size];
int DFS(int u, int f) {
    if (u == T || f == 0) return f;
    int res = 0, k;
    for (int &i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if (d[v] == d[u] + 1 && (k = DFS(v, std::min(E[i].f, f)))) {
            E[i].f -= k;
            E[i ^ 1].f += k;
            f -= k;
            res += k;
            if (f == 0) break;
        }
    }
    if (res == 0) d[u] = -1;
    return res;
}
int dinic(int siz) {
    int res = 0;
    while (BFS(siz)) {
        memcpy(now, last, sizeof(int) * siz);
        res += DFS(S, inf);
    }
    return res;
}
int main() {
    int k = read();
    int n = read();
    T = n + k + 1;
    int m = 0;
    for (int i = 1; i <= k; ++i) {
        int c = read();
        m += c;
        addEdge(n + i, T, c);
    }
    for (int i = 1; i <= n; ++i) {
        addEdge(S, i, 1);
        int p = read();
        while (p--) addEdge(i, n + read(), 1);
    }
    if (dinic(T + 1) == m) {
        for (int i = 1; i <= k; ++i) {
            printf("%d:", i);
            for (int j = last[n + i]; j; j = E[j].nxt)
                if ((j & 1) && E[j].f) {
                    printf("%d ", E[j].to);
                }
            putchar('\n');
        }
    } else
        puts("No Solution!");
    return 0;
}
