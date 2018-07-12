#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
int getOp() {
    int c;
    do
        c = getchar();
    while (c != 'C' && c != 'A');
    return c;
}
const int size = 100005, inf = 1 << 28;
struct Edge {
    int to, next, w;
} E[size * 2];
int last[size] = {}, cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].next = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int tot, csiz, crt, siz[size];
bool vis[size] = {};
int getRoot(int u, int p) {
    int maxs = 0;
    siz[u] = 1;
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v] && v != p) {
            getRoot(v, u);
            siz[u] += siz[v];
            maxs = std::max(maxs, siz[v]);
        }
    }
    maxs = std::max(maxs, tot - siz[u]);
    if (csiz > maxs) {
        csiz = maxs;
        crt = u;
    }
}
typedef std::multiset<int> Heap;
Heap heaps[size];
int hcnt = 0;
std::vector<std::pair<int, int> > rts[size];
void DFS(int heap, int u, int p, int base) {
    heaps[heap].insert(base);
    rts[u].push_back(std::make_pair(base, heap));
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v] && v != p)
            DFS(heap, v, u, base + E[i].w);
    }
}
void insert(int u) {
    for (int i = 0; i < rts[u].size(); ++i) {
        Heap &heap = heaps[rts[u][i].second];
        heap.insert(rts[u][i].first);
    }
}
void erase(int u) {
    for (int i = 0; i < rts[u].size(); ++i) {
        Heap &heap = heaps[rts[u][i].second];
        heap.erase(heap.find(rts[u][i].first));
    }
}
std::pair<int, std::vector<int> > src[size];
int scnt = 0;
void divide(int u) {
    vis[u] = true;
    ++scnt;
    src[scnt].first = u;
    std::vector<int> &s = src[scnt].second;
    for (int i = last[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (!vis[v]) {
            s.push_back(++hcnt);
            DFS(s.back(), v, u, E[i].w);

            tot = siz[v], csiz = inf;
            getRoot(v, 0);
            divide(crt);
        }
    }
}
bool flag[size] = {};
int main() {
    int n = read();
    for (int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    tot = n, csiz = inf;
    getRoot(1, 0);
    divide(crt);
    int q = read(), wcnt = n;
    for (int i = 0; i < q; ++i) {
        if (getOp() == 'C') {
            int u = read();
            flag[u] ^= 1;
            if (flag[u])
                erase(u), --wcnt;
            else
                insert(u), ++wcnt;
        } else if (wcnt) {
            int res = -inf;
            for (int j = 0; j < scnt; ++j) {
                int first = -inf, second = -inf;
                int u = src[j].first;
                std::vector<int> &s = src[j].second;
                for (int k = 0; k < s.size(); ++k) {
                    Heap &heap = heaps[s[k]];
                    if (heap.size()) {
                        int val = *heap.rbegin();
                        if (val > second) {
                            second = val;
                            if (second > first) std::swap(first, second);
                        }
                    }
                }
                if (flag[u])
                    res = std::max(res, first + second);
                else
                    res = std::max(res, std::max(first, 0) + std::max(second, 0));
            }
            printf("%d\n", res);
        } else
            puts("They have disappeared.");
    }
    return 0;
}
