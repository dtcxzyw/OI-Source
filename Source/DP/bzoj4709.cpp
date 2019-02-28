#include <cstdio>
#include <vector>
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
const int size = 100005, maxc = 10005;
int ccnt[maxc], s[size];
struct Point {
    int p, end;
    Point(int p, int end) : p(p), end(end) {}
};
std::vector<Point> q[maxc];
typedef long long Int64;
Int64 dp[size];
inline Int64 calc(Int64 base, Int64 delta, Int64 c) {
    return base + c * delta * delta;
}
int n;
int getEdge(int x, int y, Int64 c) {
    int l = s[y], r = n + 1, res = 0;
    Int64 bx = dp[x - 1], by = dp[y - 1],
          dx = s[x] - 1, dy = s[y] - 1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(calc(bx, m - dx, c) < calc(by, m - dy, c))
            res = m, l = m + 1;
        else
            r = m - 1;
    }
    return res + 1;
}
int main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        int c = read();
        s[i] = ++ccnt[c];
        std::vector<Point>& P = q[c];
        while(P.size() >= 2 &&
              P.back().end <=
                  getEdge(P.back().p, i, c))
            P.pop_back();
        P.push_back(Point(
            i, P.empty() ? 0 :
                           getEdge(P.back().p, i, c)));
        while(P.size() >= 2 && P.back().end <= s[i])
            P.pop_back();
        dp[i] = calc(dp[P.back().p - 1],
                     s[i] - s[P.back().p] + 1, c);
    }
    printf("%lld\n", dp[n]);
    return 0;
}
