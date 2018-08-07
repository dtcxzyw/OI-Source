#include <algorithm>
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
void print(int x) {
    int a = x / 10, b = x % 10;
    if (a) print(a);
    putchar('0' + b);
}
const int size = 405, mod = 1000000007;
typedef long long Int64;
Int64 inv(Int64 a) {
    Int64 res = 1;
    int k = mod - 2;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int A[size][size], B[size][size] = {};
bool solve(int n) {
    for (int i = 1; i <= n; ++i) B[i][i] = 1;
    for (int i = 1; i <= n; ++i) {
        int x = 0;
        for (int j = 1; j <= n; ++j)
            if (A[i][j]) {
                x = j;
                break;
            }
        if (x == 0) return false;
        Int64 invMv = inv(A[i][x]);
        for (int j = 1; j <= n; ++j) {
            std::swap(A[i][j], A[x][j]);
            std::swap(B[i][j], B[x][j]);
        }
        for (int j = 1; j <= n; ++j)
            if (j != x) {
                Int64 fac = A[j][x] * invMv % mod;
                for (int k = 1; k <= n; ++k) {
                    A[j][k] = sub(A[j][k], A[x][k] * fac % mod);
                    B[j][k] = sub(B[j][k], B[x][k] * fac % mod);
                }
            }
        for (int j = 1; j <= n; ++j) {
            A[x][j] = A[x][j] * invMv % mod;
            B[x][j] = B[x][j] * invMv % mod;
        }
    }
    return true;
}
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            A[i][j] = read();
    if (solve(n)) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                print(B[i][j]);
                putchar(' ');
            }
            putchar('\n');
        }
    } else
        puts("No Solution");
    return 0;
}
