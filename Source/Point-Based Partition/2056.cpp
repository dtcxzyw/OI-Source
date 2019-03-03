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
int getOp() {
    int c;
    do
        c = getchar();
    while(c != 'C' && c != 'G');
    return c;
}
const int size = 100005, ERR = -(1 << 30);
struct RemovableHeap {
    std::priority_queue<int> A, B;
    void push(int x) {
        if(x != ERR)
            A.push(x);
    }
    void pop(int x) {
        if(x != ERR)
            B.push(x);
    }
    void update() {
        while(A.size() && B.size() &&
              A.top() == B.top())
            A.pop(), B.pop();
    }
    int first() {
        update();
        return A.size() ? A.top() : ERR;
    }
    int mix() {
        update();
        if(A.empty())
            return ERR;
        int fir = A.top();
        pop(fir);
        update();
        int sec = A.size() ? A.top() : ERR;
        push(fir);
        return sec == ERR ? ERR : fir + sec;
    }
    bool replace(int x, int y) {
        if(x != y) {
            pop(x);
            push(y);
            return true;
        }
        return false;
    }
};
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int crt, tsiz, msiz, siz[size];
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
std::vector<std::pair<int, int> > G[size];
int src;
RemovableHeap Glo, Loc[size], Son[size];
void DFS(int u, int p, int len) {
    if(G[u].size())
        Son[src].push(G[u].back().second);
    G[u].push_back(std::make_pair(src, len));
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            DFS(v, u, len + 1);
    }
}
void solve(int u) {
    int fu = 0;
    if(G[u].size())
        fu = G[u].back().first;
    src = u;
    DFS(u, 0, 0);
    Loc[u].push(0);
    Loc[u].push(0);
    if(fu)
        Loc[fu].push(Son[u].first());
}
void divide(int u) {
    vis[u] = true;
    solve(u);
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
    for(int i = 1; i <= n; ++i) {
        int val = Loc[i].mix();
        Glo.push(val);
    }
    int q = read();
    for(int i = 1; i <= q; ++i) {
        if(getOp() == 'G') {
            int val = Glo.first();
            if(val != ERR)
                printf("%d\n", val);
            else
                puts("-1");
        } else {
            int u = read();
            col[u] ^= 1;
            if(col[u]) {
                {
                    int old = Loc[u].mix();
                    Loc[u].pop(0);
                    Loc[u].pop(0);
                    int cur = Loc[u].mix();
                    Glo.replace(old, cur);
                }
                for(int i = 1; i < G[u].size(); ++i) {
                    int p = G[u][i].first;
                    int pp = G[u][i - 1].first;
                    int d = G[u][i - 1].second;
                    int old = Son[p].first();
                    Son[p].pop(d);
                    int cur = Son[p].first();
                    int omix = Loc[pp].mix();
                    if(Loc[pp].replace(old, cur)) {
                        int cmix = Loc[pp].mix();
                        Glo.replace(omix, cmix);
                    }
                }
            } else {
                {
                    int old = Loc[u].mix();
                    Loc[u].push(0);
                    Loc[u].push(0);
                    int cur = Loc[u].mix();
                    Glo.replace(old, cur);
                }
                for(int i = 1; i < G[u].size(); ++i) {
                    int p = G[u][i].first;
                    int pp = G[u][i - 1].first;
                    int d = G[u][i - 1].second;
                    int old = Son[p].first();
                    Son[p].push(d);
                    int cur = Son[p].first();
                    int omix = Loc[pp].mix();
                    if(Loc[pp].replace(old, cur)) {
                        int cmix = Loc[pp].mix();
                        Glo.replace(omix, cmix);
                    }
                }
            }
        }
    }
    return 0;
}
