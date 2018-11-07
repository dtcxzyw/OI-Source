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
const int size = 55;
struct Edge {
    int to, nxt, f;
} E[1005];
int last[size], cnt;
void addEdge(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
int q[size], d[size], n;
bool BFS() {
    memset(d + 1, -1, sizeof(int) * n);
    int b = 0, e = 1;
    q[b] = 1, d[1] = 0;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f && d[v] == -1) {
                d[v] = d[u] + 1;
                if(v == 2)
                    return true;
                q[e++] = v;
            }
        }
    }
    return false;
}
int now[size];
int DFS(int u, int mf) {
    if(mf == 0 || u == 2)
        return mf;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] == d[u] + 1 &&
           (k = DFS(v, std::min(mf, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            mf -= k, res += k;
            if(mf == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
void dinic() {
    while(BFS()) {
        memcpy(now + 1, last + 1, sizeof(int) * n);
        DFS(1, 1 << 30);
    }
}
bool query(int u) {
    return d[u] == -1;
}
int main() {
    while(true) {
        n = read();
        if(n == 0)
            break;
        int m = read();
        cnt = 1;
        memset(last + 1, 0, sizeof(int) * n);
        while(m--) {
            int u = read();
            int v = read();
            int w = read();
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        dinic();
        for(int i = 1; i <= n; ++i)
            if(query(i)) {
                for(int j = last[i]; j; j = E[j].nxt) {
                    int v = E[j].to;
                    if(!query(v))
                        printf("%d %d\n", i, v);
                }
            }
        puts("");
    }
    return 0;
}
