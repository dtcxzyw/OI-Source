#include <cstdio>
int phi(int n) {
    int res = n;
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0) {
            do
                n /= i;
            while(n % i == 0);
            res = res / i * (i - 1);
        }
    if(n != 1)
        res = res / n * (n - 1);
    return res;
}
typedef long long Int64;
Int64 powm(Int64 a, int k, int mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int foo(int t) {
    if(t == 1)
        return 0;
    int x = phi(t);
    return powm(2, foo(x) + x, t);
}
int main() {
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; ++i) {
        int x;
        scanf("%d", &x);
        printf("%d\n", foo(x));
    }
    return 0;
}
