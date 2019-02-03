#include <cstdio>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int mod = 998244353;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int main() {
    Int64 inv4 = powm(4, mod - 2), phi = mod - 1;
    Int64 base = powm(3, phi / 4);
    Int64 root[4];
    root[0] = 1;
    for(int i = 1; i < 4; ++i)
        root[i] = root[i - 1] * base % mod;
    Int64 map[4][4];
    for(int i = 0; i < 4; ++i) {
        int inv = 4 - i;
        for(int j = 0; j < 4; ++j)
            map[i][j] = powm(root[j], inv);
    }
    int t = read();
    for(int i = 0; i < t; ++i) {
        Int64 n = read() % phi;
        Int64 s = read();
        Int64 res = 0;
        Int64 val[4];
        for(int j = 0; j < 4; ++j)
            val[j] = powm((s * root[j] + 1) % mod, n);
        for(int j = 0; j < 4; ++j) {
            Int64 sum = 0;
            for(int k = 0; k < 4; ++k)
                sum = (sum + map[j][k] * val[k]) % mod;
            res = (res + sum * read()) % mod;
        }
        printf("%lld\n", res * inv4 % mod);
    }
    return 0;
}
