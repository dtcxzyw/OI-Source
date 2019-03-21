#include <cstdio>
#include <cstring>
typedef long long Int64;
const int size = 1005;
struct Edge {
    int to, nxt;
    Int64 w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, Int64 w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
Int64 d[size];
int q[size], pre[size], eid[size];
bool use[size], flag[size];
bool SPFA(int S, int T) {
    memset(flag, 0, sizeof(flag));
    memset(d, 0x3f, sizeof(d));
    int b = 0, e = 1;
    q[0] = S, d[S] = 0, flag[S] = true;
    while(b != e) {
        int u = q[b++];
        flag[u] = false;
        if(b == size)
            b = 0;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(d[v] > d[u] + E[i].w) {
                d[v] = d[u] + E[i].w;
                pre[v] = u;
                eid[v] = i;
                if(!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if(e == size)
                        e = 0;
                }
            }
        }
    }
    if(d[T] != 0x3f3f3f3f3f3f3f3f) {
        int p = T;
        while(p != S) {
            use[eid[p]] = true;
            p = pre[p];
        }
        return true;
    }
    return false;
}
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        Int64 w;
        scanf("%d%d%lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    for(int i = 1; i <= k; i += 2)
        if(!SPFA(i, i + 1)) {
            puts("-1");
            return 0;
        }
    Int64 res = 0;
    for(int i = 1; i <= cnt; i += 2)
        if(use[i] || use[i + 1])
            res += E[i].w;
    printf("%lld\n", res);
    return 0;
}
