#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 30005, maxV = size * 180;
struct Edge {
    int to, next, w;
} E[maxV * 4];
int last[maxV], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int q[maxV], dis[maxV];
bool flag[maxV] = {};
int SPFA(int S, int T) {
    memset(dis, 0x3f, sizeof(dis));
    dis[S] = 0, q[0] = S, flag[S] = true;
    int b = 0, e = 1;
    while (b != e) {
        int u = q[b++];
        if (b == maxV) b = 0;
        flag[u] = false;
        for (int i = last[u]; i; i = E[i].next) {
            int v = E[i].to;
            int cd = dis[u] + E[i].w;
            if (cd < dis[v]) {
                dis[v] = cd;
                if (!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if (e == maxV) e = 0;
                }
            }
        }
    }
    return dis[T] != 0x3f3f3f3f ? dis[T] : -1;
}
int main() {
    int n = read();
    int m = read();
    int bsiz = sqrt(n);
    for (int i = 1; i <= bsiz; ++i) {
        int base = i * n;
        for (int j = 1; j <= n; ++j)
            addEdge(base + j, j, 0);
    }
    for (int i = 1; i <= bsiz; ++i) {
        int b1 = i * n, b2 = b1 + i, end = n - i;
        for (int j = 1; j <= end; ++j) {
            int u = b1 + j, v = b2 + j;
            addEdge(u, v, 1);
            addEdge(v, u, 1);
        }
    }
    int s, t;
    for (int i = 1; i <= m; ++i) {
        int pos = read() + 1;
        if (i == 1) s = pos;
        if (i == 2) t = pos;
        int off = read();
        if (off <= bsiz)
            addEdge(pos, off * n + pos, 0);
        else {
            int cp = pos - off, cnt = 1;
            while (cp >= 1) {
                addEdge(pos, cp, cnt);
                ++cnt;
                cp -= off;
            }
            cp = pos + off, cnt = 1;
            while (cp <= n) {
                addEdge(pos, cp, cnt);
                ++cnt;
                cp += off;
            }
        }
    }
    printf("%d\n", SPFA(s, t));
    return 0;
}
