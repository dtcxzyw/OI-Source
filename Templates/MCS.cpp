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
const int size = 1005;
struct Graph {
    struct Edge {
        int to, nxt;
    } E[size * size];
    int last[size], cnt;
    void reset(int n) {
        cnt = 0;
        memset(last, 0, sizeof(int) * (n + 1));
    }
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} G, L;
bool link[size][size];
int id[size], label[size];
bool foo(int n, int m) {
    G.reset(n);
    L.reset(n);
    memset(link, 0, sizeof(link));
    while(m--) {
        int u = read();
        int v = read();
        G.addEdge(u, v);
        G.addEdge(v, u);
        link[u][v] = link[v][u] = true;
    }
    for(int i = 1; i <= n; ++i)
        L.addEdge(0, i);
    memset(label + 1, 0, sizeof(int) * n);
    memset(id + 1, 0, sizeof(int) * n);
    int highest = 0, cid = n;
    while(highest != -1 && cid) {
        if(L.last[highest] == 0) {
            --highest;
            continue;
        }
        for(int& i = L.last[highest]; i;
            i = L.E[i].nxt) {
            int u = L.E[i].to;
            if(!id[u]) {
                id[u] = cid;
                --cid;
                for(int i = G.last[u]; i;
                    i = G.E[i].nxt) {
                    int v = G.E[i].to;
                    if(!id[v]) {
                        L.addEdge(++label[v], v);
                        if(label[v] > highest)
                            highest = label[v];
                    }
                }
                break;
            }
        }
    }
    id[0] = 1 << 30;
    for(int u = 1; u <= n; ++u) {
        int v0 = 0;
        for(int j = G.last[u]; j; j = G.E[j].nxt) {
            int v = G.E[j].to;
            if(id[v] > id[u] && id[v] < id[v0])
                v0 = v;
        }
        if(v0) {
            for(int j = G.last[u]; j; j = G.E[j].nxt) {
                int v = G.E[j].to;
                if(v != v0 && id[v] > id[u] &&
                   !link[v0][v])
                    return false;
            }
        }
    }
    return true;
}
int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0)
            break;
        puts(foo(n, m) ? "Perfect" : "Imperfect");
    }
    return 0;
}
