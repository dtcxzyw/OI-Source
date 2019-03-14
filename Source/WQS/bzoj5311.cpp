#include <algorithm>
#include <cstdio>
#include <cstring>
namespace IO {
    void init() {
        // setvbuf(stdin, 0, _IONBF, 0);
        // setvbuf(stdout, 0, _IONBF, 0);
    }
    const int size = 1 << 23;
    char in[size];
    char getc() {
        static char *S = in, *T = in;
        if(S == T)
            S = in, T = in + fread(in, 1, size, stdin);
        return S == T ? EOF : *S++;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 4005;
int B[size][size], n, C, dp[size];
int calc(int i, int j) {
    return dp[j] + B[j + 1][i] + C;
}
int getEdge(int x, int y) {
    int l = y, r = n, res = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(calc(m, x) <= calc(m, y))
            res = m, l = m + 1;
        else
            r = m - 1;
    }
    return res + 1;
}
int num[size], q[size], k[size];
int solve(int c) {
    C = c;
    int b = 1, e = 1;
    q[1] = 0;
    for(int i = 1; i <= n; ++i) {
        while(b < e && k[b] <= i)
            ++b;
        num[i] = num[q[b]] + 1;
        dp[i] = calc(i, q[b]);
        while(b < e && getEdge(q[e], i) <= k[e - 1])
            --e;
        k[e] = getEdge(q[e], i);
        q[++e] = i;
    }
    return num[n];
}
int A[size][size];
int main() {
    IO::init();
    n = read();
    int k = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            A[i][j] = A[i][j - 1] + read();
    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j)
            B[i][j] =
                B[i][j - 1] + A[j][j] - A[j][i - 1];
    int l = 0, r = B[1][n], ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(solve(m) <= k)
            r = m - 1, ans = dp[n] - m * k;
        else
            l = m + 1;
    }
    printf("%d\n", ans);
    return 0;
}
