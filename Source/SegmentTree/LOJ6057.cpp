#include <algorithm>
#include <cstdio>
typedef long long Int64;
#define asInt64 static_cast<Int64>
namespace IO {
    int A, B, C, P;
    Int64 lastAns = 0;
    inline int rnd() {
        return A = (A * B +
                    (C ^
                     (int)(lastAns & 0x7fffffffLL)) %
                        P) %
            P;
    }
    void init() {
        scanf("%d%d%d%d", &A, &B, &C, &P);
    }
}
const int size = 1 << 17, mod = 1000000007;
struct Data {
    Int64 sumAA, sumAB, pms;
    int rank;
} P[size * 20], *ap = P;
Data* alloc(int l, int r) {
    Data* res = ap - l;
    ap = res + r;
    return res;
}
struct Node {
    int m;
    Data* data;
    Int64 query(int l, int r) const {
        Int64 res = data[l].sumAA + data[r].sumAA;
        int lrk = data[l].rank, rrk = data[r].rank;
        if(lrk < rrk) {
            res += data[l].sumAB;
            Int64 lcnt = m - l, rcnt = lrk - lcnt;
            Int64 rsum = data[r].pms -
                (rcnt ? data[m + rcnt - 1].pms : 0);
            res += lcnt * rsum;
        } else {
            res += data[r].sumAB;
            Int64 rcnt = r - m + 1, lcnt = rrk - rcnt;
            Int64 lsum = data[l].pms -
                (lcnt ? data[m - lcnt].pms : 0);
            res += rcnt * lsum;
        }
        return res;
    }
} T[size << 1];
int A[size], B[size], n;
std::pair<int, int> st[size];
Int64 psum[size];
//[l,r)
void build(int l, int r, int id) {
    if(l + 1 == r || n <= l)
        return;
    int m = (l + r) >> 1;
    build(l, m, id << 1);
    build(m, r, id << 1 | 1);
    T[id].m = m;
    T[id].data = alloc(l, r);
    int top = 0, minv = 1 << 30;
    Int64 cans = 0, pms = 0;
    st[top].second = m;
    for(int i = m - 1; i >= l; --i) {
        int val = A[i];
        minv = std::min(minv, val);
        B[i] = minv;
        pms += minv;
        T[id].data[i].pms = pms;
        while(top && st[top].first >= val)
            --top;
        Int64 mul = asInt64(st[top].second - i) * val;
        ++top;
        st[top] = std::make_pair(val, i);
        psum[top] = psum[top - 1] + mul;
        cans += psum[top];
        T[id].data[i].sumAA = cans;
    }
    top = cans = pms = 0, minv = 1 << 30,
    st[top].second = m - 1;
    for(int i = m; i < r; ++i) {
        int val = A[i];
        minv = std::min(minv, val);
        B[i] = minv;
        pms += minv;
        T[id].data[i].pms = pms;
        while(top && st[top].first >= val)
            --top;
        Int64 mul = asInt64(i - st[top].second) * val;
        ++top;
        st[top] = std::make_pair(val, i);
        psum[top] = psum[top - 1] + mul;
        cans += psum[top];
        T[id].data[i].sumAA = cans;
    }
    int lp = m - 1, rp = m, crk = 0;
    cans = 0;
    while(l <= lp || rp < r) {
        if(rp >= r || (l <= lp && B[lp] > B[rp])) {
            T[id].data[lp].rank = ++crk;
            Int64 rcnt = crk - (m - lp);
            cans += rcnt * B[lp];
            T[id].data[lp].sumAB = cans;
            --lp;
        } else {
            T[id].data[rp].rank = ++crk;
            Int64 lcnt = crk - (rp - m + 1);
            cans += lcnt * B[rp];
            T[id].data[rp].sumAB = cans;
            ++rp;
        }
    }
}
const int maxb = 10, maxp = 1 << maxb;
int lg2[maxp];
int getLog(int x) {
    return x < maxp ? lg2[x] : maxb + lg2[x >> maxb];
}
Int64 query(int l, int r, int N) {
    if(l == r)
        return A[l];
    else {
        int pl = l + N, pr = r + N;
        int lca = pl >> (getLog(pl ^ pr) + 1);
        return T[lca].query(l, r);
    }
}
int main() {
    for(int i = 2; i < maxp; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    int q;
    scanf("%d%d", &n, &q);
    for(int i = 0; i < n; ++i)
        scanf("%d", &A[i]);
    IO::init();
    int N = 1;
    while(N < n)
        N <<= 1;
    build(0, N, 1);
    int ans = 0;
    for(int i = 0; i < q; ++i) {
        int l = IO::rnd() % n, r = IO::rnd() % n;
        if(l > r)
            std::swap(l, r);
        IO::lastAns = query(l, r, N);
        ans = (ans + IO::lastAns) % mod;
    }
    printf("%d\n", (ans + mod) % mod);
    return 0;
}
