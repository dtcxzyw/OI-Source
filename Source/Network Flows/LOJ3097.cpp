#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long Int64;
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
int iabs(int x) {
    return x >= 0 ? x : -x;
}
const int size = 12005;
struct Edge {
    int to, nxt, f, w;
} E[70005];
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
int S, T, tot, q[size];
Int64 dis[size];
bool flag[size];
bool SPFA() {
    memset(dis + 1, 0x3f, sizeof(Int64) * tot);
    q[0] = T, dis[T] = 0, flag[T] = true;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            Int64 dv = dis[u] + E[i ^ 1].w;
            if(E[i ^ 1].f && dv < dis[v]) {
                dis[v] = dv;
                if(!flag[v]) {
                    flag[v] = true;
                    if(b != e && dis[q[b]] > dis[v]) {
                        if(--b == -1)
                            b += size;
                        q[b] = v;
                    } else {
                        q[e++] = v;
                        if(e == size)
                            e = 0;
                    }
                }
            }
        }
    }
    return dis[S] != 0x3f3f3f3f3f3f3f3f;
}
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    flag[u] = true;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!flag[v] && dis[v] + E[i].w == dis[u] &&
           (k = DFS(v, std::min(f, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    flag[u] = false;
    if(res == 0)
        dis[u] = -1;
    return res;
}
Int64 MCMF() {
    Int64 res = 0;
    while(SPFA()) {
        Int64 ds = dis[S];
        memcpy(now, last, sizeof(now));
        int cf, sf = 0;
        while((cf = DFS(S, 1 << 30)))
            sf += cf;
        res += sf * ds;
    }
    return res;
}
int A[size], B[size], C[size], n;
void link(int l, int r) {
    if(l == r)
        return;
    int m = (l + r) >> 1;
    link(l, m);
    link(m + 1, r);
    std::inplace_merge(B + l, B + m + 1, B + r + 1);
    int last = 0, num = 0;
    for(int i = l; i <= r; ++i) {
        if(last && B[i] == C[last])
            continue;
        ++num;
        C[num] = B[i];
        if(last) {
            int del = C[num] - C[last];
            addEdge(tot + last, tot + num, 1 << 30,
                    del);
            addEdge(tot + num, tot + last, 1 << 30,
                    del);
        }
        last = num;
    }
    for(int i = l; i <= r; ++i) {
        int id = tot + (std::lower_bound(
                            C + 1, C + num + 1, A[i]) -
                        C);
        if(i <= m)
            addEdge(i, id, 1, 0);
        else
            addEdge(id, i + n, 1, 0);
    }
    tot += num;
}
int main() {
    int w;
    scanf("%d%d", &n, &w);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &A[i]);
    S = 2 * n + 1;
    T = S + 1;
    for(int i = 1; i <= n; ++i) {
        addEdge(S, i, 1, 0);
        addEdge(S, n + i, 1, w);
        addEdge(n + i, T, 1, 0);
    }
    memcpy(B + 1, A + 1, sizeof(int) * n);
    tot = T;
    link(1, n);
    printf("%lld\n", MCMF());
    return 0;
}
