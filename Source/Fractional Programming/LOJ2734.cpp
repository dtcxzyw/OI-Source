#include <algorithm>
#include <cassert>
#include <cmath>
#include <csetjmp>
#include <cstdio>
#include <cstring>
namespace IO {
    void init() {
        assert(setvbuf(stdin, 0, _IONBF, 0) == 0);
        assert(setvbuf(stdout, 0, _IONBF, 0) == 0);
    }
    const int size = 1 << 21;
    char in[size];
    char getc() {
        static char *S = in, *T = in;
        if(S == T)
            S = in, T = in + fread(in, 1, size, stdin);
        return S == T ? EOF : *S++;
    }
}
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
const int size = 105, maxk = 1005, inf = 0x3f3f3f3f;
typedef double FT;
const FT eps = 1e-2;
struct Edge {
    int to, nxt;
    FT w;
} E[size * size];
int last[size], cnt;
void addEdge(int u, int v, FT w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
FT dis[size];
bool vis[size];
jmp_buf buf;
bool pre(int u) {
    FT cd = dis[u];
    vis[u] = true;
    bool res = false;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        FT dv = cd + E[i].w;
        if(dv < dis[v]) {
            if(vis[v])
                longjmp(buf, 1);
            dis[v] = dv;
            pre(v);
            res = true;
            break;
        }
    }
    vis[u] = false;
    return res;
}
void DFS(int u, int d) {
    if(d == 0)
        return;
    FT cd = dis[u];
    vis[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        FT dv = cd + E[i].w;
        if(dv < dis[v]) {
            if(vis[v])
                longjmp(buf, 1);
            dis[v] = dv;
            DFS(v, d - 1);
        }
    }
    vis[u] = false;
}
int link[size][size], off[size][size];
bool check(int n, int K, FT x) {
    cnt = 0;
    memset(last + 1, 0, sizeof(int) * n);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            if(off[i][j] != inf && link[i][j] != inf)
                addEdge(i, j,
                        off[i][j] + link[i][j] * x);
        }
    memset(vis + 1, 0, sizeof(bool) * n);
    memset(dis + 1, 0, sizeof(double) * n);
    if(setjmp(buf))
        return true;
    else {
        for(int i = 1; i <= n; ++i)
            while(pre(i))
                ;
        int end = 2 * n;
        for(int k = 1; k < end; k <<= 1)
            for(int i = 1; i <= n; ++i)
                DFS(i, k);
        return false;
    }
}
int b[size][maxk], s[size][maxk];
int main() {
    IO::init();
    int n = read();
    int m = read();
    int K = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= K; ++j) {
            b[i][j] = read();
            s[i][j] = read();
        }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            int& mind = off[i][j];
            mind = inf;
            if(i == j)
                continue;
            for(int k = 1; k <= K; ++k)
                if(b[i][k] != -1 && s[j][k] != -1)
                    mind = std::min(mind,
                                    b[i][k] - s[j][k]);
        }
    memset(link, 0x3f, sizeof(link));
    for(int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        int t = read();
        link[u][v] = std::min(link[u][v], t);
    }
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            if(link[i][k] != inf)
                for(int j = 1; j <= n; ++j)
                    link[i][j] = std::min(
                        link[i][j],
                        link[i][k] + link[k][j]);
    FT l = 100.0, r = 350.0;
    while(floor(r + eps) - floor(l + eps) >= eps) {
        FT m = (l + r) / 2.0;
        (check(n, K, m) ? l : r) = m;
    }
    printf("%.0lf\n", floor(r + eps));
    return 0;
}
