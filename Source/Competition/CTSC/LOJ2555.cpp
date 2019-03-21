#include <algorithm>
#include <cstdio>
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
typedef long long Int64;
#define asInt64 static_cast<Int64>
template <typename T>
void read(T& res) {
    res = 0;
    T c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
}
const int size = 100005;
struct Node {
    int l, r;
    Int64 sumW, sumL;
} T[size * 30];
int tcnt = 0;
int insert(int l, int r, int src, int p, int L) {
    int id = ++tcnt;
    T[id] = T[src];
    T[id].sumW += asInt64(p) * L, T[id].sumL += L;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = insert(l, m, T[id].l, p, L);
        else
            T[id].r = insert(m + 1, r, T[id].r, p, L);
    }
    return id;
}
bool query(int l, int r, int id, Int64 L, Int64 g) {
    if(l == r)
        return L * l <= g;
    else {
        int m = (l + r) >> 1, lc = T[id].l;
        Int64 ll = T[lc].sumL;
        if(ll > L)
            return query(l, m, T[id].l, L, g);
        Int64 lw = T[lc].sumW;
        if(lw > g)
            return false;
        return query(m + 1, r, T[id].r, L - ll,
                     g - lw);
    }
}
int root[size], d[size];
struct Info {
    int d, p, l;
    bool operator<(const Info& rhs) const {
        return d > rhs.d;
    }
} A[size];
int main() {
    IO::init();
    int n, m;
    read(n);
    read(m);
    int maxp = 1;
    for(int i = 0; i < n; ++i) {
        read(A[i].d);
        read(A[i].p);
        read(A[i].l);
        maxp = std::max(maxp, A[i].p);
    }
    std::sort(A, A + n);
    int cur = 0;
    for(int i = 0; i < n; ++i) {
        if(d[cur] != A[i].d) {
            ++cur;
            root[cur] = root[cur - 1];
            d[cur] = A[i].d;
        }
        root[cur] =
            insert(1, maxp, root[cur], A[i].p, A[i].l);
    }
    for(int i = 1; i <= m; ++i) {
        Int64 g, L;
        read(g);
        read(L);
        int l = 1, r = cur, ans = 0;
        while(l <= r) {
            int m = (l + r) >> 1;
            int rt = root[m];
            if(T[rt].sumL >= L &&
               query(1, maxp, rt, L, g))
                ans = m, r = m - 1;
            else
                l = m + 1;
        }
        if(ans)
            printf("%d\n", d[ans]);
        else
            puts("-1");
    }
    return 0;
}
