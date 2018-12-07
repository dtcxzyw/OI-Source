// P3488
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
const int size = 500005 << 2;
typedef long long Int64;
Int64 maxv(Int64 a, Int64 b) {
    return a > b ? a : b;
}
Int64 L[size], R[size], sum[size], maxs[size];
void update(int id) {
    L[id] = maxv(L[id << 1],
                 sum[id << 1] + L[id << 1 | 1]);
    R[id] = maxv(R[id << 1] + sum[id << 1 | 1],
                 R[id << 1 | 1]);
    maxs[id] =
        maxv(maxv(maxs[id << 1], maxs[id << 1 | 1]),
             R[id << 1] + L[id << 1 | 1]);
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
Int64 k;
void build(int l, int r, int id) {
    sum[id] = (l - r - 1) * k;
    if(l != r) {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
    }
}
int p, val;
void modify(int l, int r, int id) {
    sum[id] += val;
    if(l == r)
        L[id] = R[id] = maxs[id] = maxv(sum[id], 0);
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            modify(ls);
        else
            modify(rs);
        update(id);
    }
}
int main() {
    int n = read();
    int m = read();
    k = read();
    Int64 key = read() * k;
    build(1, n, 1);
    while(m--) {
        p = read();
        val = read();
        modify(1, n, 1);
        puts(maxs[1] <= key ? "TAK" : "NIE");
    }
    return 0;
}
