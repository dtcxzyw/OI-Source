#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <deque>
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
const int magic = 0xc0c0c0c0;
struct Info {
    std::deque<int> blks;
    Int64 sum;
    int sig;
    void swap(Info& rhs) {
        blks.swap(rhs.blks);
        std::swap(sum, rhs.sum);
        std::swap(sig, rhs.sig);
    }
    int top() {
        int res;
        if(blks.empty() || sig > blks.front()) {
            res = sig;
            sig = magic;
        } else {
            res = blks.front();
            blks.pop_front();
        }
        sum -= res;
        return res;
    }
    int size() const {
        return blks.size() + (sig != magic);
    }
} A[size];
int buf[size];
void merge(Info& a, Info& b) {
    if(a.size() < b.size())
        std::swap(a, b);
    int bsiz = 0;
    while(b.size()) {
        int u = a.top();
        int v = b.top();
        buf[++bsiz] = std::max(u, v);
    }
    if(a.sig != magic) {
        a.blks.insert(std::lower_bound(a.blks.begin(),
                                       a.blks.end(),
                                       a.sig),
                      a.sig);
        a.sig = magic;
    }
    a.blks.insert(a.blks.begin(), buf + 1,
                  buf + bsiz + 1);
    for(int i = 1; i <= bsiz; ++i)
        a.sum += buf[i];
}
int w[size];
void solve(int u) {
    A[u].sig = magic;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        solve(v);
        merge(A[u], A[v]);
    }
    A[u].sig = w[u];
    A[u].sum += w[u];
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
