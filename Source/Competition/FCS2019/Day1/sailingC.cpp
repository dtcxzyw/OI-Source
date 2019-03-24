#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
const int size = 1 << 20;
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
char buf[705 * 705];
int mcnt[705][705];
bool match[705][705], color[705][705];
Complex S[size], T[size];
int n, m, w, h;
void DFS(int x, int y) {
    match[x][y] = false;
    S[x * m + y] = 1.0;
    if(x + 1 + h - 1 <= n && match[x + 1][y])
        DFS(x + 1, y);
    if(x > 1 && match[x - 1][y])
        DFS(x - 1, y);
    if(y + 1 + w - 1 <= m && match[x][y + 1])
        DFS(x, y + 1);
    if(y > 1 && match[x][y - 1])
        DFS(x, y - 1);
}
int main() {
    scanf("%d%d", &n, &m);
    int ml = m + 1, mr = 0, mt = n + 1, mb = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", buf + i * m + 1);
        for(int j = 1; j <= m; ++j)
            if(buf[i * m + j] == 'o') {
                ml = std::min(ml, j);
                mr = std::max(mr, j);
                mt = std::min(mt, i);
                mb = std::max(mb, i);
            }
    }
    int begS = 1 * m + 1, endS = n * m + m;
    int lenS = endS - begS + 1;
    int begT = mt * m + ml, endT = mb * m + mr;
    int lenT = endT - begT + 1;
    int end = lenS + lenT + 1;
    w = mr - ml + 1, h = mb - mt + 1;
    int p = 1;
    while(p < end)
        p <<= 1;
    init(p);
    //#
    {
        memset(S, 0, sizeof(Complex) * p);
        memset(T, 0, sizeof(Complex) * p);
        for(int i = begS; i <= endS; ++i)
            S[i - begS + 1] = (buf[i] == '#');
        for(int i = begT; i <= endT; ++i)
            T[i - begT + 1] = (buf[i] != 'o');
        std::reverse(T + 1, T + lenT + 1);
        FFT(p, S, root);
        FFT(p, T, root);
        for(int i = 0; i < p; ++i)
            S[i] *= T[i];
        FFT(p, S, invR);
        for(int i = 1; i + h - 1 <= n; ++i)
            for(int j = 1; j + w - 1 <= m; ++j)
                mcnt[i][j] += round(
                    S[lenT + (i * m + j - begS + 1)]
                        .real() /
                    p);
    }
    // o
    {
        memset(S, 0, sizeof(Complex) * p);
        memset(T, 0, sizeof(Complex) * p);
        for(int i = begS; i <= endS; ++i)
            S[i - begS + 1] = (buf[i] != '#');
        for(int i = begT; i <= endT; ++i)
            T[i - begT + 1] = 1.0;
        std::reverse(T + 1, T + lenT + 1);
        FFT(p, S, root);
        FFT(p, T, root);
        for(int i = 0; i < p; ++i)
            S[i] *= T[i];
        FFT(p, S, invR);
        for(int i = 1; i + h - 1 <= n; ++i)
            for(int j = 1; j + w - 1 <= m; ++j)
                mcnt[i][j] += round(
                    S[lenT + (i * m + j - begS + 1)]
                        .real() /
                    p);
    }
    for(int i = 1; i + h - 1 <= n; ++i)
        for(int j = 1; j + w - 1 <= m; ++j)
            match[i][j] = (mcnt[i][j] >= lenT);
    memset(S, 0, sizeof(Complex) * p);
    memset(T, 0, sizeof(Complex) * p);
    DFS(mt, ml);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            if(buf[i * m + j] == 'o')
                T[i * m + j - begT] = 1.0;
    FFT(p, S, root);
    FFT(p, T, root);
    for(int i = 0; i < p; ++i)
        S[i] *= T[i];
    FFT(p, S, invR);
    int res = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            res += (S[i * m + j].real() / p >= 0.5);
    printf("%d\n", res);
    return 0;
}
