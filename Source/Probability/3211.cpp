//TODO:3211
#include <cstdio>
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
typedef double FT;
const int size = 105;
struct Edge {
    int to, nxt, w;
} E[2 * size * size];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
FT A[size][size], B[size], C[size];
void solve(int n) {
}
int d[size];
int main() {
    int n = read();
    int m = read();
    while (m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w), ++d[u];
        if (u != v) {
            addEdge(v, u, w);
            ++d[v];
        }
    }
    for (int i = 1; i < n; ++i) {
        A[i][i] = -1.0;
        FT fac = 1.0 / d[i];
        for (int j = last[i]; j; j = E[j].nxt) {
        }
    }
    B[n] = 0.0, A[n][n] = 1.0;
    printf("%.3lf\n", C[1]);
    return 0;
}
