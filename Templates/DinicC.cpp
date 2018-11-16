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
const int size = 1205;
struct Edge {
    int to, nxt, f, df;
} E[240005];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
int q[size], d[size], S, T;
bool BFS(int siz) {
    memset(d + 1, -1, sizeof(int) * siz);
    d[S] = 0, q[0] = S;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f && d[v] == -1) {
                d[v] = d[u] + 1;
                if(v == T)
                    return true;
                q[e++] = v;
            }
        }
    }
    return false;
}
int now[size];
int DFS(int u, int mf) {
    if(u == T || mf == 0)
        return mf;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] == d[u] + 1 &&
           (k = DFS(v, std::min(mf, E[i].f)))) {
            E[i].f -= k, E[i].df += k;
            res += k, mf -= k;
            if(mf == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
void cook() {
    for(int i = 2; i <= cnt; i += 2) {
        E[i].f += E[i ^ 1].df;
        E[i ^ 1].f += E[i].df;
        E[i].df = E[i ^ 1].df = 0;
    }
}
int dinic(int siz) {
    int res = 0;
    while(BFS(siz)) {
        do {
            memcpy(now + 1, last + 1,
                   sizeof(int) * siz);
            res += DFS(S, 2147483647);
        } while(BFS(siz));
        cook();
    }
    return res;
}
int main() {
    int n = read();
    int m = read();
    S = read();
    T = read();
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
    }
    printf("%d\n", dinic(n));
    return 0;
}
