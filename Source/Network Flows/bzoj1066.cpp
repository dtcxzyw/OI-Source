#include <algorithm>
#include <cstdio>
#include <cstring>
int iabs(int x) {
    return x >= 0 ? x : -x;
}
const int size = 25, vsiz = 2 * size * size;
struct Edge {
    int to, nxt, f;
} E[size * size * 66 * 2];
int last[vsiz], cnt = 1;
void addEdgeImpl(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
void addEdge(int u, int v, int f) {
    addEdgeImpl(u, v, f);
    addEdgeImpl(v, u, 0);
}
int S, T, d[vsiz], q[vsiz], gap[vsiz];
void BFS() {
    d[T] = 1, ++gap[d[T]], q[0] = T;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i ^ 1].f && d[v] == 0) {
                d[v] = d[u] + 1;
                q[e++] = v;
                ++gap[d[v]];
            }
        }
    }
}
int now[vsiz];
int aug(int u, int f) {
    if(u == T || f == 0)
        return f;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] + 1 == d[u] &&
           (k = aug(v, std::min(f, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f == 0)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = T + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP() {
    BFS();
    if(d[S] == 0)
        return 0;
    memcpy(now, last, sizeof(last));
    int res = 0;
    while(d[S] <= T)
        res += aug(S, 1 << 30);
    return res;
}
int id[size][size], off[100][2];
int main() {
    int r, c, d;
    scanf("%d%d%d", &r, &c, &d);
    int ocnt = 0;
    for(int i = -d; i <= d; ++i)
        for(int j = -d; j <= d; ++j)
            if((i || j) && iabs(i) + iabs(j) <= d) {
                ++ocnt;
                off[ocnt][0] = i, off[ocnt][1] = j;
            }
    int icnt = 0;
    char buf[25];
    for(int i = 1; i <= r; ++i) {
        scanf("%s", buf + 1);
        for(int j = 1; j <= c; ++j) {
            id[i][j] = ++icnt;
            int x = buf[j] - '0';
            if(x)
                addEdge(id[i][j] << 1,
                        id[i][j] << 1 | 1, x);
        }
    }
    ++icnt;
    S = icnt << 1;
    T = icnt << 1 | 1;
    int num = 0;
    for(int i = 1; i <= r; ++i) {
        scanf("%s", buf + 1);
        for(int j = 1; j <= c; ++j) {
            if(buf[j] == 'L')
                addEdge(S, id[i][j] << 1, 1), ++num;
            bool out = false;
            for(int k = 1; k <= ocnt; ++k) {
                int ci = i + off[k][0],
                    cj = j + off[k][1];
                if(1 <= ci && ci <= r && 1 <= cj &&
                   cj <= c)
                    addEdge(id[i][j] << 1 | 1,
                            id[ci][cj] << 1, 1 << 30);
                else if(!out) {
                    addEdge(id[i][j] << 1 | 1, T, 1
                                << 30);
                    out = true;
                }
            }
        }
    }
    printf("%d\n", num - ISAP());
    return 0;
}
