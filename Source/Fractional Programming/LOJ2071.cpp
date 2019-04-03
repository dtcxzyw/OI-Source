#include <algorithm>
#include <cstdio>
typedef double FT;
const int size = 2505;
int K, S[size], P[size], R[size];
FT x;
struct Sol {
    int sp, ss;
    Sol() {}
    Sol(int sp, int ss) : sp(sp), ss(ss) {}
    bool operator<(const Sol& rhs) const {
        return sp - x * ss < rhs.sp - x * rhs.ss;
    }
    Sol operator+(const Sol& rhs) const {
        return Sol(sp + rhs.sp, ss + rhs.ss);
    }
} dp[size][size];
const int inf = 0x3f3f3f3f;
int siz[size];
void DP(int n) {
    for(int i = 0; i <= n; ++i)
        siz[i] = 1;
    for(int i = n; i >= 0; --i) {
        for(int j = 2; j <= siz[i] && j <= K; ++j)
            dp[i][j].sp = -inf, dp[i][j].ss = inf;
        if(i)
            siz[R[i]] += siz[i];
    }
    for(int i = 0; i <= n; ++i)
        siz[i] = 1;
    for(int i = n; i >= 1; --i) {
        int p = R[i], osiz = siz[p];
        siz[p] += siz[i];
        int end = std::min(siz[p], K);
        for(int j = end; j >= 2; --j)
            for(int k = std::max(j - osiz, 1);
                k <= siz[i] && k < j; ++k)
                dp[p][j] = std::max(
                    dp[p][j], dp[p][j - k] + dp[i][k]);
    }
}
int main() {
    int n;
    scanf("%d%d", &K, &n);
    ++K;
    for(int i = 1; i <= n; ++i)
        scanf("%d%d%d", &dp[i][1].ss, &dp[i][1].sp,
              &R[i]);
    x = 0.0;
    while(true) {
        DP(n);
        FT nx =
            static_cast<FT>(dp[0][K].sp) / dp[0][K].ss;
        if(nx - x > 1e-5)
            x = nx;
        else
            break;
    }
    printf("%.3lf\n", x);
    return 0;
}
