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
const int size = 855;
struct Edge {
    int to, nxt, f;
} E[size * 20];
int last[size], cnt = 1;
void addEdge(int u, int v, int f) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f;
    last[u] = cnt;
}
int S, T, n, gap[size], d[size], q[size];
void BFS() {
    memset(gap, 0, sizeof(int) * (n + 2));
    memset(d + 1, 0, sizeof(int) * n);
    d[T] = 1, q[0] = T, gap[1] = 1;
    int b = 0, e = 1;
    while(b < e) {
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
           (k = aug(v, std::min(mf, E[i].f)))) {
            E[i].f -= k, E[i ^ 1].f += k;
            res += k, mf -= k;
            if(!mf)
                return res;
        }
    }
    if(--gap[d[u]] == 0)
        d[S] = n + 1;
    ++gap[++d[u]], now[u] = last[u];
    return res;
}
int minCut() {
    for(int i = 2; i <= cnt; i += 2) {
        int tot = E[i].f + E[i ^ 1].f;
        E[i].f = E[i ^ 1].f = tot >> 1;
    }
    BFS();
    memcpy(now + 1, last + 1, sizeof(int) * n);
    int res = 0;
    while(d[S] <= n)
        res += aug(S, 1 << 30);
    return res;
}
int A[size];
bool flag[size];
void color(int l, int r) {
    memset(flag + 1, 0, sizeof(bool) * n);
    flag[S] = true, q[0] = S;
    int b = 0, e = 1;
    while(b < e) {
        int u = q[b++];
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].f && !flag[v]) {
                flag[v] = true;
                q[e++] = v;
            }
        }
    }
}
int B[size], ecnt = 0;
void buildGHT(int l, int r) {
    if(l == r)
        return;
    S = A[l], T = A[r];
    B[ecnt++] = minCut();
    color(l, r);
    int wp = l;
    for(int i = l; i <= r; ++i)
        if(flag[A[i]])
            std::swap(A[i], A[wp++]);
    buildGHT(l, wp - 1);
    buildGHT(wp, r);
}
int main() {
    n = read();
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    for(int i = 1; i <= n; ++i)
        A[i] = i;
    buildGHT(1, n);
    std::sort(B, B + ecnt);
    int siz = std::unique(B, B + ecnt) - B;
    printf("%d\n", siz);
    return 0;
}
