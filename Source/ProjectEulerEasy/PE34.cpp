#include <cstdio>
int main() {
    int A[10];
    A[0] = 1;
    for(int i = 1; i < 10; ++i)
        A[i] = A[i - 1] * i;
    int n;
    scanf("%d", &n);
    long long res = 0;
    for(int i = 10; i <= n; ++i) {
        int ci = i, s = 0;
        while(ci) {
            s += A[ci % 10];
            ci /= 10;
        }
        if(s == i) {
            res += i;
            printf("%d\n", i);
        }
        if((i & 0xfffff) == 0)
            printf("cur %d\n", i);
    }
    printf("%lld\n", res);
    return 0;
}
