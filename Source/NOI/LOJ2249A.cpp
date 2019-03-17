#include <cstdio>
#include <vector>
namespace IO {
    const int size = 1 << 24;
    char in[size];
    void init() {
        fread(in, 1, size, stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[size], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
typedef long long Int64;
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
int son[size], p[size];
Int64 len[size];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        p[v] = u;
        len[v] = len[u] + E[i].w;
        int vsiz = buildTree(v);
        siz += vsiz;
        if(vsiz > msiz)
            msiz = vsiz, son[u] = v;
    }
    return siz;
}
int top[size];
void buildChain(int u) {
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
std::vector<int> Q[size];
Int64 dp[size];
Int64 calc(int u, Int64 k, Int64 b, Int64 lim) {
    Int64 minv = 1LL << 62, base = len[u] - lim,
          offset = len[u] * k + b;
    int src = u;
    while(u) {
        std::vector<int>& cq = Q[top[u]];
        if(len[u] < base)
            break;
        int end = -1;
        {
            int l = 0, r = cq.size() - 1;
            while(l <= r) {
                int m = (l + r) >> 1;
                if(len[cq[m]] <= len[u])
                    l = m + 1, end = m;
                else
                    r = m - 1;
            }
        }
        int beg = cq.size();
        {
            int l = 0, r = end;
            while(l <= r) {
                int m = (l + r) >> 1;
                if(len[cq[m]] >= base)
                    r = m - 1, beg = m;
                else
                    l = m + 1;
            }
        }
        int trans = -1;
        {
            int l = beg, r = end;
            while(l <= r) {
                int m = (l + r) >> 1;
                int v = cq[m],
                    nv = m == end ? 0 : cq[m + 1];
                if((nv == 0 ||
                    (len[nv] - len[v]) * k <
                        dp[nv] - dp[v]))
                    r = m - 1, trans = m;
                else
                    l = m + 1;
            }
        }
        if(trans != -1) {
            int v = cq[trans];
            minv = std::min(minv, dp[v] - len[v] * k);
        }
        if(beg <= end) {
            if(trans == beg && beg != 0) {
                int v = p[cq[beg]];
                while(true) {
                    if(len[v] >= base)
                        minv = std::min(
                            minv, dp[v] - len[v] * k);
                    else
                        break;
                    v = p[v];
                }
            }
            if(!(u == src && u == top[u])) {
                if(u == src)
                    u = p[u];
                while(u != cq[end]) {
                    minv = std::min(minv, dp[u] -
                                        len[u] * k);
                    if(u == top[u])
                        break;
                    u = p[u];
                }
            }
        } else if(!(u == src && u == top[u])) {
            if(u == src)
                u = p[u];
            while(true) {
                if(len[u] >= base)
                    minv = std::min(minv, dp[u] -
                                        len[u] * k);
                else
                    break;
                if(u == top[u])
                    break;
                u = p[u];
            }
        }
        u = p[top[u]];
    }
    return minv + offset;
}
Int64 k[size], b[size], lim[size];
int fir(const std::vector<int>& A) {
    return A.back();
}
int sec(const std::vector<int>& A) {
    return A[A.size() - 2];
}
void solve(int u) {
    if(u != 1)
        dp[u] = calc(u, k[u], b[u], lim[u]);
    std::vector<int>& cq = Q[top[u]];
    while(cq.size() >= 2 &&
          (dp[sec(cq)] - dp[fir(cq)]) /
                  (len[sec(cq)] - len[fir(cq)]) >=
              (dp[fir(cq)] - dp[u]) /
                  (len[fir(cq)] - len[u]))
        cq.pop_back();
    cq.push_back(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        solve(v);
    }
}
int main() {
    IO::init();
    int n = read();
    int t = read();
    for(int i = 2; i <= n; ++i) {
        int p = read();
        Int64 w = read();
        addEdge(p, i, w);
        k[i] = read();
        b[i] = read();
        lim[i] = read();
    }
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    solve(1);
    for(int i = 2; i <= n; ++i) {
        write(dp[i]);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
