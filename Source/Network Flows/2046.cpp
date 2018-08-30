#include <cstdio>
#include <cstring>
#include <queue>
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
const int size = 515, maxv = size * size, S = 1, T = 2;
struct Edge {
    int to, nxt, w;
} E[4 * maxv];
int last[maxv], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u],
    E[cnt].w = read();
    last[u] = cnt;
}
struct Node {
    int u, dis;
    Node(int u, int dis) : u(u), dis(dis) {}
    bool operator<(const Node& rhs) const {
        return dis > rhs.dis;
    }
};
int dis[maxv];
int SSSP() {
    memset(dis, 0x3f, sizeof(dis));
    dis[S] = 0;
    std::priority_queue<Node> heap;
    heap.push(Node(S, 0));
    while(heap.size()) {
        int u = heap.top().u;
        int cd = heap.top().dis;
        heap.pop();
        if(cd > dis[u])
            continue;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            int dv = cd + E[i].w;
            if(dv < dis[v]) {
                dis[v] = dv;
                heap.push(Node(v, dv));
            }
        }
    }
    return dis[T];
}
int n;
int getId(int x, int y) {
    if(1 <= x && x <= n && 1 <= y && y <= n)
        return n * x + y + 2;
    return (x == 0 || y == n + 1) ? S : T;
}
void readNS(int i, int j) {
    addEdge(getId(i, j), getId(i + 1, j));
}
void readSN(int i, int j) {
    addEdge(getId(i + 1, j), getId(i, j));
}
int main() {
    n = read();
    for(int i = 0; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            addEdge(getId(j, i + 1), getId(j, i));
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j <= n; ++j)
            addEdge(getId(j, i), getId(j + 1, i));
    for(int i = 0; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            addEdge(getId(j, i), getId(j, i + 1));
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j <= n; ++j)
            addEdge(getId(j + 1, i), getId(j, i));
    printf("%d\n", SSSP());
    return 0;
}
