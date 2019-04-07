#include <cstdio>
int main() {
    unsigned int cur = 1;
    for(long long i = 0;; ++i, cur *= 19U) {
        if(cur == 1 && i) {
            printf("%lld\n", i);
            break;
        }
    }
    return 0;
}
