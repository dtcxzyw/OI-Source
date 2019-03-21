#include <algorithm>
#include <cstdio>
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
const int size = 1 << 18, mod = 1000000007;
void add(int& a, int b) {
    a += b;
    a = (a < mod ? a : a - mod);
}
int A[size], dp[size];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        int S = A[i], val = dp[S];
        add(res, val);
        ++val;
        for(int j = S; j; j = (j - 1) & S)
            add(dp[j], val);
    }
    printf("%d\n", res);
    return 0;
}
