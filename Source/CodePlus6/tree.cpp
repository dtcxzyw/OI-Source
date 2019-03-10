#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 100005, mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, Int64 k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int A[size];
int main() {
    int n = read();
    int q = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int equ = A[1];
    for(int i = 2; i <= n; ++i)
        if(equ != A[i]) {
            equ = -1;
            break;
        }
    if(equ == -1) {
        for(int i = 1; i <= q; ++i) {
            int l = read();
            int r = read();
            Int64 res = 1;
            for(int j = l; j < r; ++j)
                for(int k = j + 1; k <= r; ++k)
                    res = res * gcd(A[j], A[k]) % mod;
            printf("%lld\n", res);
        }
    } else {
        for(int i = 1; i <= q; ++i) {
            int l = read();
            int r = read();
            int siz = r - l + 1;
            Int64 res = powm(equ, asInt64(siz) *
                                 (siz - 1) / 2);
            printf("%lld\n", res);
        }
    }
    return 0;
}
