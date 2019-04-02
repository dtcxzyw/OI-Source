#include <algorithm>
#include <cstdio>
int bcnt(int x) {
    return __builtin_popcount(x);
}
const int maxa = 233333, maxn = 211985;
int A[20];
int main() {
    for(int i = 1; i <= maxa; ++i)
        ++A[bcnt(i)];
    int res = 0, rem = maxn;
    for(int i = 1; i < 20; ++i) {
        if(A[i] < rem) {
            rem -= A[i];
            res += A[i] << i;
        } else
            res += rem << i;
    }
    printf("%d\n", res);
    return 0;
}
