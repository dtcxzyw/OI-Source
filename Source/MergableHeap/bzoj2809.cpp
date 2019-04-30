#include <algorithm>
#include <cstdio>
namespace IO {
    char in[1 << 22];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
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
const int size = 100005;
struct Node {
    int val, son, bro;
} T[size];
int merge(int u, int v) {
    if(u && v) {
        if(T[u].val < T[v].val)
            std::swap(u, v);
        T[v].bro = T[u].son;
        T[u].son = v;
        return u;
    }
    return u | v;
}
int mergeBro(int u) {
    if(u == 0 || T[u].bro == 0)
        return u;
    int a = T[u].bro, b = T[a].bro;
    T[u].bro = T[a].bro = 0;
    return merge(merge(u, a), mergeBro(b));
}
struct Heap {
    int rt, siz, sum;
    Heap(int rt, int siz, int sum)
        : rt(rt), siz(siz), sum(sum) {}
    Heap() {}
};
int M;
Heap merge(const Heap& a, const Heap& b) {
    Heap res(merge(a.rt, b.rt), a.siz + b.siz,
             a.sum + b.sum);
    while(res.sum > M) {
        res.sum -= T[res.rt].val;
        --res.siz;
        res.rt = mergeBro(T[res.rt].son);
    }
    return res;
}
Heap hs[size];
int B[size], L[size];
typedef long long Int64;
int main() {
    IO::init();
    int n = read();
    M = read();
    for(int i = 1; i <= n; ++i) {
        B[i] = read();
        T[i].val = read();
        hs[i].rt = i;
        hs[i].siz = 1;
        hs[i].sum = T[i].val;
        L[i] = read();
    }
    Int64 res = 0;
    for(int i = n; i >= 1; --i) {
        Int64 fac = L[i];
        res = std::max(res, fac * hs[i].siz);
        if(B[i])
            hs[B[i]] = merge(hs[B[i]], hs[i]);
    }
    printf("%lld\n", res);
    return 0;
}
