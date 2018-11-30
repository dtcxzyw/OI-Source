#include <cstdio>
#include <cstring>
typedef long long Int64;
Int64 dp[19][165][165];
int pt[19];
void pre(int n, int mod) {
    memset(dp, 0, sizeof(dp));
    pt[1] = 1;
    for(int i = 2; i <= n; ++i)
        pt[i] = pt[i - 1] * 10 % mod;
    dp[0][0][0] = 1;
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < mod; ++j) {
            for(int k = 0; k <= mod; ++k)
                if(dp[i - 1][j][k]) {
                    for(int l = 0;
                        l <= 9 && k + l <= mod; ++l)
                        dp[i][(j * 10 + l) % mod]
                          [k + l] += dp[i - 1][j][k];
                }
        }
    }
}
int B[20];
int unfold(Int64 x) {
    int bit = 0;
    while(x) {
        B[++bit] = x % 10;
        x /= 10;
    }
    return bit;
}
Int64 calc(Int64 x, int mod) {
    if(x == 0)
        return 0;
    int n = unfold(x);
    Int64 res = dp[n - 1][0][mod];
    int csum = 0, cmod = 0;
    for(int i = n; i >= 1 && csum <= mod; --i) {
        for(int j = (i == n); j < B[i]; ++j) {
            int sum = csum + j;
            if(sum > mod)
                break;
            int mv = (cmod * 10 + j) * pt[i] % mod;
            if(mv)
                mv = mod - mv;
            res += dp[i - 1][mv][mod - sum];
        }
        csum += B[i];
        cmod = (cmod * 10 + B[i]) % mod;
    }
    if(csum == mod && cmod == 0)
        ++res;
    return res;
}
int main() {
    Int64 a, b;
    scanf("%lld%lld", &a, &b);
    Int64 res = 0;
    int n = unfold(b);
    if(n == 19)
        n = 18, --b, ++res;
    int end = 9 * n;
    for(int i = 1; i <= end; ++i) {
        pre(n, i);
        res += calc(b, i) - calc(a - 1, i);
    }
    printf("%lld\n", res);
    return 0;
}
