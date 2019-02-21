#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <vector>
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
const int size = 1 << 19, maxn = (1 << 18) + 5;
int tot;
Complex root[size], invR[size];
void init(int n) {
    tot = n;
    FT base = 2.0 * M_PI / n;
    for(int i = 0; i < n; ++i) {
        root[i] =
            Complex(cos(i * base), sin(i * base));
        invR[i] = std::conj(root[i]);
    }
}
void FFT(int n, Complex* A, const Complex* w) {
    for(int i = 0, j = 0; i < n; ++i) {
        if(i < j)
            std::swap(A[i], A[j]);
        for(int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
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
Complex C[size], D[size], E[size], F[size], G[size];
typedef std::vector<int> Poly;
typedef long long Int64;
#define asInt64 static_cast<Int64>
int mod, k;
void mul(int p, int n, Poly& A, const Poly& B) {
    for(int i = 0; i < n; ++i)
        C[i] = Complex(A[i] / k, A[i] % k);
    for(int i = 0; i < n; ++i)
        D[i] = Complex(B[i] / k, B[i] % k);
    memset(C + n, 0, sizeof(Complex) * (p - n));
    memset(D + n, 0, sizeof(Complex) * (p - n));
    FFT(p, C, root);
    FFT(p, D, root);
    E[0] = 4.0 * C[0].real() * D[0].real();
    F[0] = 4.0 * (C[0].real() * D[0].imag() +
                  C[0].imag() * D[0].real());
    G[0] = 4.0 * C[0].imag() * D[0].imag();
    for(int i = 1; i < p; ++i) {
        FT x1 = C[i].real(), y1 = C[i].imag();
        FT x2 = C[p - i].real(), y2 = C[p - i].imag();
        FT x3 = D[i].real(), y3 = D[i].imag();
        FT x4 = D[p - i].real(), y4 = D[p - i].imag();
        Complex a(x1 + x2, y1 - y2);
        Complex b(y1 + y2, x2 - x1);
        Complex c(x3 + x4, y3 - y4);
        Complex d(y3 + y4, x4 - x3);
        E[i] = a * c;
        F[i] = a * d + b * c;
        G[i] = b * d;
    }
    FFT(p, E, invR);
    FFT(p, F, invR);
    FFT(p, G, invR);
    FT fac = 0.25 / p;
    for(int i = 0; i < n; ++i) {
        Int64 a = round(E[i].real() * fac);
        Int64 b = round(F[i].real() * fac);
        Int64 c = round(G[i].real() * fac);
        A[i] = ((a * k + b) % mod * k + c) % mod;
    }
}
void copy(Poly& dst, const Poly& src, int n) {
    memcpy(dst.data(), src.data(), sizeof(int) * n);
}
int getSize(int x) {
    x <<= 1;
    int p = 1;
    while(p < x)
        p <<= 1;
    return p;
}
void inv(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = 1;
    else {
        int h = (n + 1) >> 1;
        inv(h, sf, g);
        int p = getSize(n);
        Poly tg(n);
        copy(tg, g, h);

        mul(p, n, tg, sf);

        for(int i = 0; i < n; ++i)
            tg[i] = -tg[i];
        tg[0] = (2 + tg[0]) % mod;

        mul(p, n, g, tg);
    }
}
int lut[maxn];
void getLn(int n, Poly& A, Poly& B) {
    inv(n, A, B);
    for(int i = 1; i < n; ++i)
        A[i - 1] = asInt64(i) * A[i] % mod;
    A[n - 1] = 0;
    mul(getSize(n), n, B, A);
    for(int i = n - 1; i >= 1; --i)
        B[i] = asInt64(lut[i]) * B[i - 1] % mod;
    B[0] = 0;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
bool flag[maxn];
int main() {
    int n = read() + 1;
    mod = read();
    int p = getSize(n);
    k = ceil(sqrt(mod));
    Poly A(n), B(n);
    A[0] = 1;
    for(int i = 1; i < n; ++i)
        A[i] = read();
    init(p);
    lut[1] = 1;
    for(int i = 2; i < n; ++i)
        lut[i] = asInt64(mod - mod / i) *
            lut[mod % i] % mod;
    getLn(n, A, B);
    int cnt = 0;
    for(int i = 1; i < n; ++i)
        if(B[i]) {
            flag[i] = true, ++cnt;
            for(int j = i, c = 1; j < n; j += i, ++c)
                B[j] = sub(B[j], lut[c]);
        }
    printf("%d\n", cnt);
    for(int i = 1; i < n; ++i)
        if(flag[i])
            printf("%d ", i);
    return 0;
}
