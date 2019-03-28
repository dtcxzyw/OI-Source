#include <cmath>
#include <cstdio>
typedef unsigned long long Int64;
namespace Mker {
    Int64 SA, SB, SC;
    void init() {
        scanf("%llu%llu%llu", &SA, &SB, &SC);
    }
    Int64 rand() {
        SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
        Int64 t = SA;
        SA = SB, SB = SC, SC ^= t ^ SA;
        return SC;
    }
}
const Int64 mod = 1000000007, phi = mod - 1,
            x1 = 94153035, k1 = 233230706,
            x2 = 905847205, k2 = 766769301;
const int size = 32768 + 7, off = 15, mask = 32767;
Int64 A[size], B[size], C[size], D[size];
int main() {
    int t;
    scanf("%d", &t);
    Mker::init();

    A[0] = C[0] = 1;
    B[0] = k1, D[0] = k2;
    for(int i = 1; i <= mask; ++i)
        A[i] = A[i - 1] * x1 % mod;
    Int64 px1 = A[mask] * x1 % mod;
    for(int i = 1; i <= mask; ++i)
        B[i] = B[i - 1] * px1 % mod;
    for(int i = 1; i <= mask; ++i)
        C[i] = C[i - 1] * x2 % mod;
    Int64 px2 = C[mask] * x2 % mod;
    for(int i = 1; i <= mask; ++i)
        D[i] = D[i - 1] * px2 % mod;

    int res = 0;
    for(int i = 0; i < t; ++i) {
        int n = Mker::rand() % phi;
        res ^= (A[n & mask] * B[n >> off] +
                C[n & mask] * D[n >> off]) %
            mod;
    }
    printf("%d\n", res);
    return 0;
}
