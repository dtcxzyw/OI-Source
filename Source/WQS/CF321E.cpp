#include <algorithm>
#include <cstdio>
namespace IO {
    char in[1 << 23], *S = in, *T = in;
    char getc() {
        if(S == T)
            S = in,
            T = in + fread(in, 1, sizeof(in), stdin);
        return S != T ? *S++ : EOF;
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
int S[size][size];
int getW(int l, int r) {
    return (S[r][r] - S[l][r] - S[r][l] + S[l][l]) / 2;
}
int P[size], tp[size], dp[size], cnt[size];
int getEdge(int x, int y, int n) {
    int l = y, r = n, ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(dp[x] + getW(x, m) <= dp[y] + getW(y, m))
            ans = m, l = m + 1;
        else
            r = m - 1;
    }
    return ans + 1;
}
std::pair<int, int> solve(int n, int m) {
    int b = 0, e = 0;
    for(int i = 1; i <= n; ++i) {
        while(b + 1 <= e && P[b + 1] <= i)
            ++b;
        int t = tp[b];
        dp[i] = dp[t] + getW(t, i) + m;
        cnt[i] = cnt[t] + 1;
        while(b + 1 <= e &&
              P[e] >= getEdge(tp[e], i, n))
            --e;
        ++e;
        P[e] = getEdge(tp[e - 1], i, n), tp[e] = i;
    }
    return std::make_pair(dp[n], cnt[n]);
}
int main() {
    int n = read();
    int k = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            S[i][j] = read() + S[i - 1][j] +
                S[i][j - 1] - S[i - 1][j - 1];
    int l = 0, r = getW(0, n), ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        std::pair<int, int> res = solve(n, m);
        if(res.second == k)
            ans = res.first - m * k;
        if(res.second < k)
            ans = res.first - m * k, r = m - 1;
        else
            l = m + 1;
    }
    printf("%d\n", ans);
    return 0;
}
