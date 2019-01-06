#include <cmath>
#include <complex>
#include <cstdio>
typedef double FT;
typedef std::complex<FT> Complex;
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
const int size = 1 << 17;
int tot, rev[size];
Complex root[size], invR[size];
void init(int n, int off) {
    tot = n;
    FT base = 2.0 * M_PI / n;
    for(int i = 0; i < n; ++i) {
        root[i] =
            Complex(cos(i * base), sin(i * base));
        invR[i] = std::conj(root[i]);
    }
    rev[0] = 0;
    for(int i = 1; i < n; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << off;
}
void FFT(int n, Complex* A, const Complex* w) {
    for(int i = 0; i < n; ++i)
        if(i < rev[i])
            std::swap(A[i], A[rev[i]]);
    for(int i = 2; i <= n; i <<= 1) {
        int m = i >> 1, fac = tot / i;
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                Complex &x = A[j + k],
                        &y = A[j + k + m];
                Complex t = w[k * fac] * y;
                y = x - t;
                x += t;
            }
    }
}
typedef long long Int64;
Complex A[size], B[size];
int main() {
    int n = read(), m = read();
    Int64 sum1 = 0, sum2 = 0;
    for(int i = 0; i < n; ++i) {
        int x = read();
        sum1 += x * x;
        sum2 += x;
        A[i].real(x);
    }
    for(int i = n - 1; i >= 0; --i) {
        int x = read();
        sum1 += x * x;
        sum2 -= x;
        A[i].imag(x);
    }
    int p = 1, off = -1;
    while(p < (n << 1))
        p <<= 1, ++off;
    init(p, off);
    FFT(p, A, root);
    B[0] = A[0].real() * A[0].imag();
    for(int i = 1; i < p; ++i) {
        FT x1 = A[i].real(), y1 = A[i].imag();
        FT x2 = A[p - i].real(), y2 = A[p - i].imag();
        Complex a(x1 + x2, y1 - y2),
            b(y1 + y2, x2 - x1);
        B[i] = 0.25 * a * b;
    }
    FFT(p, B, invR);
    FT maxv = 0.0;
    for(int i = 0; i < n; ++i) {
        FT cv = B[i].real() + B[i + n].real();
        if(cv > maxv)
            maxv = cv;
    }
    Int64 c = round(-static_cast<FT>(sum2) / n);
    printf("%lld\n", sum1 -
               2 * static_cast<Int64>(maxv / p + 0.5) +
               (2 * sum2 + n * c) * c);
    return 0;
}
