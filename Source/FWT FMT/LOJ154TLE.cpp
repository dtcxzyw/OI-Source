#include <cstdio>
#include <cstring>
#include <limits>
namespace IO {
    char in[1 << 21];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    int getc() {
        static char* S = in;
        return *S++;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 1 << 21, mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
void FWT(int* A, int end) {
    for(int i = 1; i <= end; i <<= 1) {
        int m = i >> 1;
        for(int j = 0; j < end; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k + m], &y = A[j + k];
                x = add(x, y);
            }
    }
}
void IFWT(int* A, int end) {
    for(int i = 1; i <= end; i <<= 1) {
        int m = i >> 1;
        for(int j = 0; j < end; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k + m], &y = A[j + k];
                x = sub(x, y);
            }
    }
}
typedef int(Arr)[22][size];
Arr A, B;
int bcnt[size], D[size];
void clear(Arr& S, int n) {
    int end = 1 << n;
    for(int k = 0; k <= n; ++k)
        memset(S[k], 0, sizeof(int) * end);
}
const Int64 lim = std::numeric_limits<Int64>::max() -
    asInt64(mod - 1) * (mod - 1);
Int64 C[size];
void conv(int* b, int n) {
    int end = 1 << n;
    clear(B, n);
    for(int i = 0; i < end; ++i)
        B[bcnt[i]][i] = b[i];
    for(int i = 0; i <= n; ++i)
        FWT(B[i], end);
    for(int i = 0; i <= n; ++i) {
        memset(C, 0, sizeof(Int64) * end);
        for(int j = 0; j <= i; ++j) {
            int *X = A[j], *Y = B[i - j];
            for(int k = 0; k < end; ++k) {
                C[k] += asInt64(X[k]) * Y[k];
                if(C[k] > lim)
                    C[k] %= mod;
            }
        }
        for(int k = 0; k < end; ++k)
            D[k] = C[k] % mod;
        IFWT(D, end);
        for(int j = 0; j < end; ++j)
            if(bcnt[j] == i)
                b[j] = D[j];
    }
}
int base[size], powv[size];
int main() {
    IO::init();
    int n = read();
    int m = read();
    int k = read();
    int end = 1 << n;
    for(int i = 0; i < end; ++i)
        bcnt[i] = bcnt[i >> 1] + (i & 1);
    for(int i = 1; i <= m; ++i)
        ++base[read()];
    Int64 res = base[end - 1];

    memcpy(powv, base, sizeof(int) * end);

    for(int i = 0; i < end; ++i)
        A[bcnt[i]][i] = base[i];
    for(int i = 0; i <= n; ++i)
        FWT(A[i], end);

    Int64 inv[50];
    inv[0] = inv[1] = 1;
    for(int i = 2; i <= k; ++i)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for(int i = 1; i <= k; ++i)
        inv[i] = inv[i - 1] * inv[i] % mod;
    for(int i = 2; i <= k; ++i) {
        conv(powv, n);
        res = (res + powv[end - 1] * inv[i]) % mod;
    }
    printf("%lld\n", res);
    return 0;
}
