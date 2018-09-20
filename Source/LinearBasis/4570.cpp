#include <algorithm>
#include <cstdio>
typedef long long Int64;
Int64 b[61] = {};
bool insert(Int64 x) {
    for(int i = 60; i >= 0; --i)
        if(x & (1LL << i)) {
            if(b[i])
                x ^= b[i];
            else {
                b[i] = x;
                return true;
            }
        }
    return false;
}
struct Info {
    Int64 k;
    int w;
    bool operator<(const Info& rhs) const {
        return w > rhs.w;
    }
} A[1005];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%lld%d", &A[i].k, &A[i].w);
    std::sort(A, A + n);
    int res = 0;
    for(int i = 0; i < n; ++i)
        if(insert(A[i].k))
            res += A[i].w;
    printf("%d\n", res);
    return 0;
}
