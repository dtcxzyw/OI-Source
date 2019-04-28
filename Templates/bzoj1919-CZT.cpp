#include <complex>
#include <cstdio>
namespace IO {
    char in[1 << 24];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    int getc() {
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
typedef double FT;
typedef std::complex<FT> Complex;
const int size = 500005, dsiz = 1 << 21;
int n, mod;
void FFT(int* A) {}
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
int main() {
    IO::init();
    n = read();
    mod = n + 1;
    int k = read();

    int p = 1;
    while(p < n * 2)
        p <<= 1;
    init(p);

    Poly A(n);
    for(int i = 0; i < n; ++i)
        A[i] = read();
    FFT(A);

    Poly B(n);
    for(int i = 0; i < n; ++i)
        B[i] = read();
    FFT(B);

    Poly C(n);
    for(int i = 0; i < n; ++i)
        C[i] = A[i] * powm(B[i], k) % mod;
    FFT(C);

    Int64 div = n;
    for(int i = 0; i < n; ++i) {
        write(C[i] * div % mod);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
