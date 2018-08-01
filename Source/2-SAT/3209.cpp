#include <algorithm>
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
const int maxN = 205, maxM = 3 * maxN, max2M = maxM * 2;
struct Edge {
    int to, next;
} E[max2M];
int last[maxN], cnt;
void clear() {
    memset(last, 0, sizeof(last));
    cnt = 1;
}
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u];
    last[u] = cnt;
}
int vert[maxN], pos[maxN], fa[max2M];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) fa[u] = v;
}
bool foo() {
    cnt = 1;
    memset(last, 0, sizeof(last));
    int n = read();
    int m = read();
    bool res = m <= 3 * n - 6;
    for (int i = 0; i < m; ++i) {
        int u = read();
        int v = read();
        if (res) {
            addEdge(u, v);
            addEdge(v, u);
        }
    }
    for (int i = 0; i < n; ++i) {
        int u = read();
        vert[i] = u;
        pos[u] = i;
    }
    if (!res) return false;
    for (int i = 2; i <= cnt; ++i) fa[i] = i;
    for (int i = 2; i <= cnt; i += 2) {
        int pu = pos[E[i].to], pv = pos[E[i + 1].to];
        if (pu > pv) std::swap(pu, pv);
        for (int j = pu + 1; j < pv; ++j) {
            int w = vert[j];
            for (int e = last[w]; e; e = E[e].next) {
                int to = E[e].to;
                if (pos[to] < pu || pos[to] > pv) {
                    int id = e & ~1;
                    if (find(i) == find(id)) return false;
                    merge(i, id | 1);
                    merge(id, i | 1);
                }
            }
        }
    }
    return true;
}
int main() {
    int t = read();
    while (t--)
        puts(foo() ? "YES" : "NO");
    return 0;
}
