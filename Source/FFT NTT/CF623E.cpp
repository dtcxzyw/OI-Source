#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
const int size = 1 << 16, mod = 1000000007,
          mask = (1 << 15) - 1;
typedef double FT;
typedef std::complex<double> Complex;
Complex root[size], invR[size];
int tot;
void init(int n) {
    tot = n;
    FT fac = 2.0 * acos(-1.0) / n;
    for(int i = 0; i < n; ++i) {
        root[i] = Complex(cos(i * fac), sin(i * fac));
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
                        &y = A[j + m + k];
                Complex t = w[k * fac] * y;
                y = x - t;
                x += t;
            }
    }
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
Complex A[size], B[size], C[size], D[size], E[size];
int p;
void mul(int n, int* X, int* Y) {
    memset(A, 0, sizeof(Complex) * p);
    for(int i = 0; i <= n; ++i)
        A[i] = Complex(X[i] >> 15, X[i] & mask);
    FFT(p, A, root);
    memset(B, 0, sizeof(Complex) * p);
    for(int i = 0; i <= n; ++i)
        B[i] = Complex(Y[i] >> 15, Y[i] & mask);
    FFT(p, B, root);
    C[0] = 4.0 * A[0].real() * B[0].real();
    D[0] = 4.0 * (A[0].real() * B[0].imag() +
                  A[0].imag() * B[0].real());
    E[0] = 4.0 * (A[0].imag() * B[0].imag());
    for(int i = 1; i < p; ++i) {
        FT x1 = A[i].real(), y1 = A[i].imag();
        FT x2 = A[p - i].real(), y2 = A[p - i].imag();
        Complex a(x1 + x2, y1 - y2);
        Complex b(y1 + y2, x2 - x1);
        FT x3 = B[i].real(), y3 = B[i].imag();
        FT x4 = B[p - i].real(), y4 = B[p - i].imag();
        Complex c(x3 + x4, y3 - y4);
        Complex d(y3 + y4, x4 - x3);
        C[i] = a * c;
        D[i] = b * c + a * d;
        E[i] = b * d;
    }
    FFT(p, C, invR);
    FFT(p, D, invR);
    FFT(p, E, invR);
    FT div = 4.0 * p;
    for(int i = 0; i <= n; ++i) {
        Int64 a = round(C[i].real() / div);
        a %= mod;
        Int64 b = round(D[i].real() / div);
        b %= mod;
        Int64 c = round(E[i].real() / div);
        c %= mod;
        X[i] = ((a << 30) + (b << 15) + c) % mod;
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
int X[size], Y[size], fac[size], invFac[size];
void solve(int n, int k) {
    if(n == 1) {
        X[0] = 0;
        for(int i = 1; i <= k; ++i)
            X[i] = invFac[i];
    } else {
        int h = n >> 1;
        solve(h, k);
        Int64 cur = 1, fac = powm(2, h);
        for(int i = 0; i <= k;
            ++i, cur = (cur * fac) % mod)
            Y[i] = X[i] * cur % mod;
        mul(k, X, Y);
        if(n & 1) {
            Int64 cur = 1;
            for(int i = 0; i <= k;
                ++i, cur = (cur * 2) % mod)
                X[i] = X[i] * cur % mod;
            Y[0] = 0;
            for(int i = 1; i <= k; ++i)
                Y[i] = invFac[i];
            mul(k, X, Y);
        }
    }
}
int main() {
    Int64 n;
    int k;
    scanf("%lld%d", &n, &k);
    if(n > k) {
        puts("0");
        return 0;
    }
    p = 1;
    while(p <= (k * 2))
        p <<= 1;
    init(p);
    fac[0] = 1;
    for(int i = 1; i <= k; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    invFac[0] = invFac[1] = 1;
    for(int i = 2; i <= k; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 1; i <= k; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    solve(n, k);
    Int64 res = 0;
    for(int i = 0; i <= k; ++i)
        res = (res + X[i] * asInt64(invFac[k - i])) %
            mod;
    res = res * fac[k] % mod;
    printf("%lld\n", res);
    return 0;
}
