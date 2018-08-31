#include <algorithm>
#include <cstdio>
#include <cstring>
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
int B[size], A[20][size], cnt[20][size];
void build(int l, int r, int d) {
    if(l == r)
        return;
    int m = (l + r) >> 1, lp = l, rp = m + 1,
        key = B[m], *AA = A[d], *NAA = A[d + 1],
        *AC = cnt[d], lts = m - l + 1;
    for(int i = l; i <= r; ++i)
        if(AA[i] < key)
            --lts;
    for(int i = l; i <= r; ++i) {
        AC[i] = (i == l ? 0 : AC[i - 1]);
        int val = AA[i];
        if(val < key || (val == key && lts > 0)) {
            NAA[lp++] = val;
            ++AC[i];
            if(val == key)
                --lts;
        } else
            NAA[rp++] = val;
    }
    build(l, m, d + 1);
    build(m + 1, r, d + 1);
}
int query(int l, int r, int d, int nl, int nr, int k) {
    if(l == r)
        return A[d][l];
    int cl = l == nl ? 0 : cnt[d][nl - 1],
        cr = cnt[d][nr], delta = cr - cl,
        m = (l + r) >> 1;
    if(k <= delta) {
        int lb = l + cl;
        int le = l + cr - 1;
        return query(l, m, d + 1, lb, le, k);
    } else {
        int rb = m + 1 + (nl - l - cl);
        int re = rb + nr - nl - delta;
        return query(m + 1, r, d + 1, rb, re,
                     k - delta);
    }
}
int main() {
    int n = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        A[0][i] = read();
    memcpy(B + 1, A[0] + 1, sizeof(int) * n);
    std::sort(B + 1, B + n + 1);
    build(1, n, 0);
    while(q--) {
        int l = read();
        int r = read();
        int k = read();
        printf("%d\n", query(1, n, 0, l, r, k));
    }
    return 0;
}
