#include <bitset>
#include <cstdio>
typedef long long Int64;
std::bitset<250000005> A;
void build(int x) {
    x /= 4;
    for(int i = 2; i * i <= x; ++i) {
        int base = i * i, end = x / base;
        for(int j = 1; j <= end; ++j)
            A.set(base * j);
    }
}
Int64 query(int x) {
    Int64 res = 0;
    for(int i = 2; i * i <= x; ++i) {
        int base = i * i, end = x / base;
        for(int j = 1; j <= end; ++j) {
            if(!A.test(j))
                res += end / j;
        }
    }
    return res;
}
int main() {
    int L, R;
    scanf("%d%d", &L, &R);
    build(R);
    printf("%lld\n", query(R) - query(L - 1));
    return 0;
}
