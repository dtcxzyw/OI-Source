#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
namespace IO {
    char in[1 << 24];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 22], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
typedef long long Int64;
const Int64 inf = 1LL << 62;
Int64 read() {
    Int64 res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
void write(Int64 x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 200005;
struct Edge {
    int to, nxt;
    Int64 w;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v, Int64 w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
Int64 P[size], Q[size], L[size], dis[size], sdis[size];
void DFS(int u) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        dis[v] = dis[u] + E[i].w;
        DFS(v);
    }
}
int siz;
int find(Int64 d) {
    return std::lower_bound(sdis + 1, sdis + siz + 1,
                            d) -
        sdis;
}
struct Info {
    int id, pos, old, olen;
    Info(int id, int pos, int old, int olen)
        : id(id), pos(pos), old(old), olen(olen) {}
};
typedef double FT;
Int64 dp[size];
struct Queue {
    std::vector<int> A;
    int len;
    Info insert(int id, int u) {
        int l = 1, r = len - 1, res = len;
        while(l <= r) {
            int m = (l + r) >> 1, v = A[m],
                w = A[m - 1];
            if(static_cast<FT>(dp[u] - dp[v]) *
                   (dis[v] - dis[w]) <=
               static_cast<FT>(dp[v] - dp[w]) *
                   (dis[u] - dis[v]))
                r = m - 1, res = m;
            else
                l = m + 1;
        }
        if(res == A.size())
            A.push_back(0);
        int old = A[res], olen = len;
        A[res] = u, len = res + 1;
        return Info(id, res, old, olen);
    }
    void cancel(int pos, int old, int olen) {
        len = olen, A[pos] = old;
    }
    Int64 query(Int64 P) const {
        if(len == 0)
            return inf;
        int l = 1, r = len - 1, res = A[0];
        while(l <= r) {
            int m = (l + r) >> 1, u = A[m - 1],
                v = A[m];
            if(dp[u] - dp[v] >= (dis[u] - dis[v]) * P)
                res = v, l = m + 1;
            else
                r = m - 1;
        }
        return dp[res] - dis[res] * P;
    }
} q[size << 2];
int off;
std::vector<Info> bak[size];
void insert(int u) {
    int p = find(dis[u]) + off;
    while(p) {
        bak[u].push_back(q[p].insert(p, u));
        p >>= 1;
    }
}
void erase(int u) {
    for(int i = 0; i < bak[u].size(); ++i) {
        Info bi = bak[u][i];
        q[bi.id].cancel(bi.pos, bi.old, bi.olen);
    }
}
Int64 query(int u) {
    int s = find(dis[u] - L[u]) + off - 1,
        t = find(dis[u]) + off + 1;
    Int64 res = inf, cp = P[u];
    for(; s ^ t ^ 1; s >>= 1, t >>= 1) {
        if(~s & 1)
            res = std::min(res, q[s ^ 1].query(cp));
        if(t & 1)
            res = std::min(res, q[t ^ 1].query(cp));
    }
    return res + dis[u] * P[u] + Q[u];
}
void solve(int u) {
    if(u != 1)
        dp[u] = query(u);
    insert(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        solve(v);
    }
    erase(u);
}
int main() {
    IO::init();
    int n = read();
    read();
    for(int i = 2; i <= n; ++i) {
        int f = read();
        Int64 s = read();
        addEdge(f, i, s);
        P[i] = read();
        Q[i] = read();
        L[i] = read();
    }
    DFS(1);
    memcpy(sdis + 1, dis + 1, sizeof(Int64) * n);
    std::sort(sdis + 1, sdis + n + 1);
    siz = std::unique(sdis + 1, sdis + n + 1) -
        (sdis + 1);
    off = 1;
    while(off < siz + 2)
        off <<= 1;
    solve(1);
    for(int i = 2; i <= n; ++i) {
        write(dp[i]);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
