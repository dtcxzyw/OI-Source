#include <algorithm>
#include <cstdio>
#include <cstring>
namespace IO {
    char in[1 << 23];
    char getc() {
        static char *S = in, *T = in;
        if(S == T) {
            S = in,
            T = in + fread(in, 1, sizeof(in), stdin);
        }
        return S == T ? EOF : *S++;
    }
    char out[1 << 23], *S = out;
    void putc(char ch) {
        *S++ = ch;
        if(S == out + sizeof(out)) {
            S = out;
            fwrite(out, sizeof(out), 1, stdout);
        }
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
typedef long long Int64;
void write(Int64 x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 1000005;
struct Edge {
    int to, nxt, w;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
int P[size], Q[size];
Int64 L[size], dp[size], maxt, A[size], B[size],
    top = 0;
void solve(int u) {
    Int64 fac = P[u];
    int l = 1, r = top, trans = 1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(m == 1 ||
           fac * (A[m - 1] - A[m]) < B[m - 1] - B[m])
            trans = m, l = m + 1;
        else
            r = m - 1;
    }
    dp[u] =
        P[u] * L[u] + Q[u] - fac * A[trans] + B[trans];
    maxt = std::max(maxt, dp[u]);
}
#define asFT static_cast<double>
struct Backup {
    Int64 olda, oldb;
    int pos, osiz;
    void insert(Int64 na, Int64 nb) {
        int l = 1, r = top;
        pos = top + 1;
        while(l <= r) {
            int m = (l + r) >> 1;
            if(m == 1 ||
               asFT(B[m - 1] - B[m]) * (A[m] - na) <
                   asFT(B[m] - nb) * (A[m - 1] - A[m]))
                l = m + 1;
            else
                pos = m, r = m - 1;
        }
        osiz = top;
        top = pos;
        olda = A[pos], oldb = B[pos];
        A[pos] = na, B[pos] = nb;
    }
    void recover() {
        A[pos] = olda;
        B[pos] = oldb;
        top = osiz;
    }
};
void DFS(int u, int p) {
    if(u != 1)
        solve(u);
    Backup bak;
    bak.insert(L[u], dp[u]);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p)
            continue;
        L[v] = L[u] + E[i].w;
        DFS(v, u);
    }
    bak.recover();
}
int main() {
    int n = read();
    for(int i = 2; i <= n; ++i) {
        int f = read();
        int s = read();
        P[i] = read();
        Q[i] = read();
        addEdge(f, i, s);
    }
    DFS(1, 0);
    for(int i = 2; i <= n; ++i) {
        write(dp[i]);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
