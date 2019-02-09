#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 100005;
typedef long long Int64;
int k;
struct Pair {
    Int64 sum, tag;
};
void update(Pair* A, int id, Int64 len) {
    A[id].sum = A[id << 1].sum + A[id << 1 | 1].sum +
        len * A[id].tag;
}
void add(Pair* A, int s, int t, Int64 v) {
    Int64 p = 1;
    for(s += k - 1, t += k + 1; s ^ t ^ 1;
        s >>= 1, t >>= 1, p <<= 1) {
        if(~s & 1)
            A[s ^ 1].sum += p * v, A[s ^ 1].tag += v;
        if(t & 1)
            A[t ^ 1].sum += p * v, A[t ^ 1].tag += v;
        update(A, s >> 1, p << 1);
        update(A, t >> 1, p << 1);
    }
    while(s > 1)
        update(A, s >>= 1, p <<= 1);
}
Int64 query(Pair* A, int s, int t) {
    Int64 p = 1, res = 0, lc = 0, rc = 0;
    for(s += k - 1, t += k + 1; s ^ t ^ 1;
        s >>= 1, t >>= 1, p <<= 1) {
        res += lc * A[s].tag + rc * A[t].tag;
        if(~s & 1) {
            res += A[s ^ 1].sum;
            lc += p;
        }
        if(t & 1) {
            res += A[t ^ 1].sum;
            rc += p;
        }
    }
    res += lc * A[s].tag + rc * A[t].tag;
    Int64 stag = 0;
    while(s > 1) {
        s >>= 1;
        stag += A[s].tag;
    }
    return res + (lc + rc) * stag;
}
Pair A[size << 2], B[size << 2];
int main() {
    int n = read();
    k = 1;
    while(k - 2 < n)
        k <<= 1;
    for(int i = 1; i <= n; ++i)
        A[i + k].sum = read();
    for(int i = k - 1; i >= 1; --i)
        A[i].sum = A[i << 1].sum + A[i << 1 | 1].sum;
    int m = read();
    for(int i = 1; i <= m; ++i) {
        int d = read();
        int l = read();
        int r = read();
        if(d == 1) {
            Int64 x = read();
            add(A, l, r, x * (1 - i));
            add(B, l, r, x);
        } else
            printf("%lld\n", query(B, l, r) * (i - 1) +
                       query(A, l, r));
    }
    return 0;
}
