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
const int size = 1000005;
int A[size], q[size], dp[size];
bool cmp(int a, int b) {
    return dp[a] == dp[b] ? A[a] <= A[b] :
                            dp[a] > dp[b];
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int t = read();
    for(int x = 1; x <= t; ++x) {
        int k = read(), b = 1, e = 1;
        q[1] = 1, dp[1] = 0;
        for(int i = 2; i <= n; ++i) {
            while(b < e && q[b] + k < i)
                ++b;
            int t = q[b];
            dp[i] = dp[t] + (A[t] <= A[i]);
            while(b < e && cmp(q[e], i))
                --e;
            q[++e] = i;
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
