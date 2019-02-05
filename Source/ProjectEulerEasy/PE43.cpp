#include <algorithm>
#include <cstdio>
int A[10];
const int p[10] = { 0, 2, 3, 5, 7, 11, 13, 17 };
int main() {
    for(int i = 0; i < 10; ++i)
        A[i] = i;
    long long res = 0;
    do {
        long long val = 0;
        for(int i = 1; i <= 7; ++i) {
            int sum = 0;
            for(int j = 0; j < 3; ++j)
                sum = sum * 10 + A[i + j];
            if(sum % p[i])
                goto err;
        }
        for(int i = 0; i < 10; ++i)
            val = val * 10 + A[i];
        res += val;
        printf("%lld\n", val);
    err : {}
    } while(std::next_permutation(A, A + 10));
    printf("%lld\n", res);
    return 0;
}
