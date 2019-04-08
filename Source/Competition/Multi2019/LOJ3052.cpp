#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <queue>
namespace IO {
    char buf[1 << 22];
    void init() {
        fread(buf, 1, sizeof(buf), stdin);
    }
    char getc() {
        static char* S = buf;
        return *S++;
    }
}  // namespace IO
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
const int size = 200005;
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
typedef long long Int64;
struct Info {
    std::priority_queue<int> blks;
    Int64 sum;
    void insert(int w) {
        blks.push(w);
        sum += w;
    }
    void swap(Info& rhs) {
        blks.swap(rhs.blks);
        std::swap(sum, rhs.sum);
    }
} A[size];
int buf[size];
void merge(Info& a, Info& b) {
    if(a.blks.size() < b.blks.size())
        std::swap(a, b);
    int bsiz = 0;
    while(b.blks.size()) {
        int u = a.blks.top();
        a.blks.pop();
        int v = b.blks.top();
        b.blks.pop();
        a.sum -= u;
        buf[++bsiz] = std::max(u, v);
    }
    for(int i = 1; i <= bsiz; ++i)
        a.insert(buf[i]);
}
int w[size];
void solve(int u) {
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        solve(v);
        merge(A[u], A[v]);
    }
    A[u].insert(w[u]);
}
int main() {
    IO::init();
    int n = read();
    for(int i = 1; i <= n; ++i)
        w[i] = read();
    for(int i = 2; i <= n; ++i) {
        int p = read();
        addEdge(p, i);
    }
    solve(1);
    printf("%" PRId64 "\n", A[1].sum);
    return 0;
}
