#include <algorithm>
#include <cstdio>
#include <cstring>
namespace IO {
    const int size = 1 << 23;
    char in[size], *S = in;
    void init() {
        setvbuf(stdin, 0, _IONBF, 0);
        setvbuf(stdout, 0, _IONBF, 0);
        fread(in, 1, size, stdin);
    }
    char getc() {
        return *S++;
    }
}
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
int iabs(int x) {
    return x < 0 ? -x : x;
}
const int size = 300005;
struct Edge {
    int to, nxt, w;
} E[2 * size];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 C;
struct Chain {
    Int64 sum;
    int cnt;
    Chain() : sum(0), cnt(0) {}
    Chain(Int64 sum, int cnt) : sum(sum), cnt(cnt) {}
    bool operator<(const Chain& rhs) const {
        return sum == rhs.sum ? cnt > rhs.cnt :
                                sum < rhs.sum;
    }
    Chain operator+(const Chain& rhs) const {
        return Chain(sum + rhs.sum, cnt + rhs.cnt);
    }
    Chain operator+(int len) const {
        return Chain(sum + len, cnt);
    }
};
Chain makeChain(const Chain& c) {
    return Chain(c.sum + C, c.cnt + 1);
}
struct Info {
    Chain L0, L1;
    Info(const Chain& L0, const Chain& L1)
        : L0(L0), L1(L1) {}
};
Info DFS(int u, int p) {
    Chain L0, L1, L2;
    if(C > 0)
        L2.sum = C, L2.cnt = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == p)
            continue;
        Info vres = DFS(v, u);
        L2 =
            std::max(L2 + vres.L0,
                     makeChain(L1 + vres.L1 + E[i].w));
        L1 = std::max(L1 + vres.L0,
                      L0 + vres.L1 + E[i].w);
        L0 = L0 + vres.L0;
    }
    return Info(
        std::max(makeChain(L1), std::max(L0, L2)), L1);
}
int main() {
    IO::init();
    int n = read();
    int k = read() + 1;
    Int64 sum = 0;
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
        sum += iabs(w);
    }
    if(k > 1)
        sum = sum / (k - 1) + 1;
    Int64 l = -sum, r = sum, ans = 0;
    while(l <= r) {
        Int64 m = (l + r) >> 1;
        C = m;
        Chain res = DFS(1, 0).L0;
        if(res.cnt <= k)
            l = m + 1, ans = res.sum - asInt64(m) * k;
        else
            r = m - 1;
        if(res.cnt == k)
            break;
    }
    printf("%lld\n", ans);
    return 0;
}
