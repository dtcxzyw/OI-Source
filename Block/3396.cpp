#include <cmath>
#include <cstdio>
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
    while (c != 'A' && c != 'C');
    return c;
}
const int size = 150005, sqrtN = 400;
int A[size], B[sqrtN][sqrtN] = {};
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i <= n; ++i) A[i] = read();
    int end = pow(n, 1.0 / 3.0);
    for (int i = 1; i <= end; ++i) {
        int k = i == 1 ? 0 : 1;
        for (int j = 1; j <= n; ++j) {
            B[i][k] += A[j];
            ++k;
            if (k == i) k = 0;
        }
    }
    while (m--) {
        if (getOp() == 'A') {
            int p = read();
            int x = read();
            int res = 0;
            if (p <= end)
                res = B[p][x];
            else {
                for (int i = x; i <= n; i += p)
                    res += A[i];
            }
            printf("%d\n", res);
        } else {
            int u = read();
            int old = A[u];
            A[u] = read();
            int delta = A[u] - old;
            for (int i = 1; i <= end; ++i) B[i][u % i] += delta;
        }
    }
    return 0;
}
