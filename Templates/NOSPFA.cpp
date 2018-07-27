//4779
#include <cstdio>
#include <cstring>
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
const int size = 100005;
struct Edge {
    int to, next, w;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int dis[size];
struct Node {
    int u, d;
    Node(int u) : u(u), d(dis[u]) {}
    bool operator<(const Node &rhs) const {
        return d > rhs.d;
    }
};
void SSSP(int s) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    std::priority_queue<Node> heap;
    heap.push(s);
    while (heap.size()) {
        int u = heap.top().u;
        int d = heap.top().d;
        heap.pop();
        if (dis[u] != d) continue;
        for (int i = last[u]; i; i = E[i].next) {
            int v = E[i].to;
            int cd = d + E[i].w;
            if (cd < dis[v]) {
                dis[v] = cd;
                heap.push(v);
            }
        }
    }
}
int main() {
    int n = read();
    int m = read();
    int s = read();
    while (m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
    }
    SSSP(s);
    for (int i = 1; i <= n; ++i)
        printf("%d ", dis[i]);
    return 0;
}
