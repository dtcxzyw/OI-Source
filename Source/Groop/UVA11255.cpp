#include <cstdio>
#include <cstring>
typedef long long Int64;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
const int p[12] = { 2,  3,  5,  7,  11, 13,
                    17, 19, 23, 29, 31, 37 };
int fac[45][12], ccnt[12];
void init(int n) {
    for(int i = 1; i <= n; ++i) {
        int x = i;
        for(int j = 0; j < 12; ++j) {
            fac[i][j] = fac[i - 1][j];
            while(x % p[j] == 0) {
                x /= p[j];
                ++fac[i][j];
            }
        }
    }
}
void mul(int k, int op) {
    for(int i = 0; i < 12; ++i)
        ccnt[i] += fac[k][i] * op;
}
Int64 calc(int* A, int len, int tot) {
    memset(ccnt, 0, sizeof(ccnt));
    mul(tot / len, 1);
    for(int i = 0; i < 3; ++i) {
        int c = A[i] / len, d = A[i] % len;
        if(d)
            return 0;
        mul(c, -1);
    }
    Int64 res = 1;
    for(int i = 0; i < 12; ++i)
        for(int j = 0; j < ccnt[i]; ++j)
            res *= p[i];
    return res;
}
Int64 foo() {
    int A[3];
    scanf("%d%d%d", &A[0], &A[1], &A[2]);
    int n = A[0] + A[1] + A[2];
    Int64 sum = 0;
    for(int i = 0; i < n; ++i) {
        int len = n / gcd(n, i);
        sum += calc(A, len, n);
    }
    if(n & 1) {
        for(int i = 0; i < 3; ++i)
            if(A[i]) {
                --A[i];
                sum += n * calc(A, 2, n - 1);
                ++A[i];
            }
    } else {
        int k = n >> 1;
        sum += k * calc(A, 2, n);
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j) {
                --A[i], --A[j];
                if(A[i] >= 0 && A[j] >= 0)
                    sum += k * calc(A, 2, n - 2);
                ++A[i], ++A[j];
            }
    }
    return sum / (2 * n);
}
int main() {
    init(40);
    int n;
    scanf("%d", &n);
    while(n--)
        printf("%lld\n", foo());
    return 0;
}
