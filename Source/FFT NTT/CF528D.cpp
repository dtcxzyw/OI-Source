#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
typedef double FT;
typedef std::complex<FT> Complex;
const int maxn = 200005, size = 1 << 19;
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
Complex A[size], B[size];
char S[maxn], T[maxn];
int cnt[maxn], lenS, lenT, k, p;
void solve(char ch) {
    memset(A, 0, sizeof(Complex) * p);
    memset(B, 0, sizeof(Complex) * p);
    for(int i = 1, l = 0, r = 0, cur = 0; i <= lenS;
        ++i) {
        while(r < lenS && r < i + k)
            cur += (S[++r] == ch);
        while(l < i - k)
            cur -= (S[l++] == ch);
        A[i] = (cur ? 1.0 : 0.0);
    }
    FFT(p, A, root);
    for(int i = 1; i <= lenT; ++i)
        B[lenT - i + 1] = (T[i] == ch);
    FFT(p, B, root);
    for(int i = 0; i < p; ++i)
        A[i] *= B[i];
    FFT(p, A, invR);
    for(int i = 1; i <= lenS; ++i)
        cnt[i] += round(A[i + lenT].real() / p);
}
int main() {
    scanf("%d%d%d%s%s", &lenS, &lenT, &k, S + 1,
          T + 1);
    int end = lenS + lenT + 1;
    p = 1;
    while(p < end)
        p <<= 1;
    init(p);
    solve('A');
    solve('G');
    solve('C');
    solve('T');
    int res = 0;
    for(int i = 1; i <= lenS; ++i) {
        if(cnt[i] >= lenT)
            ++res;
    }
    printf("%d\n", res);
    return 0;
}
