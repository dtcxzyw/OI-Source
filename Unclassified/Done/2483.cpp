#include <algorithm>
#include <cstdio>
const int size = 5005;
struct Edge {
    int to, next;
    double w;
} E[2][size * 40];
int last[2][size] = {}, cnt[2] = {};
void addEdge(int u, int v, double w, int i) {
    ++cnt[i];
    Edge& r = E[i][cnt[i]];
    r.to = v, r.next = last[i][u], r.w = w;
    last[i][u] = cnt[i];
}
double dis[size];
bool flag[size] = {};
int q[size];
void SPFA(int n) {
    for(int i = 1; i < n; ++i)
        dis[i] = 1e20;
    dis[n] = 0.0, flag[n] = true, q[0] = n;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        flag[u] = false;
        if(b == size)
            b = 0;
        for(int i = last[1][u]; i; i = E[1][i].next) {
            int v = E[1][i].to;
            if(dis[v] > dis[u] + E[1][i].w) {
                dis[v] = dis[u] + E[1][i].w;
                if(!flag[v]) {
                    flag[v] = true;
                    q[e++] = v;
                    if(e == size)
                        e = 0;
                }
            }
        }
    }
}
struct Node {
    double g;
    int p;
    double f() const {
        return g + dis[p];
    }
    bool operator<(const Node& rhs) const {
        return f() == rhs.f() ? g > rhs.g : f() > rhs.f();
    }
};
struct Heap {
private:
    Node A[size * 2000];
    int siz;

public:
    Heap() : siz(0) {}
    void push(const Node& node) {
        A[siz++] = node;
        std::push_heap(A, A + siz);
    }
    Node pop() {
        Node res = A[0];
        std::pop_heap(A, A + siz);
        --siz;
        return res;
    }
    bool nonEmpty() const {
        return siz;
    }

} heap;
int main() {
    int n, m;
    double e;
    scanf("%d%d%lf", &n, &m, &e);
    e += 1e-6;
    int u, v;
    double w;
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%lf", &u, &v, &w);
        addEdge(u, v, w, 0);
        addEdge(v, u, w, 1);
    }
    SPFA(n);
    int ans = 0;
    Node s;
    s.g = 0.0;
    s.p = 1;
    heap.push(s);
    while(heap.nonEmpty()) {
        Node u = heap.pop();
        if(u.p == n) {
            if(e >= u.g)
                e -= u.g, ++ans;
            else
                break;
        }
        for(int i = last[0][u.p]; i; i = E[0][i].next) {
            Node node;
            node.p = E[0][i].to;
            node.g = u.g + E[0][i].w;
            heap.push(node);
        }
    }
    printf("%d\n", ans);
    return 0;
}
