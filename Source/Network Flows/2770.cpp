#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
std::string read() {
    std::string res;
    int c;
    do
        c = getchar();
    while (!isalnum(c));
    while (isalnum(c)) {
        res += c;
        c = getchar();
    }
    return res;
}
const int maxn = 105, size = 2 * maxn, inf = 0x3f3f3f3f;
int S, T;
struct Edge {
    int to, nxt, f, w;
} E[2 * maxn * maxn];
int last[size] = {}, cnt = 1;
void addEdgeImpl(int u, int v, int f, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].f = f, E[cnt].w = w;
    last[u] = cnt;
}
void addEdge(int u, int v, int f, int w) {
    addEdgeImpl(u, v, f, w);
    addEdgeImpl(v, u, 0, -w);
}
int dis[size], eid[size], q[size];
bool flag[size] = {};
bool SPFA(int siz) {
    memset(dis, 0xc0, sizeof(int) * siz);
    q[0] = S, dis[S] = 0, flag[S] = true;
    int b = 0, e = 1;
    while (b != e) {
        int u = q[b++];
        flag[u] = false;
        if (b == size) b = 0;
        for (int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            int cd = dis[u] + E[i].w;
            if (E[i].f && dis[v] < cd) {
                dis[v] = cd;
                eid[v] = i;
                if (!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if (e == size) e = 0;
                }
            }
        }
    }
    return dis[T] != 0xc0c0c0c0;
}
std::pair<int, int> MCMF(int siz) {
    int resA = 0, resB = 0;
    while (SPFA(siz)) {
        int p = T, mf = inf;
        while (p != S) {
            int e = eid[p];
            mf = std::min(mf, E[e].f);
            p = E[e ^ 1].to;
        }
        p = T;
        while (p != S) {
            int e = eid[p];
            E[e].f -= mf, E[e ^ 1].f += mf;
            p = E[e ^ 1].to;
        }
        resA += mf;
        resB += mf * dis[T];
    }
    return std::make_pair(resA, resB);
}
std::string A[size];
int find(const std::string &name, int n) {
    return std::find(A + 1, A + n + 1, name) - A;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    S = 1, T = n + n;
    for (int i = 1; i <= n; ++i) A[i] = read();
    addEdge(1, 1 + n, 2, 0);
    for (int i = 2; i < n; ++i) addEdge(i, i + n, 1, 0);
    addEdge(n, n + n, 2, 0);
    while (m--) {
        int u = find(read(), n);
        int v = find(read(), n);
        if (u > v) std::swap(u, v);
        addEdge(u + n, v, inf, 1);
    }
    std::pair<int, int> res = MCMF(T + 1);
    if (res.first == 2) {
        printf("%d\n", res.second);
        int p = 1;
        while (p != n) {
            puts(A[p].c_str());
            for (int i = last[p + n]; i; i = E[i].nxt)
                if ((i & 1) == 0 && E[i].f != inf) {
                    p = E[i].to;
                    flag[p] = true;
                    break;
                }
        }
        while (p != 1) {
            puts(A[p].c_str());
            for (int i = last[p]; i; i = E[i].nxt)
                if ((i & 1) && E[i].f != 0) {
                    int v = E[i].to - n;
                    if (!flag[v]) {
                        p = v;
                        break;
                    }
                }
        }
        puts(A[1].c_str());
    } else
        puts("No Solution!");
    return 0;
}
