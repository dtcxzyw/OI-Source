#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 100005;
int A[size], B[size], C[size];
Int64 cans;
void add(int pos, Int64& ans) {
    int col = A[pos];
    Int64 val = asInt64(++C[col]) * B[col];
    if(val > ans)
        ans = val;
}
Int64 query(int l, int r) {
    Int64 ans = cans;
    for(int i = l; i <= r; ++i)
        add(i, ans);
    for(int i = l; i <= r; ++i)
        --C[A[i]];
    return ans;
}
struct Queue {
    int l, r, bid, id;
    bool operator<(const Queue& rhs) const {
        return bid == rhs.bid ? r < rhs.r :
                                bid < rhs.bid;
    }
} Q[size];
Int64 ans[size];
int main() {
    int n = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    memcpy(B + 1, A + 1, sizeof(int) * n);
    std::sort(B + 1, B + n + 1);
    int siz = std::unique(B + 1, B + n + 1) - (B + 1);
    for(int i = 1; i <= n; ++i)
        A[i] = std::lower_bound(B + 1, B + siz + 1,
                                A[i]) -
            B;
    int bsiz = sqrt(n) + 1;
    for(int i = 1; i <= q; ++i) {
        Q[i].l = read();
        Q[i].r = read();
        Q[i].id = i;
        Q[i].bid = Q[i].l / bsiz;
    }
    std::sort(Q + 1, Q + q + 1);
    Q[0].bid = -1;
    int bend, cr;
    for(int i = 1; i <= q; ++i) {
        if(Q[i].bid != Q[i - 1].bid) {
            memset(C + 1, 0, sizeof(int) * siz);
            cans = 0;
            cr = (Q[i].bid + 1) * bsiz;
            bend = cr - 1;
        }
        while(cr <= Q[i].r)
            add(cr++, cans);
        ans[Q[i].id] =
            query(Q[i].l, std::min(bend, Q[i].r));
    }
    for(int i = 1; i <= q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
