#include <cstdio>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int mod = 998244353, size = 1 << 20;
const Int64 inv2 = (mod + 1) / 2;
Int64 powm(Int64 a, Int64 k) {
    Int64 res = 1;
    while (k) {
        if (k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
void FWT(int n, int *A) {
    for (int i = 2; i <= n; i <<= 1) {
        int m = i >> 1;
        for (int j = 0; j < n; j += i)
            for (int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + m + k], t = y;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
void IFWT(int n, int *A) {
    for (int i = 2; i <= n; i <<= 1) {
        int m = i >> 1;
        for (int j = 0; j < n; j += i)
            for (int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + m + k], t = y;
                y = sub(x, t) * inv2 % mod;
                x = add(x, t) * inv2 % mod;
            }
    }
}
int A[size], B[size];
int sg(int x) {
    return x - (1 << (31 - __builtin_clz(x)));
}
int main() {
    Int64 k;
    int m;
    scanf("%lld%d", &k, &m);
    int sum = powm(m, k);
    for (int i = 1; i <= m; ++i) {
        int val = sg(i);
        ++A[val];
    }
    int p = 1 << (31 - __builtin_clz(m));
    FWT(p, A);
    B[0] = 1;
    FWT(p, B);
    while (k) {
        if (k & 1) {
            for (int i = 0; i < p; ++i)
                B[i] = asInt64(B[i]) * A[i] % mod;
        }
        k >>= 1;
        if (k) {
            for (int i = 0; i < p; ++i)
                A[i] = asInt64(A[i]) * A[i] % mod;
        }
    }
    IFWT(p, B);
    printf("%d\n", sub(sum, B[0]));
    return 0;
}
