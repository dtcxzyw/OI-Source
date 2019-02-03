#include <cstdio>
typedef long long Int64;
int main() {
    Int64 n;
    scanf("%lld", &n);
    Int64 res = 1;
    for(Int64 i = 2; i * i <= n; ++i) {
        if(n % i == 0) {
            res = i;
            do
                n /= i;
            while(n % i == 0);
        }
    }
    if(n)
        res = n;
    printf("%lld\n", res);
    return 0;
}
