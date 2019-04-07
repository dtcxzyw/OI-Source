#include <algorithm>
#include <cstdio>
typedef unsigned long long Int64;
Int64 add(Int64 a, Int64 b, Int64 mod) {
    a += b;
    return a >= mod ? a - mod : a;
}
Int64 mulm(Int64 a, Int64 b, Int64 mod) {
    Int64 res = 0;
    while(b) {
        if(b & 1)
            res = add(res, a, mod);
        b >>= 1, a = add(a, a, mod);
    }
    return res;
}
Int64 powm(Int64 a, Int64 k, Int64 mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = mulm(res, a, mod);
        k >>= 1, a = mulm(a, a, mod);
    }
    return res;
}
int main() {
    freopen("data/5.ans", "r", stdin);
    Int64 res = 0;
    for(int i = 1; i <= 10000; ++i) {
        Int64 x;
        scanf("%llu", &x);
        res = std::max(res, x);
    }
    for(Int64 i = res + 1;; ++i) {
        if(powm(19, 278117030, i) ==
           4780942455857497844) {
            printf("%llu\n", i);
            break;
        }
        if((i & 0xfffff) == 0)
            printf("%llu\n", i);
    }
    return 0;
}
