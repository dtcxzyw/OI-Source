#include <cstdio>
template <int base>
bool check(int x) {
    int b[25], icnt = 0;
    while(x) {
        b[icnt++] = x % base;
        x /= base;
    }
    --icnt;
    for(int i = 0; i < icnt - i; ++i)
        if(b[i] != b[icnt - i])
            return false;
    return true;
}
int main() {
    int n;
    scanf("%d", &n);
    long long res = 0;
    for(int i = 1; i < n; ++i)
        if(check<10>(i) && check<2>(i)) {
            printf("%d\n", i);
            res += i;
        }
    printf("%lld\n", res);
    return 0;
}
