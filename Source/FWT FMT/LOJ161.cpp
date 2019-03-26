#include <cstdio>
namespace IO {
    char in[1 << 25];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    int getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 24], *S = out;
    void putc(int ch) {
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
const int size = 1 << 20, mod = 1000000009;
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
Int64 fma(Int64 a, Int64 b, Int64 c) {
    return (a + b * c) % mod;
}
void FMT(int* A, int end) {
    for(int i = 1; i < end; i <<= 1)
        for(int j = i; j < end; j = (j + 1) | i)
            A[j] = add(A[j], A[j - i]);
}
void IFMT(int* A, int end) {
    for(int i = 1; i < end; i <<= 1)
        for(int j = i; j < end; j = (j + 1) | i)
            A[j] = sub(A[j], A[j - i]);
}
int A[21][size], B[21][size], C[21][size], bcnt[size];
int main() {
    IO::init();
    int n = read(), end = 1 << n;
    for(int i = 0; i < end; ++i)
        bcnt[i] = bcnt[i >> 1] + (i & 1);
    for(int i = 0; i < end; ++i)
        A[bcnt[i]][i] = read();
    for(int i = 0; i <= n; ++i)
        FMT(A[i], end);
    for(int i = 0; i < end; ++i)
        B[bcnt[i]][i] = read();
    for(int i = 0; i <= n; ++i)
        FMT(B[i], end);
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= i; ++j) {
            int *X = A[j], *Y = B[i - j], *Z = C[i];
            for(int k = 0; k < end; ++k)
                Z[k] = fma(Z[k], X[k], Y[k]);
        }
        IFMT(C[i], end);
    }
    for(int i = 0; i < end; ++i) {
        write(C[bcnt[i]][i]);
        IO::putc(' ');
    }
    IO::uninit();
    return 0;
}
