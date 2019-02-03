#include <cstdio>
int A[10005];
int main() {
    int res = 0;
    for(int i = 1; i < 10000; ++i) {
        for(int j = 1; j < i; ++j)
            if(i % j == 0)
                A[i] += j;
        if(A[i] < i && A[A[i]] == i)
            res += A[i] + i;
    }
    printf("%d\n", res);
    return 0;
}
