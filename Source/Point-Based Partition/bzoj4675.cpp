#include <algorithm>
#include <cstdio>
#include <cstring>
typedef double FT;
#define asFT static_cast<FT>
typedef long long Int64;
#define asInt64 static_cast<Int64>
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
const int size = 50005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int crt, msiz, tsiz, siz[size];
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int csiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            csiz = std::max(csiz, siz[v]);
        }
    }
    csiz = std::max(csiz, tsiz - siz[u]);
    if(csiz < msiz)
        msiz = csiz, crt = u;
}
int getRoot(int u, int usiz) {
    msiz = 1 << 30, tsiz = usiz;
    getRootImpl(u, 0);
    return crt;
}
int m, LN[10], maxL = 0, LA, LB, PCA[size], PCB[size];
Int64 ans = 0;
void DFS(int u, int p, int len) {
    LB = std::max(len, LB);
    ++PCB[len];
    if(len < maxL) {
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(v != p && !vis[v])
                DFS(v, u, len + 1);
        }
    }
}
void solve(int u) {
    LA = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            LB = 0;
            DFS(v, u, 1);
            for(int k = 0; k < m; ++k) {
                int cl = LN[k],
                    end = std::min(LB, cl - 1);
                for(int j = std::max(cl - LA, 1);
                    j <= end; ++j)
                    ans +=
                        asInt64(PCB[j]) * PCA[cl - j];
            }
            for(int j = 1; j <= LB; ++j)
                PCA[j] += PCB[j];
            LA = std::max(LA, LB);
            memset(PCB + 1, 0, sizeof(int) * LB);
        }
    }
    for(int i = 0; i < m; ++i)
        ans += PCA[LN[i]];
    memset(PCA + 1, 0, sizeof(int) * LA);
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            divide(nrt);
        }
    }
}
FT calc(int n, int m) {
    FT a = asFT(m) * (m - 1);
    FT b = asFT(n) * (n - 1);
    return a / b;
}
int main() {
    int n = read();
    m = read();
    for(int i = 0; i < m; ++i) {
        LN[i] = read();
        maxL = std::max(maxL, LN[i]);
    }
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    divide(getRoot(1, n));
    int d = n % 3, base = n / 3;
    printf("%.2lf\n", ans * calc(n, base + (d != 0)));
    printf("%.2lf\n", ans * calc(n, base + (d == 2)));
    printf("%.2lf\n", ans * calc(n, base));
    return 0;
}
