#include <cstdio>
namespace IO {
    const int size = 1 << 25;
    char buf[size];
    void init() {
        fread(buf, 1, size, stdin);
    }
    char getc() {
        static char* S = buf;
        return *S++;
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
const int size = 1000005;
struct Edge {
    int to, nxt, w;
} E[size * 2];
int last[size], cnt = 0;
void addEdge(int u, int v, int w) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u], E[cnt].w = w;
    last[u] = cnt;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
int n;
Int64 res = 0;
int diff(int a, int b) {
    return a < b ? b - a : a - b;
}
int DFS(int u, int p) {
    int siz = 1;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p) {
            int vsiz = DFS(v, u);
            res +=
                asInt64(diff(vsiz, n - vsiz)) * E[i].w;
            siz += vsiz;
        }
    }
    return siz;
}
int main() {
    IO::init();
    n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        int w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    DFS(1, 0);
    printf("%lld\n", res);
    return 0;
}
