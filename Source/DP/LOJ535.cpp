#include <algorithm>
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
const int size = 300005;
int S[size];
void reset(int n) {
    memset(S + 1, 0, sizeof(int) * n);
}
void add(int x, int n) {
    while(x <= n) {
        ++S[x];
        x += x & -x;
    }
}
int query(int x) {
    int res = 0;
    while(x) {
        res += S[x];
        x -= x & -x;
    }
    return res;
}
int maxv[size << 2];
void modify(int l, int r, int id, int nl, int nr,
            int op) {
    if(nl <= l && r <= nr)
        maxv[id] += op;
    else {
        int tag = maxv[id] -
            std::max(maxv[id << 1], maxv[id << 1 | 1]),
            m = (l + r) >> 1;
        if(nl <= m)
            modify(l, m, id << 1, nl, nr, op);
        if(m < nr)
            modify(m + 1, r, id << 1 | 1, nl, nr, op);
        maxv[id] = std::max(maxv[id << 1],
                            maxv[id << 1 | 1]) +
            tag;
    }
}
struct Seg {
    int op, l, r, p;
    bool operator<(const Seg& rhs) const {
        return p < rhs.p;
    }
} B[size * 2];
int A[size], L[size], R[size];
int findL(int x, int n) {
    int l = 1, r = n, res = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(A[L[m]] > x)
            res = m, r = m - 1;
        else
            l = m + 1;
    }
    return res ? L[res] : (1 << 30);
}
int findR(int x, int n) {
    int l = 1, r = n, res = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(A[R[m]] < x)
            res = m, r = m - 1;
        else
            l = m + 1;
    }
    return res ? R[res] : 0;
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int lc = 0;
    for(int i = 1; i <= n; ++i)
        if(A[i] > A[L[lc]])
            L[++lc] = i;
    A[0] = 1 << 30;
    int rc = 0;
    for(int i = n; i >= 1; --i)
        if(A[i] < A[R[rc]])
            R[++rc] = i;
    int scnt = 0;
    for(int i = 1; i <= n; ++i) {
        int l = findL(A[i], lc), r = findR(A[i], rc);
        if(l < i && r > i) {
            ++scnt;
            B[scnt].op = 1, B[scnt].l = i + 1,
            B[scnt].r = r, B[scnt].p = l;
            ++scnt;
            B[scnt].op = -1, B[scnt].l = i + 1,
            B[scnt].r = r, B[scnt].p = i;
        }
    }
    std::sort(B + 1, B + scnt + 1);
    int maxs = 0, l = 1;
    for(int i = 1; i <= n; ++i) {
        while(l <= scnt && B[l].p <= i) {
            modify(1, n, 1, B[l].l, B[l].r, B[l].op);
            ++l;
        }
        maxs = std::max(maxs, maxv[1]);
    }
    long long res = 0;
    for(int i = n; i >= 1; --i) {
        res += query(A[i]);
        add(A[i], n);
    }
    printf("%lld\n", res - 2 * maxs);
    return 0;
}
