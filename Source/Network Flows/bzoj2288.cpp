#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 100015;
struct Edge {
    int to, nxt, f, w;
} E[6 * size];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v, int f, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f,
    E[cnt].w = w;
    last[u] = cnt;
}
void addEdge(int u, int v, int f, int w) {
    addEdgeImpl(u, v, f, w);
    addEdgeImpl(v, u, 0, -w);
}
int dis[size], q[size], S, T;
bool flag[size];
bool SPFA() {
    memset(dis + 1, 0xc0, sizeof(int) * T);
    int b = 0, e = 1;
    dis[T] = 0, q[b] = T, flag[T] = true;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to, dv = dis[u] - E[i].w;
            if(E[i ^ 1].f && dv > dis[v]) {
                dis[v] = dv;
                if(!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if(e == size)
                        e = 0;
                }
            }
        }
    }
    return dis[S] != static_cast<int>(0xc0c0c0c0);
}
int now[size];
bool vis[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    vis[u] = true;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v] && dis[u] == dis[v] + E[i].w &&
           (k = DFS(v, std::min(E[i].f, f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            f -= k, res += k;
            if(f == 0)
                break;
        }
    }
    if(res)
        vis[u] = false;
    return res;
}
int MCMF() {
    int res = 0;
    while(SPFA()) {
        memset(vis + 1, 0, sizeof(bool) * T);
        memcpy(now + 1, last + 1, sizeof(int) * T);
        int sf = 0, cf;
        while((cf = DFS(S, 1 << 30)))
            sf += cf;
        res += dis[S] * sf;
    }
    return res;
}
int A[size];
int main() {
    int n = read();
    int m = read();
    int rn = 0;
    for(int i = 1; i <= n; ++i) {
        int val = read();
        if(val) {
            if(rn == 0 || (val ^ A[rn]) < 0)
                A[++rn] = val;
            else
                A[rn] += val;
        }
    }
    int SS = rn + 2;
    S = SS + 1, T = S + 1;
    addEdge(S, SS, m, 0);
    for(int i = 1; i <= rn; ++i) {
        addEdge(SS, i, 1, 0);
        addEdge(i, i + 1, 1, A[i]);
        addEdge(i + 1, T, 1, 0);
    }
    printf("%d\n", std::max(0, MCMF()));
    return 0;
}
