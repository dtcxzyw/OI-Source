#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
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
const int size = 100005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int siz[size], nrt, cmsiz, tsiz;
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p || vis[v])
            continue;
        getRootImpl(v, u);
        siz[u] += siz[v];
        msiz = std::max(msiz, siz[v]);
    }
    msiz = std::max(msiz, tsiz - siz[u]);
    if(cmsiz > msiz)
        cmsiz = msiz, nrt = u;
}
int getRoot(int u, int usiz) {
    cmsiz = 1 << 30, tsiz = usiz;
    getRootImpl(u, 0);
    return nrt;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 ans = 0, B[size];
int D[size], maxd, rt;
struct Info {
    int rt, v, dis;
    Info(int rt, int v, int dis)
        : rt(rt), v(v), dis(dis) {}
};
std::vector<Info> A[size];
void DFS(int u, int p, int d) {
    if(rt)
        A[u].push_back(Info(rt, p, d));
    ++D[d];
    maxd = std::max(maxd, d);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p || vis[v])
            continue;
        DFS(v, u, d + 1);
    }
}
std::vector<int> C[size];
int fa[size];
void solve(int u) {
    rt = u;
    std::vector<int>& c = C[u];
    c.push_back(1);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(vis[v])
            continue;
        maxd = 0;
        DFS(v, u, 1);
        if(c.size() < maxd + 1)
            c.resize(maxd + 1);
        for(int j = 1; j <= maxd; ++j) {
            ans += D[j] * B[j];
            B[j] += asInt64(D[j]) * c[j];
            c[j] += D[j];
        }
        memset(D + 1, 0, sizeof(int) * maxd);
    }
    rt = 0;
    for(int i = 0; i < A[u].size(); ++i) {
        std::vector<int>& X = C[A[u][i].rt];
        int v = A[u][i].v;
        if(!vis[v]) {
            maxd = 0;
            DFS(v, u, 1);
            for(int j = 1; j <= maxd; ++j) {
                c[j] -= D[j];
                B[j] -= asInt64(D[j]) * c[j];
            }
        }
        int d = A[u][i].dis;
        for(int j = d;
            j < c.size() && j - d < X.size(); ++j)
            ans += B[j] * X[j - d];
        if(!vis[v]) {
            for(int j = 1; j <= maxd; ++j) {
                B[j] += asInt64(D[j]) * c[j];
                c[j] += D[j];
            }
            memset(D + 1, 0, sizeof(int) * maxd);
        }
    }
    memset(B, 0, sizeof(Int64) * c.size());
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    std::vector<int>& c = C[u];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            {
                maxd = 0;
                DFS(v, u, 1);
                for(int j = 1; j <= maxd; ++j)
                    c[j] -= D[j];
                memset(D + 1, 0, sizeof(int) * maxd);
            }
            int crt = getRoot(v, siz[v]);
            divide(crt);
            {
                maxd = 0;
                DFS(v, u, 1);
                for(int j = 1; j <= maxd; ++j)
                    c[j] += D[j];
                memset(D + 1, 0, sizeof(int) * maxd);
            }
        }
    }
}
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    divide(getRoot(1, n));
    printf("%lld\n", ans);
    return 0;
}
