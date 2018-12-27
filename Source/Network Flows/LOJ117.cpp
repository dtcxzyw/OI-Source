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
int minv(int a, int b) {
    return a < b ? a : b;
}
const int size = 50050, inf = 1 << 30;
struct Edge {
    int to, nxt, f;
} E[size * 7];
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
int q[size], d[size], gap[size], S, T, siz;
void BFS() {
    memset(d + 1, 0, sizeof(int) * siz);
    memset(gap, 0, sizeof(gap));
    q[0] = T, d[T] = 1, ++gap[1];
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(!d[v]) {
                d[v] = d[u] + 1;
                ++gap[d[v]];
                q[e++] = v;
            }
        }
    }
}
int now[size];
int aug(int u, int mf) {
    if(u == T || mf == 0)
        return mf;
    int res = 0, k;
    for(int& i = now[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[u] == d[v] + 1 &&
           (k = aug(v, minv(E[i].f, mf)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, mf -= k;
            if(mf == 0)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = siz + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int ISAP() {
    memcpy(now + 1, last + 1, sizeof(int) * siz);
    BFS();
    int res = 0;
    while(d[S] <= siz)
        res += aug(S, inf);
    return res;
}
int f[size];
int main() {
    int n = read();
    int m = read();
    int s = read();
    int t = read();
    siz = n + 2;
    while(m--) {
        int u = read();
        int v = read();
        int a = read();
        int b = read();
        addEdge(u, v, b - a);
        f[u] -= a, f[v] += a;
    }
    S = n + 1, T = n + 2;
    int sum = 0;
    for(int i = 1; i <= n; ++i)
        if(f[i] > 0) {
            addEdge(S, i, f[i]);
            sum += f[i];
        } else if(f[i] < 0)
            addEdge(i, T, -f[i]);
    addEdge(t, s, inf);
    if(ISAP() == sum) {
        S = t, T = s;
        int af = ISAP();
        int res = E[cnt].f - af;
        printf("%d\n", res > 0 ? res : 0);
    } else
        puts("please go home to sleep");
    return 0;
}
