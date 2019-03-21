#include <cstdio>
typedef long long Int64;
Int64 query(int x) {
    Int64 res = 0;
    for(int i = 2; i * i <= x; ++i) {
        bool flag = false;
        for(int j = 2; j * j <= i; ++j)
            if(i % j == 0) {
                flag = true;
                break;
            }
        if(flag)
            continue;
        int base = i * i, end = x / base;
        for(int j = 1; j <= end; ++j)
            res += end / j;
    }
    return res;
}
int main() {
    int L, R;
    scanf("%d%d", &L, &R);
    printf("%lld\n", query(R) - query(L - 1));
    return 0;
}
