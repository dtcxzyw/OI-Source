#include <cstdio>
typedef long long Int64;
Int64 T(Int64 n) {
    return n * (n + 1) / 2;
}
Int64 P(Int64 n) {
    return n * (3 * n - 1) / 2;
}
Int64 H(Int64 n) {
    return n * (2 * n - 1);
}
int main() {
    Int64 i = 1, j = 1, k = 1;
    while(true) {
        Int64 vi = T(i), vj = P(j), vk = H(k);
        if(vi == vj && vi == vk)
            printf("%lld %lld %lld %lld\n", i, j, k,
                   vi);
        if(vi <= vj && vi <= vk)
            ++i;
        else if(vj <= vi && vj <= vk)
            ++j;
        else
            ++k;
    }
    return 0;
}
