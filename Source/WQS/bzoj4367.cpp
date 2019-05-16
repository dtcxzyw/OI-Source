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
int iabs(int x) {
    return x < 0 ? -x : x;
}
const int size = 100005;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int A[size];
std::pair<Int64, int> solve(int n, int m, int s) {
    int l = 0, r = 0, cnt = 0;
    Int64 sum = 0;
    for(int i = 1; i <= n; ++i)
        if(A[i] > m) {
            sum += A[i], ++cnt, r = i;
            if(l == 0)
                l = i;
        }
    if(cnt == 0)
        l = r = s;
    return std::make_pair(
        sum - asInt64(cnt) * m, r - l +
            std::min(iabs(l - s), iabs(r - s)) + cnt);
}
int main() {
    int n = read();
    int s = read();
    int d = read();
    int maxv = 0;
    for(int i = 1; i <= n; ++i) {
        A[i] = read();
        maxv = std::max(maxv, A[i]);
    }
    int l = 0, r = maxv;
    Int64 ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        std::pair<Int64, int> res = solve(n, m, s);
    }
    printf("%lld\n", ans);
    return 0;
}
