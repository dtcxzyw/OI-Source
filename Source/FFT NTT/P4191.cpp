#include <cstdio>
#include <vector>
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
typedef long long Int64;
typedef std::vector<int> Poly;
const int size = 500005;
int pw[size], n, mod;
const int P[4] = { 2, 3, 5, 7 };
void FFT(Poly& A);
void FFTImpl(Poly& A, int p) {
    Poly C[7];
    int csiz = A.size() / p;
    for(int i = 0; i < p; ++i) {
        C[i].resize(csiz);
        for(int j = i, k = 0; j < A.size();
            j += p, ++k)
            C[i][k] = A[j];
        FFT(C[i]);
    }
    int off = n / A.size();
    for(int i = 0; i < p; ++i) {
        int base = i * csiz;
        for(int j = 0; j < csiz; ++j) {
            Int64 res = 0, fac = 1, dst = base + j,
                  mul = pw[off * dst];
            for(int k = 0; k < p; ++k) {
                res = (res + fac * C[k][j]) % mod;
                fac = fac * mul % mod;
            }
            A[dst] = res;
        }
    }
}
void FFT(Poly& A) {
    if(A.size() != 1) {
        for(int i = 0; i < 4; ++i)
            if(A.size() % P[i] == 0)
                return FFTImpl(A, P[i]);
    }
}
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

    Int64 g = 0;
    for(int i = 2; i <= n; ++i) {
        bool flag = true;
        for(int j = 0; j < 4; ++j)
            if(n % P[j] == 0 &&
               powm(i, n / P[j]) == 1) {
                flag = false;
                break;
            }
        if(flag) {
            g = i;
            break;
        }
    }
    pw[0] = 1;
    for(int i = 1; i < n; ++i)
        pw[i] = pw[i - 1] * g % mod;

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
    Int64 ig = powm(g, mod - 2);
    for(int i = 1; i < n; ++i)
        pw[i] = pw[i - 1] * ig % mod;
    FFT(C);

    Int64 div = n;
    for(int i = 0; i < n; ++i) {
        write(C[i] * div % mod);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
