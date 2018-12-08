// SP12056
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
const int size = 305;
typedef long long Int64;
Int64 A[size][size];
bool flag[size], vis[size];
void merge(int u, int v, int n) {
    for(int i = 1; i <= n; ++i) {
        A[i][u] += A[i][v];
        A[u][i] += A[v][i];
    }
    flag[v] = true;
}
Int64 w[size];
Int64 solveImpl(int n, int cnt, int& s, int& t) {
    memcpy(vis + 1, flag + 1, sizeof(bool) * n);
    memset(w + 1, 0, sizeof(Int64) * n);
    for(int i = 1; i <= n; ++i)
        if(!flag[i]) {
            t = i;
            break;
        }
    while(cnt--) {
        s = t;
        vis[s] = true;
        t = 0;
        for(int i = 1; i <= n; ++i)
            if(!vis[i]) {
                w[i] += A[s][i];
                if(w[i] >= w[t])
                    t = i;
            }
    }
    merge(s, t, n);
    return w[t];
}
Int64 solve(int n) {
    memset(flag + 1, 0, sizeof(bool) * n);
    Int64 res = 1LL << 60;
    int s, t;
    for(int i = n - 1; i && res; --i)
        res = std::min(res, solveImpl(n, i, s, t));
    return res;
}
int main() {
    while(true) {
        int n = read();
        int m = read();
        read();
        if(n == 0)
            break;
        memset(A, 0, sizeof(A));
        while(m--) {
            int u = read();
            int v = read();
            int w = read();
            A[u][v] += w;
            A[v][u] += w;
        }
        printf("%lld\n", solve(n));
    }
    return 0;
}
