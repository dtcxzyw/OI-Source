// 4722
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
const int size = 1205;
struct Edge {
    int to, nxt, w;
} E[240005];
int last[size], cnt = 1;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int f[size], gap[size << 1], h[size];
struct Cmp {
    bool operator()(int a, int b) const {
        return h[a] < h[b];
    }
};
int push(int u, int v, int id, int fu) {
    int w = std::min(fu, E[id].w);
    f[u] -= w, f[v] += w, E[id].w -= w,
        E[id ^ 1].w += w;
    printf("push %d %d %d\n", u, v, w);
    return w;
}
int q[size];
bool flag[size];
void pre(int n, int t) {
    memset(h, 0x3f, sizeof(h));
    h[t] = 0, flag[t] = true, q[0] = t;
    int b = 0, e = 1;
    while(b != e) {
        int u = q[b++];
        if(b == size)
            b = 0;
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i ^ 1].w && h[v] > h[u] + 1) {
                h[v] = h[u] + 1;
                q[e++] = v;
                if(e == size)
                    e = 0;
            }
        }
    }
}
const int inf = 2147483647;
int solve(int n, int s, int t) {
    std::priority_queue<int, std::vector<int>, Cmp>
        heap;
    pre(n, t);
    if(h[s] == 0x3f3f3f3f)
        return 0;
    h[s] = n;
    for(int i = 1; i <= n; ++i)
        if(h[i] != 0x3f3f3f3f)
            ++gap[h[i]];
    flag[s] = flag[t] = true;
    for(int i = last[s]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(push(s, v, i, inf) && !flag[v])
            heap.push(v), flag[v] = true;
    }
    while(heap.size()) {
        int u = heap.top();
        int hu = h[u];
        heap.pop();
        flag[u] = false;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(hu == h[v] + 1 && push(u, v, i, f[u]) &&
               !flag[v]) {
                heap.push(v), flag[v] = true;
                if(!f[u])
                    break;
            }
        }
        if(f[u]) {
            if(--gap[hu] == 0) {
                for(int i = 1; i <= n; ++i)
                    if(i != s && i != t && hu < h[i] &&
                       h[i] <= n)
                        h[i] = n + 1;
            }
            h[u] = inf;
            for(int i = last[u]; i; i = E[i].nxt)
                if(E[i].w)
                    h[u] =
                        std::min(h[u], h[E[i].to] + 1);
            ++gap[h[u]];
            heap.push(u);
            flag[u] = true;
        }
    }
    return f[t];
}
int main() {
    int n = read();
    int m = read();
    int s = read();
    int t = read();
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, 0);
    }
    printf("%d\n", solve(n, s, t));
    return 0;
}
