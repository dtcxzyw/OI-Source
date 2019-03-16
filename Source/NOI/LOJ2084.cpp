// FIXME
#include <algorithm>
#include <cstdio>
#include <cstring>
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
typedef long long Int64;
#define asInt64 static_cast<Int64>
namespace HashTable {
    const int modu = 5000011, modv = 4999999;
    std::pair<Int64, int> LUT[modu];
    std::vector<int> clr;
    int crk;
    void clear() {
        for(int i = 0; i < clr.size(); ++i)
            LUT[clr[i]].first = 0;
        clr.clear();
        crk = 0;
    }
    void load(Int64 x, Int64 y) {
        Int64 key = x << 32 | y;
        int hu = key % modu, hv = 1 + key % modv,
            cur = hu;
        while(true) {
            if(LUT[cur].first == 0) {
                LUT[cur].first = key;
                LUT[cur].second = ++crk;
                clr.push_back(cur);
            }
            if(LUT[cur].first == key)
                return;
            cur += hv;
            if(cur >= modu)
                cur -= modu;
        }
    }
    int find(Int64 x, Int64 y) {
        Int64 key = x << 32 | y;
        int hu = key % modu, hv = 1 + key % modv,
            cur = hu;
        while(true) {
            if(LUT[cur].first == 0)
                return -1;
            if(LUT[cur].first == key)
                return LUT[cur].second;
            cur += hv;
            if(cur >= modu)
                cur -= modu;
        }
    }
}
const int size = 100005, maxP = 2500005;
struct Edge {
    int to, nxt;
} E[maxP * 4];
int last[size], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int dfn[maxP], low[maxP], ts = 0, ccnt;
void DFS(int u, int p) {
    dfn[u] = low[u] = ++ts;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p)
            continue;
        if(dfn[v])
            low[u] = std::min(low[u], dfn[v]);
        else {
            DFS(v, u);
            low[u] = std::min(low[u], low[v]);
            if(p && dfn[u] <= low[v])
                ++ccnt;
        }
    }
}
struct Point {
    int x, y;
} P[size];
bool mark[maxP];
int foo() {
    int n = read();
    int m = read();
    int k = read();
    for(int i = 1; i <= k; ++i) {
        P[i].x = read();
        P[i].y = read();
    }
    if(asInt64(n) * m - k <= 1)
        return -1;
    HashTable::clear();
    for(int i = 1; i <= k; ++i) {
        int bx = std::max(1, P[i].x - 2),
            ex = std::min(n, P[i].x + 2);
        int by = std::max(1, P[i].y - 2),
            ey = std::min(m, P[i].y + 2);
        for(int x = bx; x <= ex; ++x)
            for(int y = by; y <= ey; ++y)
                HashTable::load(x, y);
    }
    int siz = HashTable::crk;
    fprintf(stderr, "P %d\n", siz);
    memset(mark + 1, 0, sizeof(bool) * siz);
    for(int i = 1; i <= k; ++i)
        mark[HashTable::find(P[i].x, P[i].y)] = true;
    ++siz;
    memset(last + 1, 0, sizeof(int) * siz);
    cnt = 0;
    for(int i = 0; i < HashTable::clr.size(); ++i) {
        std::pair<Int64, int> info =
            HashTable::LUT[HashTable::clr[i]];
        if(mark[info.second])
            continue;
        int x = info.first >> 32,
            y = info.first & ((1LL << 32) - 1),
            u = info.second;
        if(x < n) {
            int v = HashTable::find(x + 1, y);
            if(v != -1 && !mark[v]) {
                addEdge(u, v);
                addEdge(v, u);
            } else if(v == -1) {
                addEdge(u, siz);
                addEdge(siz, u);
            }
        }
        if(y < m) {
            int v = HashTable::find(x, y + 1);
            if(v != -1 && !mark[v]) {
                addEdge(u, v);
                addEdge(v, u);
            } else if(v == -1) {
                addEdge(u, siz);
                addEdge(siz, u);
            }
        }
    }
    memset(dfn + 1, 0, sizeof(int) * siz);
    ccnt = 0;
    DFS(siz, 0);
    if(ts < siz - k)
        return 0;
    if(asInt64(n) * m - k == 2)
        return -1;
    return ccnt ? 1 : 2;
}
int main() {
    int t = read();
    for(int i = 0; i < t; ++i)
        printf("%d\n", foo());
    return 0;
}
