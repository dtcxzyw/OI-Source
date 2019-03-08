#include <cstdio>
namespace IO {
    const int size = 1 << 26;
    char in[size], *S = in;
    void init() {
        setvbuf(stdin, 0, _IONBF, 0);
        setvbuf(stdout, 0, _IONBF, 0);
        fread(in, 1, size, stdin);
    }
    char getc() {
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
const int size = 5000005, mod = 1000000007,
          fac = 998244353;
typedef long long Int64;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
Int64 A[size], B[size];
int main() {
    IO::init();
    int n = read();
    B[0] = 1;
    Int64 cur = 1;
    for(int i = 1; i <= n; ++i) {
        Int64 val = read();
        A[i] = val;
        cur = cur * val % mod;
        B[i] = cur;
    }
    cur = powm(cur, mod - 2);
    Int64 invFac = powm(fac, mod - 2);
    Int64 ans = 0;
    for(int i = n; i >= 1; --i) {
        ans = (ans * invFac + B[i - 1] * cur) % mod;
        cur = cur * A[i] % mod;
    }
    printf("%lld\n", ans * powm(fac, n - 1) % mod);
    return 0;
}
