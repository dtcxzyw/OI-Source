#include <cstdio>
typedef long long Int64;
const Int64 mod = 1e10;
Int64 add(Int64 a, Int64 b) {
    a += b;
    return a < mod ? a : a - mod;
}
Int64 mulm(Int64 a, Int64 k) {
    Int64 res = 0;
    while(k) {
        if(k & 1)
            res = add(res, a);
        k >>= 1, a = add(a, a);
    }
    return res;
}
Int64 powm(Int64 a, Int64 k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = mulm(res, a);
        k >>= 1, a = mulm(a, a);
    }
    return res;
}
int main() {
    int n;
    scanf("%d", &n);
    Int64 res = 0;
    for(int i = 1; i <= n; ++i)
        res = add(res, powm(i, i));
    printf("%lld\n", res);
    return 0;
}
