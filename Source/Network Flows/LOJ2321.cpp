#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int maxn = 2005, size = maxn * 4,
          inf = 0x3f3f3f3f;
struct Edge {
    int to, rev, f, w;
    Edge(int to, int rev, int f, int w)
        : to(to), rev(rev), f(f), w(w) {}
};
std::vector<Edge> G[size];
void addEdge(int u, int v, int f, int w) {
    int urev = G[u].size(), vrev = G[v].size();
    G[u].push_back(Edge(v, vrev, f, w));
    G[v].push_back(Edge(u, urev, 0, -w));
}
int dis[size], q[size], S, T;
bool flag[size];
bool SPFA(int n) {
    memset(dis + 1, 0x3f, sizeof(int) * n);
    dis[T] = 0, q[0] = T, flag[T] = true;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(auto E : G[u]) {
            int v = E.to;
            int dv = dis[u] - E.w;
            if(G[v][E.rev].f && dv < dis[v]) {
                dis[v] = dv;
                if(!flag[v]) {
                    flag[v] = true;
                    if(b == e || dis[q[b]] <= dis[v]) {
                        q[e++] = v;
                        if(e == size)
                            e = 0;
                    } else {
                        if(--b == -1)
                            b = size - 1;
                        q[b] = v;
                    }
                }
            }
        }
    }
    return dis[S] != inf;
}
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    flag[u] = true;
    int res = 0, k;
    for(int& i = now[u]; i < G[u].size(); ++i) {
        Edge& E = G[u][i];
        int v = E.to;
        if(E.f && !flag[v] && dis[v] + E.w == dis[u] &&
           (k = DFS(v, std::min(f, E.f)))) {
            E.f -= k, G[v][E.rev].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    flag[u] = false;
    if(!res)
        dis[u] = -1;
    return res;
}
int MCMF(int n, int f) {
    int res = 0, sumf = 0;
    while(SPFA(n)) {
        memset(now + 1, 0, sizeof(int) * n);
        int sf = 0, cf, cd = dis[S];
        while((cf = DFS(S, inf)))
            sf += cf;
        res += sf * cd;
        sumf += sf;
    }
    return sumf == f ? res : -1;
}
int id[maxn][maxn][4], bcnt[16];
void addEdgeAuto(int u, int v, int f, int w,
                 bool col) {
    if(col)
        addEdge(v, u, f, w);
    else
        addEdge(u, v, f, w);
}
void buildGraph(int i, int j, int v, int src,
                bool col) {
    switch(bcnt[v]) {
        case 1: {
            int base, ori;
            for(int k = 0; k < 4; ++k)
                if(v & (1 << k)) {
                    ori = k;
                    base = id[i][j][k];
                    break;
                }
            addEdgeAuto(src, base, 1, 0, col);
            for(int k = 0; k < 4; ++k)
                if(!(v & (1 << k))) {
                    int cid = id[i][j][k];
                    addEdgeAuto(base, cid, 1,
                                (ori ^ k) == 2 ? 2 : 1,
                                col);
                }
        } break;
        case 2: {
            int base[2], ori[2], bcnt = 0;
            bool orif[4] = {};
            for(int k = 0; k < 4; ++k)
                if(v & (1 << k)) {
                    orif[k] = true;
                    base[bcnt] = id[i][j][k];
                    ori[bcnt] = k;
                    ++bcnt;
                }
            addEdgeAuto(src, base[0], 1, 0, col);
            addEdgeAuto(src, base[1], 1, 0, col);
            if(!((orif[0] && orif[2]) ||
                 (orif[1] && orif[3]))) {
                addEdgeAuto(base[0],
                            id[i][j][ori[0] ^ 2], 1, 1,
                            col);
                addEdgeAuto(base[1],
                            id[i][j][ori[1] ^ 2], 1, 1,
                            col);
            }
        } break;
        case 3: {
            int base, ori;
            for(int k = 0; k < 4; ++k)
                if(!(v & (1 << k))) {
                    base = id[i][j][k];
                    ori = k;
                    break;
                }
            for(int k = 0; k < 4; ++k)
                if(v & (1 << k)) {
                    int cid = id[i][j][k];
                    addEdgeAuto(src, cid, 1, 0, col);
                    addEdgeAuto(cid, base, 1,
                                (k ^ ori) == 2 ? 2 : 1,
                                col);
                }
        } break;
        case 4: {
            for(int k = 0; k < 4; ++k) {
                int cid = id[i][j][k];
                addEdgeAuto(src, cid, 1, 0, col);
            }
        } break;
    }
}
const int off[4][2] = { { -1, 0 },
                        { 0, 1 },
                        { 1, 0 },
                        { 0, -1 } };
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int vcnt = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            for(int k = 0; k < 4; ++k)
                id[i][j][k] = ++vcnt;
    S = ++vcnt;
    T = ++vcnt;
    for(int i = 1; i < 16; ++i)
        bcnt[i] = bcnt[i >> 1] + (i & 1);
    int ocnt[2] = {};
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            bool col = (i + j) & 1;
            int src = col ? T : S;
            int v;
            scanf("%d", &v);
            buildGraph(i, j, v, src, col);
            ocnt[col] += bcnt[v];
        }
    if(ocnt[0] != ocnt[1]) {
        puts("-1");
        return 0;
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            if((i + j) & 1)
                for(int k = 0; k < 4; ++k) {
                    int sid = id[i][j][k];
                    int ox = i + off[k][0],
                        oy = j + off[k][1], ok = k ^ 2;
                    int cid = id[ox][oy][ok];
                    if(cid)
                        addEdge(cid, sid, 1, 0);
                }
    printf("%d\n", MCMF(vcnt, ocnt[0]));
    return 0;
}
