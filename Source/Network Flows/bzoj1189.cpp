#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 25, vsiz = 5005;
struct Edge {
    int to, nxt, f;
} E[100005];
int last[vsiz], cnt;
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
    memset(gap, 0, sizeof(gap));
    memset(d, 0, sizeof(d));
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
int now[vsiz], siz;
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
        d[S] = siz + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP(int csiz) {
    siz = csiz;
    BFS();
    if(d[S] == 0)
        return 0;
    memcpy(now, last, sizeof(last));
    int res = 0;
    while(d[S] <= siz)
        res += aug(S, 1 << 30);
    return res;
}
const int off[4][2] = { { -1, 0 },
                        { 1, 0 },
                        { 0, -1 },
                        { 0, 1 } };
int id[size][size], dis[size][size], bq[vsiz][2],
    tid[vsiz];
char map[size][size];
void build(int sx, int sy, int mid, int& icnt) {
    memset(dis, 0x3f, sizeof(dis));
    bq[0][0] = sx, bq[0][1] = sy, dis[sx][sy] = 0;
    int b = 0, e = 1;
    for(int i = 1; i <= mid; ++i) {
        tid[i] = ++icnt;
        addEdge(tid[i], T, 1);
        if(i > 1)
            addEdge(tid[i - 1], tid[i], 1 << 30);
    }
    while(b != e) {
        int cx = bq[b][0], cy = bq[b][1];
        ++b;
        int nd = dis[cx][cy] + 1;
        if(nd > mid)
            continue;
        for(int i = 0; i < 4; ++i) {
            int nx = cx + off[i][0],
                ny = cy + off[i][1];
            if(map[nx][ny] == '.' &&
               dis[nx][ny] == 0x3f3f3f3f) {
                dis[nx][ny] = nd;
                addEdge(id[nx][ny], tid[nd], 1 << 30);
                bq[e][0] = nx, bq[e][1] = ny;
                ++e;
            }
        }
    }
}
bool check(int n, int m, int mid, int icnt) {
    S = ++icnt;
    T = ++icnt;
    memset(last, 0, sizeof(last));
    cnt = 1;
    int xcnt = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            if(map[i][j] == 'D')
                build(i, j, mid, icnt);
            else if(map[i][j] == '.')
                addEdge(S, id[i][j], 1), ++xcnt;
        }
    return ISAP(icnt) == xcnt;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int icnt = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", map[i] + 1);
        for(int j = 1; j <= m; ++j)
            if(map[i][j] == '.')
                id[i][j] = ++icnt;
    }
    int l = 0, r = n * m, ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(n, m, mid, icnt))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    if(ans == -1)
        puts("impossible");
    else
        printf("%d\n", ans);
    return 0;
}
