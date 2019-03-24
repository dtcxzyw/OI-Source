#include <cstdio>
const int size = 100005;
typedef long long Int64;
Int64 L[size], R[size];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lld%lld", &L[i], &R[i]);
    Int64 res = 0;
    for(int i = 60; i >= 0; --i) {
        Int64 cl = (1LL << i);
        bool flag = true;
        for(int j = 1; j <= n; ++j)
            if(R[j] < cl) {
                flag = false;
                break;
            }
        if(flag) {
            res |= cl;
            for(int j = 1; j <= n; ++j)
                L[j] -= cl, R[j] -= cl;
        } else {
            for(int j = 1; j <= n; ++j)
                if(L[j] < cl && R[j] >= cl)
                    R[j] = cl - 1;
                else if(L[j] >= cl)
                    L[j] -= cl, R[j] -= cl;
        }
    }
    printf("%lld\n", res);
    return 0;
}
