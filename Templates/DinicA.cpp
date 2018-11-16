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
const int size = 10005;
struct Edge {
    int to, nxt, f;
} E[200005];
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
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, mf -= k;
            if(mf == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
int dinic(int siz) {
    int res = 0;
    while(BFS(siz)) {
        memcpy(now + 1, last + 1, sizeof(int) * siz);
        res += DFS(S, 1 << 30);
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
