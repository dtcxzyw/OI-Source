#include <cstdio>
#include <cstring>
namespace IO {
    char in[1 << 23];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 23], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
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
void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 205, mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
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
int P[size][105], M[size];
void foo0() {
    int id = read();
    int u = read();
    int v = read();
    Int64 p = u * powm(v, mod - 2) % mod;
    for(int i = 0; i < M[id]; ++i) {
        int tr = p * P[id][i + 1] % mod;
        P[id][i] = add(P[id][i], tr);
        P[id][i + 1] = sub(P[id][i + 1], tr);
    }
}
int id[size], K[size], D[size], inv[size];
void foo1() {
    int k = read();
    for(int i = 1; i <= k; ++i)
        id[i] = read();
    K[0] = 1;
    memset(K + 1, 0, sizeof(int) * k);
    for(int i = 1; i <= k; ++i) {
        int u = id[i];
        Int64 np = P[u][0];
        if(np == 1)
            continue;
        Int64 p = sub(1, np);
        for(int j = i; j >= 1; --j)
            K[j] = (K[j] * np + K[j - 1] * p) % mod;
        K[0] = K[0] * np % mod;
    }
    for(int i = 1; i <= k; ++i) {
        int u = id[i];
        Int64 np = P[u][0];
        Int64 p = sub(1, np);
        if(p) {
            Int64 res = 0;
            if(p != 1) {
                Int64 ip = powm(p, mod - 2);
                memcpy(D, K, sizeof(int) * (k + 1));
                for(int j = k; j >= 1; --j) {
                    Int64 src = D[j] * ip % mod;
                    D[j - 1] =
                        (D[j - 1] - src * np) % mod;
                    res = (res + src * inv[j]) % mod;
                }
                if(res < 0)
                    res += mod;
            } else {
                for(int j = k; j >= 1; --j)
                    res = (res +
                           asInt64(K[j]) * inv[j]) %
                        mod;
            }
            write(res * p % mod);
        } else
            IO::putc('0');
        IO::putc(' ');
    }
    IO::putc('\n');
}
int main() {
    IO::init();
    inv[1] = 1;
    for(int i = 2; i <= 200; ++i)
        inv[i] = asInt64(mod - mod / i) *
            inv[mod % i] % mod;
    int n = read();
    for(int i = 1; i <= n; ++i) {
        M[i] = read();
        P[i][M[i]] = 1;
    }
    int q = read();
    for(int t = 1; t <= q; ++t) {
        int op = read();
        if(op == 0)
            foo0();
        else
            foo1();
    }
    for(int i = 1; i <= n; ++i) {
        Int64 res = 0;
        for(int j = 1; j <= M[i]; ++j)
            res = (res + asInt64(P[i][j]) * j) % mod;
        write(res);
        IO::putc(' ');
    }
    IO::putc('\n');
    IO::uninit();
    return 0;
}
