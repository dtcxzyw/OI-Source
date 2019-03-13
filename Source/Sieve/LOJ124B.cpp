#include <cstdio>
const int size = 10000007, mod = 1000000007;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int p[670005], idk[size];
int main() {
    int n, k, pcnt = 0;
    scanf("%d%d", &n, &k);
    idk[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!idk[i]) {
            p[++pcnt] = i;
            idk[i] = powm(i, k);
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            idk[val] =
                asInt64(idk[i]) * idk[p[j]] % mod;
            if(i % p[j] == 0)
                break;
        }
    }
    for(int i = 1; i <= n; ++i)
        idk[i] = add(idk[i - 1], idk[i]);
    Int64 sum = 0;
    for(int i = 1; i <= n;) {
        int div = n / i, j = n / div;
        sum = (sum +
               div * asInt64(idk[j] - idk[i - 1])) %
            mod;
        i = j + 1;
    }
    if(sum < 0)
        sum += mod;
    printf("%lld\n", sum);
    return 0;
}
