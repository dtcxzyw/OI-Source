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
typedef long long Int64;
const int size = 100005;
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
Int64 L[size], dp[size], maxt, A[size], B[size],
    top = 0;
void solve(int u) {
    Int64 fac = 2 * L[u];
    int l = 1, r = top, trans = 1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(m == 1 ||
           fac * (A[m - 1] - A[m]) < B[m - 1] - B[m])
            trans = m, l = m + 1;
        else
            r = m - 1;
    }
    dp[u] = L[u] * L[u] - fac * A[trans] + B[trans];
    maxt = std::max(maxt, dp[u]);
}
#define asFT static_cast<double>
struct Backup {
    Int64 olda, oldb;
    int pos, osiz;
    void insert(Int64 na, Int64 nb) {
        int l = 1, r = top;
        pos = top + 1;
        while(l <= r) {
            int m = (l + r) >> 1;
            if(m == 1 ||
               asFT(B[m - 1] - B[m]) * (A[m] - na) <
                   asFT(B[m] - nb) * (A[m - 1] - A[m]))
                l = m + 1;
            else
                pos = m, r = m - 1;
        }
        osiz = top;
        top = pos;
        olda = A[pos], oldb = B[pos];
        A[pos] = na, B[pos] = nb;
    }
    void recover() {
        A[pos] = olda;
        B[pos] = oldb;
        top = osiz;
    }
};
Int64 P;
void DFS(int u, int p) {
    if(u != 1)
        solve(u);
    Backup bak;
    bak.insert(L[u], L[u] * L[u] + dp[u] + P);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p)
            continue;
        L[v] = L[u] + E[i].w;
        DFS(v, u);
    }
    bak.recover();
}
Int64 foo() {
    int n = read();
    cnt = 0;
    memset(last + 1, 0, sizeof(int) * n);
    P = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dp[1] = -P;
    maxt = 0;
    DFS(1, 0);
    return maxt;
}
int main() {
    int t = read();
    for(int i = 1; i <= t; ++i)
        printf("%lld\n", foo());
    return 0;
}
