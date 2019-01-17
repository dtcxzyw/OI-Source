#include <algorithm>
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
const int size = 30005, inf = 1 << 29;
struct Edge {
    int to, nxt, w;
} E[size * 4];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
struct Info {
    int u, d;
    Info(int u, int d) : u(u), d(d) {}
    bool operator<(const Info& rhs) const {
        return d > rhs.d;
    }
};
std::pair<int, int> dis[size];
std::priority_queue<Info> heap;
void SSSP(int n) {
    memset(dis + 1, 0x3f, sizeof(dis[0]) * n);
    heap.push(Info(1, 0));
    dis[1].first = 0;
    while(heap.size()) {
        int u = heap.top().u;
        int d = heap.top().d;
        heap.pop();
        if(dis[u].first < d)
            continue;
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            int dv = d + E[i].w;
            if(dv < dis[v].first) {
                dis[v].first = dv, dis[v].second = u;
                heap.push(Info(v, dv));
            } else if(dv == dis[v].first &&
                      u < dis[v].second)
                dis[v].second = u;
        }
    }
    cnt = 0;
    memset(last + 1, 0, sizeof(int) * n);
    for(int i = 2; i <= n; ++i) {
        int p = dis[i].second;
        int d = dis[i].first - dis[p].first;
        addEdge(i, p, d);
        addEdge(p, i, d);
    }
}
int mtsiz, tsiz, nrt, siz[size];
bool flag[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !flag[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            msiz = std::max(msiz, siz[v]);
        }
    }
    msiz = std::max(msiz, tsiz - siz[u]);
    if(msiz < mtsiz)
        mtsiz = msiz, nrt = u;
}
int getRoot(int u, int csiz) {
    tsiz = csiz, mtsiz = inf;
    getRootImpl(u, 0);
    return nrt;
}
struct Maxv {
    int maxl, cnt, ts;
} A[size];
int k, cts = 0, ans = 0;
long long acc = 0;
void updateAns(int len, int val) {
    if(len > ans)
        ans = len, acc = 0;
    if(len == ans)
        acc += val;
}
void loadMax(int ecnt) {
    if(A[ecnt].ts != cts)
        A[ecnt].maxl = -inf, A[ecnt].ts = cts;
}
void updateMax(int ecnt, int len) {
    loadMax(ecnt);
    if(A[ecnt].maxl < len)
        A[ecnt].maxl = len, A[ecnt].cnt = 0;
    A[ecnt].cnt += (len == A[ecnt].maxl);
}
bool op;
void DFS(int u, int p, int ecnt, int len) {
    if(op)
        updateMax(ecnt, len);
    else {
        int opec = k - ecnt;
        loadMax(opec);
        updateAns(A[opec].maxl + len, A[opec].cnt);
    }
    if(++ecnt <= k)
        for(int i = last[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(v != p && !flag[v])
                DFS(v, u, ecnt, len + E[i].w);
        }
}
void solve(int u) {
    ++cts;
    updateMax(0, 0);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!flag[v]) {
            op = false;
            DFS(v, u, 1, E[i].w);
            op = true;
            DFS(v, u, 1, E[i].w);
        }
    }
}
void divide(int u) {
    flag[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!flag[v])
            divide(getRoot(v, siz[v]));
    }
}
int main() {
    int n = read();
    int m = read();
    k = read() - 1;
    while(m--) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    SSSP(n);
    divide(getRoot(1, n));
    printf("%d %lld\n", ans, acc);
    return 0;
}
