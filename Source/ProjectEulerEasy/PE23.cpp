#include <cstdio>
int A[30000];
bool B[30000];
int main() {
    int acnt = 0;
    for(int i = 1; i <= 28123; ++i) {
        int sum = 0;
        for(int j = 1; j < i; ++j)
            if(i % j == 0)
                sum += j;
        if(sum > i) {
            A[++acnt] = i;
            B[i] = true;
        }
    }
    int sum = 0;
    for(int i = 1; i <= 28123; ++i) {
        bool flag = false;
        for(int j = 1; j <= acnt && i > A[j]; ++j)
            if(B[i - A[j]]) {
                flag = true;
                break;
            }
        if(!flag)
            sum += i;
    }
    printf("%d\n", sum);
    return 0;
}
