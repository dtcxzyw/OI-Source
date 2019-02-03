#include <cstdio>
const int size = 100;
int A[size];
int main() {
    int n;
    scanf("%d", &n);
    A[0] = A[1] = 1;
    long long sum = 0;
    for(int i = 2;; ++i) {
        A[i] = A[i - 1] + A[i - 2];
        if(A[i] > n)
            break;
        if((A[i] & 1) == 0)
            sum += A[i];
    }
    printf("%lld\n", sum);
    return 0;
}
