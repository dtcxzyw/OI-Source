#include <algorithm>
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
std::vector<int> A[305];
bool cmp(int a, int b) {
    return a < b;
}
long long dp[50005];
int main() {
    int n = read();
    int k = read();
    for(int i = 1; i <= n; ++i) {
        int c = read();
        A[c].push_back(read());
    }
    for(int i = 1; i <= 300; ++i)
        if(A[i].size()) {
            printf("cur %d\n", i);
            int end = std::min(
                static_cast<int>(A[i].size()), k / i);
            std::partial_sort(A[i].begin(),
                              A[i].begin() + end,
                              A[i].end(), cmp);
            for(int j = 1; j <= k; ++j)
                printf("%lld ", dp[j]);
            puts("");
        }
    for(int i = 1; i <= k; ++i)
        printf("%lld ", dp[i]);
    return 0;
}
