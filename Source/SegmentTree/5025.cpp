#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 500005, psiz = size << 2;
struct Edge {
    int to, nxt;
} E[size * 40];
int last[psiz], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
int pid[size];
bool leaf[psiz];
void build(int l, int r, int id) {
    if(l == r) {
        pid[l] = id;
        leaf[id] = true;
    } else {
        int m = (l + r) >> 1;
        build(ls);
        addEdge(id, id << 1);
        build(rs);
        addEdge(id, id << 1 | 1);
    }
}
int nl, nr, p;
void link(int l, int r, int id) {
    if(nl <= l && r <= nr)
        addEdge(p, id);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            link(ls);
        if(m < nr)
            link(rs);
    }
}
int dfn[psiz], low[psiz], icnt = 0, st[psiz], top = 0,
                          col[psiz], cw[psiz],
                          ccnt = 0;
bool flag[psiz];
void tarjan(int u) {
    dfn[u] = low[u] = ++icnt;
    st[++top] = u;
    flag[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(dfn[v]) {
            if(flag[v])
                low[u] = std::min(low[u], dfn[v]);
        } else {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int c = ++ccnt, v;
        do {
            v = st[top--];
            col[v] = c;
            cw[c] += leaf[v];
            flag[v] = false;
        } while(v != u);
    }
}
std::vector<int> G[psiz];
int in[psiz], q[psiz];
void topSortDp() {
    int qsiz = 0;
    for(int i = 1; i <= ccnt; ++i)
        if(!in[i])
            q[++qsiz] = i;
    for(int i = 1; i <= qsiz; ++i) {
        int u = q[i];
        std::sort(G[u].begin(), G[u].end());
        int siz =
            std::unique(G[u].begin(), G[u].end()) -
            G[u].begin();
        for(int j = 0; j < siz; ++j) {
            int v = G[u][j];
            cw[v] += cw[u];
            if(--in[v] == 0)
                q[++qsiz] = v;
        }
    }
}
Int64 x[size], r[size];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i) {
        x[i] = read();
        r[i] = read();
    }
    build(1, n, 1);
    for(int i = 1; i <= n; ++i) {
        nl = std::lower_bound(x + 1, x + n + 1,
                              x[i] - r[i]) -
            x;
        nr = std::upper_bound(x + 1, x + n + 1,
                              x[i] + r[i]) -
            x - 1;
        if(nl != nr) {
            p = pid[i];
            link(1, n, 1);
        }
    }
    int end = pid[n];
    for(int i = 1; i <= end; ++i)
        if(!dfn[i])
            tarjan(i);
    for(int i = 1; i <= end; ++i) {
        int ci = col[i];
        for(int j = last[i]; j; j = E[j].nxt) {
            int v = E[j].to, cv = col[v];
            if(ci != cv) {
                G[cv].push_back(ci);
                ++in[ci];
            }
        }
    }
    topSortDp();
    Int64 ans = 0;
    for(int i = 1; i <= n; ++i) {
        int ci = col[pid[i]];
        Int64 w = cw[ci];
        ans += i * w;
    }
    printf("%lld\n", ans % 1000000007);
    return 0;
}
