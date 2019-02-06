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
const int size = 100005;
struct Edge {
    int to, nxt, w;
} E[2000005];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
struct Node {
    int u, d1, d2;
    Node(int u, int d1, int d2)
        : u(u), d1(d1), d2(d2) {}
    bool operator<(const Node& rhs) const {
        return d2 == rhs.d2 ? d1 > rhs.d1 :
                              d2 > rhs.d2;
    }
};
int d1[size], d2[size];
bool flag[size];
int main() {
    int n = read();
    int m = read();
    int k = read();
    for(int i = 0; i < m; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    memset(d1, 0x3f, sizeof(int) * n);
    memset(d2, 0x3f, sizeof(int) * n);
    std::priority_queue<Node> heap;
    for(int i = 0; i < k; ++i) {
        int u = read();
        d1[u] = d2[u] = 0;
        heap.push(Node(u, 0, 0));
    }
    while(heap.size()) {
        Node node = heap.top();
        heap.pop();
        if(flag[node.u])
            continue;
        flag[node.u] = true;
        for(int i = last[node.u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(node.d2 + E[i].w < d2[v]) {
                if(node.d2 + E[i].w <= d1[v]) {
                    d2[v] = d1[v];
                    d1[v] = node.d2 + E[i].w;
                } else
                    d2[v] = node.d2 + E[i].w;
                heap.push(Node(v, d1[v], d2[v]));
            }
        }
    }
    printf("%d\n", d2[0]);
    return 0;
}
