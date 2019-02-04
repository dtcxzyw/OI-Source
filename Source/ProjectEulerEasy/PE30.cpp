#include <cstdio>
int A[10];
int main() {
    for(int i = 0; i < 10; ++i) {
        int x = 1;
        for(int j = 0; j < 5; ++j)
            x *= i;
        A[i] = x;
    }
    long long res = 0;
    for(int i = 10; i <= 300000; ++i) {
        int x = i, sum = 0;
        while(x) {
            sum += A[x % 10];
            x /= 10;
        }
        if(sum == i)
            res += i;
    }
    printf("%lld\n", res);
    return 0;
}
