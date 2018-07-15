//P3803
#include <cmath>
#include <complex>
#include <cstdio>
int readBit() {
    int c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    return c - '0';
}
typedef double FT;
typedef std::complex<FT> Complex;
const int size = 1 << 21;
Complex root[size], invR[size];
int tot;
void init(int n) {
    tot = n;
    FT fac = 2.0 * acos(-1.0) / n;
    for (int i = 0; i < n; ++i) {
        root[i] = Complex(cos(fac * i), sin(fac * i));
        invR[i] = conj(root[i]);
    }
}
void FFT(int n, Complex *A, Complex *w) {
    for (int i = 0, j = 0; i < n; ++i) {
        if (i > j) std::swap(A[i], A[j]);
        int l = n >> 1;
        while ((j ^= l) < l) l >>= 1;
    }
    for (int i = 2; i <= n; i <<= 1) {
        int m = i >> 1, fac = tot / i;
        for (int j = 0; j < n; j += i)
            for (int k = 0; k < m; ++k) {
                Complex t = A[j + k + m] * w[k * fac];
                A[j + k + m] = A[j + k] - t;
                A[j + k] += t;
            }
    }
}
Complex A[size], B[size];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i)
        A[i].real(readBit());
    for (int i = 0; i <= m; ++i)
        A[i].imag(readBit());
    int end = n + m + 1, p = 1;
    while (p < end) p <<= 1;
    init(p);
    FFT(p, A, root);
    B[0] = A[0].real() * A[0].imag();
    for (int i = 1; i < p; ++i) {
        FT x1 = A[i].real(), y1 = A[i].imag();
        FT x2 = A[p - i].real(), y2 = A[p - i].imag();
        Complex a((x1 + x2) * 0.5, (y1 - y2) * 0.5);
        Complex b((y1 + y2) * 0.5, (x2 - x1) * 0.5);
        B[i] = a * b;
    }
    FFT(p, B, invR);
    for (int i = 0; i < end; ++i)
        printf("%d ", static_cast<int>(B[i].real() / p + 0.5));
    return 0;
}
