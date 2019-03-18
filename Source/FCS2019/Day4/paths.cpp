#include <algorithm>
#include <cstdio>
const int size = 1005;
struct Info {
    int u, v, w;
    bool operator<(const Info& rhs) const {
        return w < rhs.w;
    }
} A[size];
int fa[size];
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 1;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int use[size * 2];
bool col(int u, int p, int dst) {
    if(u == dst)
        return true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            if(col(v, u, dst)) {
                use[i] = true;
                return true;
            }
        }
    }
    return false;
}
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; ++i)
        scanf("%d%d%d", &A[i].u, &A[i].v, &A[i].w);
    std::sort(A + 1, A + m + 1);
    bool flag = false;
    for(int i = 1; i <= m; ++i) {
        int u = find(A[i].u), v = find(A[i].v);
        if(u != v) {
            fa[u] = v;
            addEdge(A[i].u, A[i].v, A[i].w);
            addEdge(A[i].v, A[i].u, A[i].w);
            int lcnt = 0;
            for(int j = 2; j <= k; j += 2)
                lcnt += (find(j - 1) == find(j));
            if(lcnt * 2 == k) {
                flag = true;
                break;
            }
        }
    }
    if(flag) {
        for(int j = 2; j <= k; j += 2)
            col(j, 0, j - 1);
        int res = 0;
        for(int j = 2; j <= cnt; j += 2)
            if(use[j] || use[j ^ 1])
                res += E[j].w;
        printf("%d\n", res);
    } else
        puts("-1");
    return 0;
}
