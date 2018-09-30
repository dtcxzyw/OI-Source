#include <algorithm>
#include <cstdio>
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
const int size = 105, maxm = 1005, mod = 31011;
struct Edge {
    int u, v, w;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
} E[maxm];
int fa[size], end[maxm], refCount[maxm], cnt;
int find(int u) {
    return fa[u] == u ? u : find(fa[u]);
}
void DFS(int p, int e, int rem) {
    if(rem) {
        if(p < e) {
            int u = find(E[p].u), v = find(E[p].v);
            if(u != v) {
                fa[u] = v;
                DFS(p + 1, e, rem - 1);
                fa[u] = u, fa[v] = v;
            }
            DFS(p + 1, e, rem);
        }
    } else
        ++cnt;
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i)
        fa[i] = i;
    for(int i = 1; i <= m; ++i) {
        E[i].u = read();
        E[i].v = read();
        E[i].w = read();
    }
    std::sort(E + 1, E + m + 1);
    int ecnt = 0, wcnt = 0;
    end[0] = 1;
    for(int i = 1; i <= m; ++i) {
        if(E[i].w != E[i - 1].w)
            end[wcnt++] = i;
        int u = find(E[i].u), v = find(E[i].v);
        if(u != v) {
            fa[u] = v;
            ++ecnt;
            ++refCount[wcnt];
        }
    }
    end[wcnt] = m + 1;
    if(ecnt == n - 1) {
        long long ans = 1;
        for(int i = 1; i <= n; ++i)
            fa[i] = i;
        int cur = 1;
        for(int i = 1; i <= wcnt; ++i) {
            cnt = 0;
            DFS(end[i - 1], end[i], refCount[i]);
            ans = ans * cnt % mod;
            while(cur < end[i]) {
                int u = find(E[cur].u),
                    v = find(E[cur].v);
                if(u != v)
                    fa[u] = v;
                ++cur;
            }
        }
        printf("%lld\n", ans);
    } else
        puts("0");
    return 0;
}
