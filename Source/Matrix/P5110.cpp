#include <cstdio>
namespace Mker {
    unsigned long long SA, SB, SC;
    void init() {
        scanf("%llu%llu%llu", &SA, &SB, &SC);
    }
    unsigned long long rand() {
        SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
        unsigned long long t = SA;
        SA = SB, SB = SC, SC ^= t ^ SA;
        return SC;
    }
}
typedef long long Int64;
const int mod = 1000000007, phi = mod - 1;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
const int x1 = 94153035, k1 = 233230706,
          x2 = 905847205, k2 = 766769301;
int main() {
    int t;
    scanf("%d", &t);
    Mker::init();
    int res = 0;
    for(int i = 0; i < t; ++i) {
        int n = Mker::rand() % phi;
        res ^= (k1 * powm(x1, n) + k2 * powm(x2, n)) %
            mod;
        if(i % 1000000 == 0)
            printf("%d\n", i);
    }
    printf("%d\n", res);
    return 0;
}
