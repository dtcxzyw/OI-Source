// ERROR
#include <cstdio>
const int size = 1000005;
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
Int64 powm(Int64 a, int k, int p) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % p;
        k >>= 1, a = a * a % p;
    }
    return res;
}
int calc(int n, int pc, int k, int mod) {
    Int64 res = 1;
    for(int i = 1; i <= n; ++i)
        res = res * (4 * i - 2) % pc;
    int end = n + 1;
    Int64 div = 1;
    for(int i = 2; i <= end; ++i)
        div = div * i % pc;
    res = res * powm(div, k, pc) % pc;
    int mul = mod / pc;
    return res * mul % mod * powm(mul % pc, k, pc) % mod;
}
int main() {
    int n, p;
    scanf("%d%d", &n, &p);
    int res = 0, x = p;
    for(int i = 2; i * i <= x; ++i)
        if(x % i == 0) {
            int old = x;
            do
                x /= i;
            while(x % i == 0);
            int pc = old / x;
            res = (res + calc(n, pc, pc / i * (i - 1) - 1, p)) % p;
        }
    if(x != 1)
        res = (res + calc(n, x, x - 2, p)) % p;
    printf("%d\n", res);
    return 0;
}
