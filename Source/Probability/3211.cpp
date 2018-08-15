#include <algorithm>
#include <cmath>
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
    for (int i = 1; i <= n; ++i) {
        int x = i;
        for (int j = i + 1; j <= n; ++j)
            if (fabs(A[j][i]) > fabs(A[x][i]))
                x = j;
        if (i != x) {
            std::swap(B[i], B[x]);
            for (int j = i; j <= n; ++j)
                std::swap(A[i][j], A[x][j]);
        }
        for (int j = i + 1; j <= n; ++j) {
            FT fac = A[j][i] / A[i][i];
            B[j] -= B[i] * fac;
            for (int k = i; k <= n; ++k)
                A[j][k] -= A[i][k] * fac;
        }
    }
    for (int i = n; i >= 1; --i) {
        FT sum = B[i];
        for (int j = i + 1; j <= n; ++j)
            sum -= C[j] * A[i][j];
        C[i] = sum / A[i][i];
    }
}
int d[size] = {};
int main() {
    int n = read();
    int m = read();
    int maxw = 0;
    while (m--) {
        int u = read();
        int v = read();
        int w = read();
        maxw = std::max(maxw, w);
        addEdge(u, v, w), ++d[u];
        if (u != v) {
            addEdge(v, u, w);
            ++d[v];
        }
    }
    FT ans = 0.0;
    for (int k = 1; k <= maxw; k <<= 1) {
        memset(A, 0, sizeof(A));
        for (int i = 1; i < n; ++i) {
            A[i][i] = d[i];
            B[i] = 0.0;
            for (int j = last[i]; j; j = E[j].nxt) {
                int v = E[j].to;
                if (E[j].w & k)
                    ++A[i][v], ++B[i];
                else
                    --A[i][v];
            }
        }
        B[n] = 0.0, A[n][n] = 1.0;
        solve(n);
        ans += k * C[1];
    }
    printf("%.3lf\n", ans);
    return 0;
}
