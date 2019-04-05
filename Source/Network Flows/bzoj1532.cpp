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
const int size = 20015;
struct Edge {
    int to, nxt, f;
} E[4 * size];
int last[size], cnt = 1;
void addEdgeImpl(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
void addEdge(int u, int v) {
    addEdgeImpl(u, v);
    addEdgeImpl(v, u);
}
int S, T, d[size], q[size];
bool BFS() {
    memset(d + 1, -1, sizeof(int) * T);
    int b = 0, e = 1;
    q[0] = T, d[T] = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i ^ 1].f && d[v] == -1) {
                d[v] = d[u] + 1;
                if(v == S)
                    return true;
                q[e++] = v;
            }
        }
    }
    return false;
}
int now[size];
int DFS(int u, int f) {
    if(u == T || f == 0)
        return f;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[u] == d[v] + 1 &&
           (k = DFS(v, std::min(f, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, f -= k;
            if(f == 0)
                break;
        }
    }
    if(res == 0)
        d[u] = -1;
    return res;
}
int Dinic() {
    int res = 0;
    while(BFS()) {
        memcpy(now + 1, last + 1, sizeof(int) * T);
        res += DFS(S, 1 << 30);
    }
    return res;
}
int main() {
    int n = read();
    int m = read();
    S = n + m + 1, T = S + 1;
    for(int i = 1; i <= m; ++i) {
        addEdge(S, i);
        addEdge(i, m + read());
        addEdge(i, m + read());
    }
    int end = cnt;
    for(int i = 1; i <= n; ++i)
        addEdge(i + m, T);
    int l = 1, r = m, ans = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        for(int i = 2; i <= end; i += 2)
            E[i].f = 1, E[i ^ 1].f = 0;
        for(int i = end + 1; i <= cnt; i += 2)
            E[i].f = mid, E[i ^ 1].f = 0;
        int res = Dinic();
        if(res == m)
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
