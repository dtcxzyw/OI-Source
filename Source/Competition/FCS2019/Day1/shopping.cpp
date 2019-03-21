#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <vector>
namespace IO {
    const int size = 1 << 23;
    char buf[size];
    char getc() {
        static char *S = 0, *T = 0;
        if(S == T)
            S = buf,
            T = S + fread(buf, 1, size, stdin);
        return S == T ? EOF : *S++;
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
const int mod = 1000000007;
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
typedef std::vector<int> Poly;
namespace Conv {
    const int size = 1 << 18;
    typedef double FT;
    typedef std::complex<FT> Complex;
    Complex root[size], invR[size];
    int tot;
    void init(int n) {
        tot = n;
        FT base = 2.0 * acos(-1.0) / n;
        for(int i = 0; i < n; ++i) {
            root[i] =
                Complex(cos(base * i), sin(base * i));
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
                    Complex t = y * w[k * fac];
                    y = x - t;
                    x += t;
                }
        }
    }
    const int mask = (1 << 16) - 1;
    Complex A[size], B[size], C[size], D[size],
        E[size];
    Poly mul(const Poly& X, const Poly& Y) {
        int nX = X.size(), nY = Y.size();
        int end = nX + nY - 1;
        int p = 1;
        while(p < end)
            p <<= 1;
        memset(A, 0, sizeof(Complex) * p);
        memset(B, 0, sizeof(Complex) * p);
        for(int i = 0; i < nX; ++i)
            A[i] = Complex(X[i] >> 16, X[i] & mask);
        for(int i = 0; i < nY; ++i)
            B[i] = Complex(Y[i] >> 16, Y[i] & mask);
        FFT(p, A, root);
        FFT(p, B, root);
        C[0] = 4.0 * A[0].real() * B[0].real();
        D[0] = 4.0 * (A[0].real() * B[0].imag() +
                      A[0].imag() * B[0].real());
        E[0] = 4.0 * A[0].imag() * B[0].imag();
        for(int i = 1; i < p; ++i) {
            FT x1 = A[i].real(), y1 = A[i].imag();
            FT x2 = A[p - i].real(),
               y2 = A[p - i].imag();
            FT x3 = B[i].real(), y3 = B[i].imag();
            FT x4 = B[p - i].real(),
               y4 = B[p - i].imag();
            Complex a(x1 + x2, y1 - y2);
            Complex b(y1 + y2, x2 - x1);
            Complex c(x3 + x4, y3 - y4);
            Complex d(y3 + y4, x4 - x3);
            C[i] = a * c;
            D[i] = a * d + b * c;
            E[i] = b * d;
        }
        FFT(p, C, invR);
        FFT(p, D, invR);
        FFT(p, E, invR);
        FT div = 4.0 * p;
        Poly Z(end);
        for(int i = 0; i < end; ++i) {
            Int64 a = round(C[i].real() / div);
            Int64 b = round(D[i].real() / div);
            Int64 c = round(E[i].real() / div);
            Int64 res = ((a % mod) << 32) +
                ((b % mod) << 16) + c;
            Z[i] = res % mod;
        }
        return Z;
    }
}
int A[305];
Poly solve(int l, int r) {
    if(l == r)
        return Poly(A[l] + 1, 1);
    else {
        int m = (l + r) >> 1;
        return Conv::mul(solve(l, m), solve(m + 1, r));
    }
}
const int size = 5000005;
int fac[2 * size], invFac[2 * size];
int main() {
    int n = read();
    int m = read();
    int k = read();
    int sum = 0;
    for(int i = 1; i <= m; ++i) {
        A[i] = read();
        sum += A[i];
    }
    int p = 1;
    while(p <= (sum * 2))
        p <<= 1;
    Conv::init(p);
    Poly B = solve(1, m);
    n -= m;
    int end = k + n - 1;
    fac[0] = 1;
    for(int i = 1; i <= end; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    invFac[0] = invFac[1] = 1;
    for(int i = 2; i <= end; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 1; i <= end; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    Int64 res = 0;
    if(n) {
        for(int i = 0; i <= sum && i <= k; ++i) {
            int c = end - i;
            res = (res +
                   asInt64(B[i]) * fac[c] % mod *
                       invFac[k - i]) %
                mod;
        }
        res = res * invFac[n - 1] % mod;
    } else if(sum >= k)
        res = B[k];
    if(res < 0)
        res += mod;
    printf("%lld\n", res);
    return 0;
}
