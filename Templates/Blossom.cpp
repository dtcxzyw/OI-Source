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
const int size = 505;
struct Edge {
    int to, nxt;
} E[size * size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int fa[size];
int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}
int match[size], q[size * size], d[size], pre[size],
    cts = 0, ts[size];
int getLCA(int u, int v) {
    ++cts;
    while(true) {
        if(u) {
            u = find(u);
            if(ts[u] == cts)
                return u;
            else
                ts[u] = cts, u = pre[match[u]];
        }
        std::swap(u, v);
    }
}
void contract(int u, int v, int p, int& e) {
    while(find(u) != p) {
        pre[u] = v;
        v = match[u];
        if(d[v] == 2)
            d[v] = 1, q[e++] = v;
        if(fa[u] == 0)
            fa[u] = p;
        if(fa[v] == 0)
            fa[v] = p;
        u = pre[v];
    }
}
bool aug(int s, int n) {
    memset(fa + 1, 0, sizeof(int) * n);
    memset(d + 1, 0, sizeof(int) * n);
    memset(pre + 1, 0, sizeof(int) * n);
    q[0] = s, d[s] = 1;
    int b = 0, e = 1;
    while(b < e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(find(u) == find(v))
                continue;
            if(d[v] == 1) {
                int lca = getLCA(u, v);
                contract(u, v, lca, e);
                contract(v, u, lca, e);
            } else if(d[v] == 0) {
                d[v] = 2, pre[v] = u;
                if(!match[v]) {
                    int cp = v;
                    while(cp) {
                        int p = pre[cp];
                        match[cp] = p;
                        std::swap(cp, match[p]);
                    }
                    return true;
                }
                d[match[v]] = 1, q[e++] = match[v];
            }
        }
    }
    return false;
}
int main() {
    int n = read();
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    int res = 0;
    for(int i = 1; i <= n; ++i)
        if(!match[i])
            for(int j = last[i]; j; j = E[j].nxt) {
                int v = E[j].to;
                if(!match[v]) {
                    match[v] = i, match[i] = v, ++res;
                    break;
                }
            }
    for(int i = 1; i <= n; ++i)
        if(match[i] == 0 && aug(i, n))
            ++res;
    printf("%d\n", res);
    for(int i = 1; i <= n; ++i)
        printf("%d ", match[i]);
    return 0;
}
