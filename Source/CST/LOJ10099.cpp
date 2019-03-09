#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
const int size = 505;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int dfn[size], low[size], icnt;
bool cut[size];
void DFS(int u, int p) {
    dfn[u] = low[u] = ++icnt;
    int ssiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            if(dfn[v])
                low[u] = std::min(low[u], dfn[v]);
            else {
                ++ssiz;
                DFS(v, u);
                low[u] = std::min(low[u], low[v]);
                if(p && dfn[u] <= low[v])
                    cut[u] = true;
            }
        }
    }
    if(!p && ssiz >= 2)
        cut[u] = true;
}
bool vis[size];
int bsiz;
std::set<int> lc;
void color(int u) {
    vis[u] = true, ++bsiz;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(cut[v])
            lc.insert(v);
        else if(!vis[v])
            color(v);
    }
}
bool use[size];
void foo(int cid, int n) {
    icnt = 0;
    memset(last, 0, sizeof(last));
    memset(cut, 0, sizeof(cut));
    memset(vis, 0, sizeof(vis));
    memset(dfn, 0, sizeof(dfn));
    memset(use, 0, sizeof(use));
    cnt = 0;
    for(int i = 1; i <= n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
        use[u] = use[v] = true;
    }
    for(int i = 1; i < size; ++i)
        if(use[i] && !dfn[i])
            DFS(i, 0);
    int num = 0;
    long long res = 1;
    for(int i = 1; i < size; ++i)
        if(use[i] && !cut[i] && !vis[i]) {
            bsiz = 0;
            lc.clear();
            color(i);
            int ccnt = lc.size();
            if(ccnt == 1)
                res *= bsiz, ++num;
            else if(ccnt == 0 && bsiz)
                res *= static_cast<long long>(bsiz) *
                    (bsiz - 1) / 2,
                    num += 2;
        }
    printf("Case %d: %d %lld\n", cid, num, res);
}
int main() {
    int n, id = 0;
    while(scanf("%d", &n) != EOF && n)
        foo(++id, n);
    return 0;
}
