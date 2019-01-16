#include <algorithm>
#include <cstdio>
#include <cstring>
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
std::vector<int> A[305];
bool cmp(int a, int b) {
    return a > b;
}
const int maxk = 50005;
typedef long long Int64;
Int64 dp[maxk], w[maxk], old[maxk];
int lut[maxk], num;
void solve(int l, int r, int pl, int pr) {
    if(l > r)
        return;
    int m = (l + r) >> 1, trans = 0,
        end = std::min(pr, m);
    Int64 maxv = 0;
    for(int i = std::max(pl, m - num); i <= end; ++i) {
        Int64 val = old[lut[i]] + w[m - i];
        if(val > maxv)
            trans = i, maxv = val;
    }
    dp[lut[m]] = maxv;
    solve(l, m - 1, pl, trans);
    solve(m + 1, r, trans, pr);
}
int main() {
    int n = read();
    int k = read();
    for(int i = 1; i <= n; ++i) {
        int c = read();
        A[c].push_back(read());
    }
    for(int i = 1; i <= 300; ++i)
        if(A[i].size()) {
            memcpy(old + 1, dp + 1, sizeof(Int64) * k);
            int end = std::min(
                static_cast<int>(A[i].size()), k / i);
            std::partial_sort(A[i].begin(),
                              A[i].begin() + end,
                              A[i].end(), cmp);
            for(int j = 0; j < end; ++j)
                w[j + 1] = w[j] + A[i][j];
            num = end;
            for(int j = 0; j < i; ++j) {
                int cnt = 0, now = j;
                while(now <= k) {
                    lut[++cnt] = now;
                    now += i;
                }
                solve(2, cnt, 1, cnt);
            }
        }
    for(int i = 1; i <= k; ++i)
        printf("%lld ", dp[i]);
    return 0;
}
