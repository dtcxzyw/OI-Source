//4722
#include <climits>
#include <cstdio>
#include <queue>
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
const int size = 1205;
struct Edge {
    int to, nxt;
    unsigned int w;
} E[240005];
int last[size] = {}, cnt = 1;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
unsigned int f[size] = {};
int gap[size] = {}, h[size] = {};
struct Node {
    int u, uh;
    Node(int u) : u(u), uh(h[u]) {}
    bool operator<(const Node &rhs) const {
        return uh < rhs.uh;
    }
};
unsigned int push(int u, int v, int id) {
    unsigned int w = std::min(f[u], E[id].w);
    f[u] -= w, f[v] += w, E[id].w -= w, E[id ^ 1].w += w;
    return w;
}
int solve(int n, int s, int t) {
    std::priority_queue<Node> heap;
    f[s] = UINT_MAX;
    h[s] = n;
    heap.push(s);
    while (heap.size()) {
        int u = heap.top().u;
        heap.pop();
        for (int i = last[u]; i && f[u]; i = E[i].nxt) {
            int v = E[i].to;
            if ((u == s || h[u] == h[v] + 1) && push(u, v, i) && v != s && v != t)
                heap.push(v);
        }
        if (u != s && u != t && f[u]) {
            if (--gap[h[u]] == 0) {
                int hl = h[u];
                for (int i = 1; i <= n; ++i)
                    if (i != s && i != t && hl < h[i])
                        h[i] = n + 1;
            }
            ++gap[++h[u]];
            heap.push(u);
        }
    }
    return f[t];
}
int main() {
    int n = read();
    int m = read();
    int s = read();
    int t = read();
    while (m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, 0);
    }
    printf("%d\n", solve(n, s, t));
    return 0;
}
