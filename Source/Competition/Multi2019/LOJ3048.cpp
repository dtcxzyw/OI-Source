#include <cstdio>
#include <queue>
namespace IO {
    char in[1 << 23];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
}
typedef unsigned int U32;
U32 read() {
    U32 res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10U + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 500005, maxd = 31;
struct Node {
    int siz, c[2];
} T[size * 80];
int root[size], tcnt = 0;
int modify(int src, U32 x, int d, int op) {
    int id = ++tcnt;
    T[id] = T[src];
    T[id].siz += op;
    if(d != -1) {
        int& c = T[id].c[(x >> d) & 1];
        c = modify(c, x, d - 1, op);
    }
    return id;
}
U32 query(int id, U32 x, int d) {
    if(d == -1)
        return 0;
    int bx = (x >> d) & 1, nb = bx ^ 1,
        c = T[id].c[nb];
    if(T[c].siz)
        return query(c, x, d - 1) | (1U << d);
    return query(T[id].c[bx], x, d - 1);
}
struct Sol {
    int u;
    U32 val;
    Sol(int u, U32 val) : u(u), val(val) {}
    bool operator<(const Sol& rhs) const {
        return val < rhs.val;
    }
};
U32 A[size];
Sol getSol(int u) {
    U32 x = A[u - 1];
    U32 val = query(root[u], x, maxd);
    root[u] = modify(root[u], x ^ val, maxd, -1);
    return Sol(u, val);
}
typedef unsigned long long U64;
int main() {
    IO::init();
    int n = read();
    int k = read();
    for(int i = 1; i <= n; ++i)
        A[i] = A[i - 1] ^ read();
    for(int i = n; i >= 1; --i)
        root[i] = modify(root[i + 1], A[i], maxd, 1);
    std::priority_queue<Sol> heap;
    for(int i = 1; i <= n; ++i)
        heap.push(getSol(i));
    U64 sum = 0;
    for(int i = 1; i <= k; ++i) {
        sum += heap.top().val;
        int u = heap.top().u;
        heap.pop();
        if(T[root[u]].siz)
            heap.push(getSol(u));
    }
    printf("%llu\n", sum);
    return 0;
}
