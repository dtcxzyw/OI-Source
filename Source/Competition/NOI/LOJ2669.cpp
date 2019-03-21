// FIXME
#include <algorithm>
#include <cstdio>
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
typedef long long Int64;
const int size = 200005;
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 1;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
bool ring[size], vis[size];
int st[size], top = 0, rv[size], rd[size], rsiz = 0;
Int64 rsum = 0;
bool findRing(int u, int p) {
    if(vis[u]) {
        int v;
        do {
            int eid = st[top--];
            v = E[eid].to;
            ++rsiz;
            rd[rsiz] = E[eid].w;
            rsum += E[eid].w;
            rv[rsiz] = v;
            ring[v] = true;
        } while(v != u);
        return true;
    }
    vis[u] = true;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            st[++top] = i ^ 1;
            if(findRing(v, u))
                return true;
            --top;
        }
    }
    return false;
}
Int64 clen[size];
void DFS(int u, int p) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !ring[v]) {
            DFS(v, u);
            clen[u] =
                std::max(clen[u], clen[v] + E[i].w);
        }
    }
}
const Int64 inf = 1LL << 62;
struct RemovableHeap {
    std::priority_queue<Int64> A, B;
    void push(Int64 x) {
        A.push(x);
    }
    void pop(Int64 x) {
        B.push(x);
    }
    Int64 top() {
        while(A.size() && B.size() &&
              A.top() == B.top())
            A.pop(), B.pop();
        return A.size() ? A.top() : -inf;
    }
};
Int64 ans = inf;
void solve(int u, int p, Int64 d) {
    if(d >= ans)
        return;
    ans = std::min(ans, std::max(d, clen[u]));
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !ring[v])
            solve(v, u, d + E[i].w);
    }
}
int nxt(int x, int siz) {
    if(++x > siz)
        return 1;
    return x;
}
Int64 lenA[size], lenB[size];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        int id = n + i;
        addEdge(u, id, w);
        addEdge(id, u, w);
        addEdge(v, id, w);
        addEdge(id, v, w);
    }
    findRing(1, 0);
    for(int i = 1; i <= rsiz; ++i)
        DFS(rv[i], 0);
    RemovableHeap A, B;
    int end = 1;
    Int64 csum = 0;
    lenA[1] = lenB[1] = clen[rv[1]];
    lenB[1] += rsum;
    for(int i = 2; i <= rsiz; ++i) {
        csum += rd[i];
        lenA[i] = csum + clen[rv[i]],
        lenB[i] = rsum - csum + clen[rv[i]];
        if(lenA[i] < lenB[i]) {
            end = i;
            if(rv[i] <= n)
                A.push(lenA[i]);
        } else if(rv[i] <= n)
            B.push(lenB[i]);
    }
    Int64 deltaA = 0, deltaB = 0;
    for(int i = 1; i <= rsiz; ++i) {
        if(i != 1) {
            if(rv[i] <= n) {
                if(lenA[i] + deltaA < lenB[i] + deltaB)
                    A.pop(lenA[i]);
                else
                    B.pop(lenB[i]);
            }
            if(rv[i - 1] <= n) {
                if(lenA[i - 1] + deltaA + rsum <
                   lenB[i - 1] + deltaB - rsum)
                    A.push(lenA[i - 1] + rsum);
                else
                    B.push(lenB[i - 1] - rsum);
            }
            deltaA -= rd[i];
            deltaB += rd[i];
            while(nxt(end, rsiz) != i) {
                int np = nxt(end, rsiz);
                if(lenA[np] + deltaA +
                       (np < i ? rsum : 0) <
                   lenB[np] + deltaB -
                       (np < i ? rsum : 0)) {
                    if(rv[np] <= n) {
                        A.push(lenA[np] +
                               (np < i ? rsum : 0));
                        B.pop(lenB[np] -
                              (np < i ? rsum : 0));
                    }
                    end = np;
                } else
                    break;
            }
        }
        int u = rv[i];
        solve(u, 0, std::max(A.top() + deltaA,
                             B.top() + deltaB));
    }
    printf("%lld.%d", ans >> 1, ans & 1 ? 5 : 0);
    return 0;
}
