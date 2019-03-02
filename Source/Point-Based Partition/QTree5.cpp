#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
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
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int crt, msiz, tsiz, siz[size];
bool vis[size];
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int csiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            csiz = std::max(csiz, siz[v]);
        }
    }
    csiz = std::max(csiz, tsiz - siz[u]);
    if(csiz < msiz)
        msiz = csiz, crt = u;
}
int getRoot(int u, int usiz) {
    msiz = 1 << 30, tsiz = usiz;
    getRootImpl(u, 0);
    return crt;
}
const int inf = 1 << 30;
struct RemovableHeap {
    std::priority_queue<int, std::vector<int>,
                        std::greater<int> >
        A, B;
    void push(int x) {
        A.push(x);
    }
    void pop(int x) {
        B.push(x);
    }
    int top() {
        while(A.size() && B.size() &&
              A.top() == B.top())
            A.pop(), B.pop();
        return A.size() ? A.top() : inf;
    }
} T[size];
std::vector<std::pair<int, int> > A[size];
void DFS(int u, int p, int d) {
    A[u].push_back(std::make_pair(crt, d));
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            DFS(v, u, d + 1);
    }
}
void divide(int u) {
    vis[u] = true;
    crt = u;
    DFS(u, 0, 0);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            divide(nrt);
        }
    }
}
bool col[size];
int main() {
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    divide(getRoot(1, n));
    int q = read();
    for(int i = 1; i <= q; ++i) {
        int op = read();
        int u = read();
        if(op) {
            int res = inf;
            for(int i = 0; i < A[u].size(); ++i) {
                int p = A[u][i].first;
                int d = A[u][i].second;
                res = std::min(res, T[p].top() + d);
            }
            if(res == inf)
                puts("-1");
            else
                printf("%d\n", res);
        } else {
            col[u] ^= 1;
            if(col[u]) {
                for(int i = 0; i < A[u].size(); ++i) {
                    int p = A[u][i].first;
                    int d = A[u][i].second;
                    T[p].push(d);
                }
            } else {
                for(int i = 0; i < A[u].size(); ++i) {
                    int p = A[u][i].first;
                    int d = A[u][i].second;
                    T[p].pop(d);
                }
            }
        }
    }
    return 0;
}
