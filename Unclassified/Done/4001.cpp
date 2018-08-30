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
const int size = 1010, vsiz = size * size * 2;
struct Edge {
    int to, next, w;
} E[3 * vsiz];
int last[vsiz] = {}, cnt = 0;
void addEdgeImpl(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u], E[cnt].w = w;
    last[u] = cnt;
}
void addEdge(int u, int v, int w) {
    addEdgeImpl(u, v, w);
    addEdgeImpl(v, u, w);
}
const int S = 1, T = 2;
int dis[vsiz], q[vsiz];
bool flag[vsiz] = {};
void SPFA() {
    memset(dis, 0x3f, sizeof(dis));
    int b = 0, e = 1;
    q[0] = S, dis[S] = 0, flag[S] = true;
    while(b != e) {
        int u = q[b];
        flag[u] = false;
        b = (b + 1) % vsiz;
        for(int i = last[u]; i; i = E[i].next) {
            int v = E[i].to;
            if(dis[v] > dis[u] + E[i].w) {
                dis[v] = dis[u] + E[i].w;
                if(!flag[v]) {
                    flag[v] = true;
                    q[e] = v;
                    e = (e + 1) % vsiz;
                }
            }
        }
    }
}
int ID[size][size][2];
int main() {
    int n = read();
    int m = read();
    int icnt = 2;
    for(int i = 1; i < n; ++i)
        for(int j = 1; j < m; ++j) {
            ID[i][j][0] = ++icnt;
            ID[i][j][1] = ++icnt;
        }
    for(int i = 1; i <= n; ++i)
        ID[i][0][0] = ID[i][0][1] = S,
        ID[i][m][0] = ID[i][m][1] = T;
    for(int i = 1; i <= m; ++i)
        ID[0][i][0] = ID[0][i][1] = T,
        ID[n][i][0] = ID[n][i][1] = S;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j < m; ++j)
            addEdge(ID[i - 1][j][0], ID[i][j][1],
                    read());
    for(int i = 1; i < n; ++i)
        for(int j = 1; j <= m; ++j)
            addEdge(ID[i][j - 1][1], ID[i][j][0],
                    read());
    for(int i = 1; i < n; ++i)
        for(int j = 1; j < m; ++j)
            addEdge(ID[i][j][0], ID[i][j][1], read());
    SPFA();
    printf("%d\n", dis[T]);
    return 0;
}
