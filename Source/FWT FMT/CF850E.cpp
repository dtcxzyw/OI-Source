#include <cstdio>
const int size = 1 << 20, mod = 1000000007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
const Int64 inv2 = (mod + 1) / 2;
int A[size], B[size];
int main() {
    int n;
    scanf("%d", &n);
    int siz = 1 << n;
    for(int i = 0; i < siz; ++i) {
        char c;
        do
            c = getchar();
        while(c < '0' || c > '1');
        A[i] = (c == '1');
    }
    for(int i = 2; i <= siz; i <<= 1) {
        int m = i >> 1;
        for(int j = 0; j < siz; j += i)
            for(int k = 0; k < m; ++k) {
                int x = A[j + k], y = A[j + m + k];
                A[j + k] = add(x, y);
                A[j + m + k] = sub(x, y);
            }
    }
    for(int i = 0; i < siz; ++i)
        A[i] = asInt64(A[i]) * A[i] % mod;
    for(int i = 2; i <= siz; i <<= 1) {
        int m = i >> 1;
        for(int j = 0; j < siz; j += i)
            for(int k = 0; k < m; ++k) {
                int x = A[j + k], y = A[j + m + k];
                A[j + k] = add(x, y) * inv2 % mod;
                A[j + m + k] = sub(x, y) * inv2 % mod;
            }
    }
    B[0] = 1;
    for(int i = 1; i < siz; ++i) {
        B[i] = B[i >> 1] << (i & 1);
        if(B[i] >= mod)
            B[i] -= mod;
    }
    int mask = siz - 1;
    Int64 res = 0;
    for(int i = 0; i < siz; ++i)
        res =
            (res + asInt64(A[i]) * B[mask ^ i]) % mod;
    printf("%lld\n", res * 3 % mod);
    return 0;
}
