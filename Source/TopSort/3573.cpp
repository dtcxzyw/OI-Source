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
int maxv(int a, int b) {
    return a > b ? a : b;
}
const int size = 500005;
int q[size];
struct Graph {
    struct Edge {
        int to, nxt;
    } E[size * 2];
    int last[size], cnt, d[size];
    Graph() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        ++d[v];
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
    int dis[size];
    void SSSP(int n) {
        int qsiz = 0;
        for(int i = 1; i <= n; ++i)
            if(d[i] == 0)
                q[++qsiz] = i;
        for(int i = 1; i <= qsiz; ++i) {
            int u = q[i];
            for(int j = last[u]; j; j = E[j].nxt) {
                int v = E[j].to;
                dis[v] = maxv(dis[v], dis[u] + 1);
                if(--d[v] == 0)
                    q[++qsiz] = v;
            }
        }
    }
} GA, GB;
class Heap {
private:
    std::priority_queue<int> A, B;

public:
    void push(int x) {
        A.push(x);
    }
    void pop(int x) {
        B.push(x);
        while(A.size() && B.size() &&
              A.top() == B.top())
            A.pop(), B.pop();
    }
    int top() {
        return A.top();
    }
};
int w[size * 2], d[size];
int main() {
    int n = read();
    int m = read();
    while(m--) {
        int u = read();
        int v = read();
        GA.addEdge(u, v);
        GB.addEdge(v, u);
    }
    memcpy(d + 1, GA.d + 1, sizeof(int) * n);
    GA.SSSP(n);
    GB.SSSP(n);
    for(int i = 1; i <= n; ++i)
        for(int j = GA.last[i]; j; j = GA.E[j].nxt) {
            int v = GA.E[j].to;
            w[j] = GA.dis[i] + GB.dis[v] + 1;
        }
    Heap heap;
    int res = 1 << 30, pid, qsiz = 0;
    for(int i = 1; i <= n; ++i) {
        heap.push(GB.dis[i]);
        if(d[i] == 0)
            q[++qsiz] = i;
    }
    for(int i = 1; i <= qsiz; ++i) {
        int u = q[i];
        for(int j = GB.last[u]; j; j = GB.E[j].nxt)
            heap.pop(w[j]);
        heap.pop(GB.dis[u]);
        if(heap.top() < res) {
            res = heap.top();
            pid = u;
        }
        for(int j = GA.last[u]; j; j = GA.E[j].nxt) {
            heap.push(w[j]);
            int v = GA.E[j].to;
            if(--d[v] == 0)
                q[++qsiz] = v;
        }
        heap.push(GA.dis[u]);
    }
    printf("%d %d\n", pid, res);
    return 0;
}
