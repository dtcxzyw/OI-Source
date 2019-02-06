#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
typedef double FT;
#define asFT static_cast<FT>
typedef std::complex<FT> Complex;
const int size = 1 << 20;
Complex root[size], invR[size];
int tot;
void init(int n) {
    tot = n;
    FT base = 2.0 * acos(-1.0) / n;
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
                Complex t = y * w[k * fac];
                y = x - t;
                x += t;
            }
    }
}
const int maxn = 300005;
char S[maxn], T[maxn];
Complex A1[size], B1[size], A2[size], B2[size],
    A3[size], B3[size], C[size];
int pos[maxn];
int main() {
    int lenT, lenS;
    scanf("%d%d%s%s", &lenT, &lenS, T + 1, S + 1);
    std::reverse(T + 1, T + lenT + 1);
    for(int i = 1; i <= lenS; ++i)
        if(S[i] == '*')
            S[i] = 0;
    for(int i = 1; i <= lenT; ++i)
        if(T[i] == '*')
            T[i] = 0;
    int p = 1;
    while(p <= (lenS + lenT))
        p <<= 1;
    init(p);
    for(int i = 1; i <= lenS; ++i)
        A1[i] = asFT(S[i]) * S[i] * S[i];
    for(int i = 1; i <= lenT; ++i)
        B1[i] = T[i];
    FFT(p, A1, root);
    FFT(p, B1, root);
    for(int i = 1; i <= lenS; ++i)
        A2[i] = asFT(S[i]) * S[i];
    for(int i = 1; i <= lenT; ++i)
        B2[i] = asFT(T[i]) * T[i];
    FFT(p, A2, root);
    FFT(p, B2, root);
    for(int i = 1; i <= lenS; ++i)
        A3[i] = S[i];
    for(int i = 1; i <= lenT; ++i)
        B3[i] = asFT(T[i]) * T[i] * T[i];
    FFT(p, A3, root);
    FFT(p, B3, root);
    for(int i = 0; i < p; ++i)
        C[i] = A1[i] * B1[i] - 2.0 * A2[i] * B2[i] +
            A3[i] * B3[i];
    FFT(p, C, invR);
    int end = lenS - lenT + 1, pcnt = 0;
    FT reps = 0.5 * p;
    for(int i = 1; i <= end; ++i) {
        if(fabs(C[i + lenT]) < reps)
            pos[++pcnt] = i;
    }
    printf("%d\n", pcnt);
    for(int i = 1; i <= pcnt; ++i)
        printf("%d ", pos[i]);
    return 0;
}
