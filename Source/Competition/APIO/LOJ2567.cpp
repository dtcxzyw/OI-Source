#include <algorithm>
#include <cstdio>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 505, mod = 1000000007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int A[size], B[size], C[size * 2], F[size * 2][size],
    S[size * 2], SS[size * 2], inv[size];
int main() {
    int n;
    scanf("%d", &n);
    int icnt = 0;
    C[icnt++] = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", &A[i], &B[i]);
        C[icnt++] = A[i] - 1;
        C[icnt++] = B[i];
    }
    inv[1] = 1;
    for(int i = 2; i <= n; ++i)
        inv[i] = asInt64(mod - mod / i) *
            inv[mod % i] % mod;
    std::sort(C, C + icnt);
    icnt = std::unique(C, C + icnt) - C;
    F[0][0] = S[0] = 1;
    SS[0] = 1;
    for(int i = 1; i < icnt; ++i)
        SS[i] = add(SS[i - 1], S[i]);
    for(int i = 1; i <= n; ++i) {
        int a =
            std::lower_bound(C, C + icnt, A[i] - 1) -
            C;
        int b =
            std::lower_bound(C, C + icnt, B[i]) - C;
        for(int j = b; j > a; --j) {
            int delta = C[j] - C[j - 1];
            for(int k = std::min(delta, i); k >= 2;
                --k) {
                int addv = F[j][k - 1] *
                    asInt64(delta - k + 1) % mod *
                    inv[k] % mod;
                F[j][k] = add(F[j][k], addv);
                S[j] = add(S[j], addv);
            }
            int addv =
                SS[j - 1] * asInt64(delta) % mod;
            F[j][1] = add(F[j][1], addv);
            S[j] = add(S[j], addv);
        }
        SS[0] = 1;
        for(int j = 1; j < icnt; ++j)
            SS[j] = add(SS[j - 1], S[j]);
    }
    int res = SS[icnt - 1] - 1;
    printf("%d\n", res < 0 ? res + mod : res);
    return 0;
}
