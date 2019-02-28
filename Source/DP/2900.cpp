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
const int size = 50005;
typedef long long Int64;
#define asInt64 static_cast<Int64>
struct RECT {
    int w, h;
    bool operator<(const RECT& rhs) const {
        return w == rhs.w ? h > rhs.h : w < rhs.w;
    }
} A[size];
int q[size];
Int64 dp[size];
Int64 deltaA(int i, int j) {
    return dp[i - 1] - dp[j - 1];
}
Int64 deltaB(int i, int j) {
    return A[i].h - A[j].h;
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i) {
        A[i].w = read();
        A[i].h = read();
    }
    std::sort(A + 1, A + n + 1);
    int cur = 0;
    for(int i = 1; i <= n; ++i) {
        while(cur && A[cur].h <= A[i].h)
            --cur;
        A[++cur] = A[i];
    }
    n = cur;
    int b = 1, e = 0;
    for(int i = 1; i <= n; ++i) {
        while(b + 1 <= e &&
              deltaA(q[e - 1], q[e]) *
                      deltaB(q[e], i) <=
                  deltaA(q[e], i) *
                      deltaB(q[e - 1], q[e]))
            --e;
        q[++e] = i;
        while(b + 1 <= e &&
              -A[i].w * deltaB(q[b], q[b + 1]) <=
                  deltaA(q[b], q[b + 1]))
            ++b;
        int t = q[b];
        dp[i] = dp[t - 1] + asInt64(A[i].w) * A[t].h;
    }
    printf("%lld\n", dp[n]);
    return 0;
}
