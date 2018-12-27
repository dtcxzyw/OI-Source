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
int minv(int a, int b) {
    return a < b ? a : b;
}
const int size = 205;
struct Edge {
    int to, nxt, f;
} E[105 * size];
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
int q[size], d[size], S, T;
bool BFS() {
    memset(d + 1, -1, sizeof(int) * T);
    int b = 0, e = 1;
    q[b] = S, d[S] = 0;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f && d[v] == -1) {
                d[v] = d[u] + 1;
                if(v == T)
                    return true;
                q[e++] = v;
            }
        }
    }
    return false;
}
int now[size];
int DFS(int u, int mf) {
    if(u == T || mf == 0)
        return mf;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] == d[u] + 1 &&
           (k = DFS(v, minv(mf, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, mf -= k;
            if(mf == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
int dinic() {
    int res = 0;
    while(BFS()) {
        memcpy(now + 1, last + 1, sizeof(int) * T);
        res += DFS(S, 1 << 30);
    }
    return res;
}
int f[size], base[size * 50];
int main() {
    int n = read();
    int m = read();
    S = n + 1, T = S + 1;
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        int a = read();
        int b = read();
        addEdge(u, v, b - a);
        f[u] -= a, f[v] += a;
        base[i] = a;
    }
    int sum = 0;
    for(int i = 1; i <= n; ++i)
        if(f[i] > 0) {
            addEdge(S, i, f[i]);
            sum += f[i];
        } else if(f[i] < 0)
            addEdge(i, T, -f[i]);
    bool res = dinic() == sum;
    if(res) {
        puts("YES");
        for(int i = 1; i <= m; ++i)
            printf("%d\n", base[i] + E[i << 1 | 1].f);
    } else
        puts("NO");
    return 0;
}
