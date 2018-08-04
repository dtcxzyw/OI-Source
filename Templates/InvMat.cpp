//TODO:P4783
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
const int size = 405, mod = 1000000007;
int A[size][size];
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            A[i][j] = read();

    return 0;
}
