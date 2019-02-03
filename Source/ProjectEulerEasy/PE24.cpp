#include <algorithm>
#include <cstdio>
int A[10];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < 10; ++i)
        A[i] = i;
    for(int i = 1; i < n; ++i)
        std::next_permutation(A, A + 10);
    for(int i = 0; i < 10; ++i)
        printf("%d", A[i]);
    puts("");
    int fac[10];
    bool ch[10] = {};
    fac[0] = 1;
    for(int i = 1; i < 10; ++i)
        fac[i] = fac[i - 1] * i;
    --n;
    for(int i = 0; i < 10; ++i) {
        int val = n / fac[9 - i] + 1;
        n %= fac[9 - i];
        for(int j = 0; j < 10; ++j)
            if(!ch[j]) {
                if(--val == 0) {
                    ch[j] = true;
                    A[i] = j;
                    break;
                }
            }
    }
    for(int i = 0; i < 10; ++i)
        printf("%d", A[i]);
    puts("");
    return 0;
}
