#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int getOp() {
    int c;
    do
        c = getchar();
    while (c != 'M' && c != 'A');
    return c;
}
const int size = 1000005, blockSize = 1005;
int A[size], B[size], offset[blockSize] = {};
void update(int l, int r) {
    memcpy(B + l, A + l, sizeof(int) * (r - l + 1));
    std::sort(B + l, B + r + 1);
}
int main() {
    int n = read();
    int bsiz = sqrt(n);
    int q = read();
    for (int i = 1; i <= n; ++i) A[i] = read();
    memcpy(B, A, sizeof(int) * (n + 1));
    int bid = n / bsiz;
    for (int i = 0; i <= bid; ++i) {
        int beg = std::max(1, i * bsiz);
        int end = std::min((i + 1) * bsiz - 1, n);
        std::sort(B + beg, B + end + 1);
    }
    while (q--) {
        int op = getOp();
        int l = read();
        int r = read();
        int w = read();
        int lb = l / bsiz, rb = r / bsiz;
        int bl = std::max(1, lb * bsiz);
        int el = std::min((lb + 1) * bsiz - 1, n);
        int br = std::max(1, rb * bsiz);
        int er = std::min((rb + 1) * bsiz - 1, n);
        if (op == 'M') {
            if (lb == rb) {
                for (int i = l; i <= r; ++i) A[i] += w;
                update(bl, el);
            } else {
                for (int i = l; i <= el; ++i) A[i] += w;
                update(bl, el);
                for (int i = lb + 1; i < rb; ++i) offset[i] += w;
                for (int i = br; i <= r; ++i) A[i] += w;
                update(br, er);
            }
        } else {
            int cnt = 0;
            if (lb == rb) {
                int bw = w - offset[lb];
                for (int i = l; i <= r; ++i) cnt += A[i] >= bw;
            } else {
                int lbw = w - offset[lb];
                for (int i = l; i <= el; ++i) cnt += A[i] >= lbw;
                for (int i = lb + 1; i < rb; ++i) {
                    int beg = std::max(1, i * bsiz);
                    int end = std::min((i + 1) * bsiz - 1, n);
                    int bw = w - offset[i];
                    cnt += (B + end + 1) - std::lower_bound(B + beg, B + end + 1, bw);
                }
                int rbw = w - offset[rb];
                for (int i = br; i <= r; ++i) cnt += A[i] >= rbw;
            }
            printf("%d\n", cnt);
        }
    }
    return 0;
}
