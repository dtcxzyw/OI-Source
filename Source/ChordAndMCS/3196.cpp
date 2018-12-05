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
const int size = 10005;
struct Graph {
    struct Edge {
        int to, nxt;
    } E[size * 200];
    int last[size], cnt;
    Graph() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} G, L;
int id[size], label[size];
int main() {
    int n = read();
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        G.addEdge(u, v);
        G.addEdge(v, u);
    }
    for(int i = 1; i <= n; ++i)
        L.addEdge(0, i);
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
                id[u] = cid--;
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
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        int cnt = 1;
        for(int j = G.last[i]; j; j = G.E[j].nxt) {
            int v = G.E[j].to;
            cnt += id[v] > id[i];
        }
        if(cnt > res)
            res = cnt;
    }
    printf("%d\n", res);
    return 0;
}
