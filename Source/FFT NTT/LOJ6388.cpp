#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <deque>
typedef float FT;
typedef std::complex<FT> Complex;
const int size = 1 << 23;
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
int rev[size];
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
Complex A[size], B[size], C[size], D[size];
char S[1505 * 1505], Op[5000005];
int offset[128];
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0, cp = 0; i < n; ++i, cp += m)
        scanf("%s", S + cp);
    std::deque<bool> P;
    {
        P.push_back(false);
        int cpos = 0;
        scanf("%s", Op + 1);
        offset['w'] = -m, offset['s'] = m;
        offset['a'] = -1, offset['d'] = 1;
        for(int i = 1; i <= k; ++i) {
            int off = offset[Op[i]];
            if(cpos > 0) {
                int end = cpos + off;
                while(end >= P.size())
                    P.push_back(true);
                P[end] = false;
                cpos = end;
            } else {
                int end = cpos - off;
                if(end >= 0)
                    P[end] = false, cpos = end;
                else {
                    end = -end;
                    for(int j = 0; j < end; ++j)
                        P.push_front(true);
                    P[0] = false, cpos = 0;
                }
            }
        }
    }
    int siz = 1, off = -1, len = n * m,
        plen = P.size(), end = len + P.size();
    while(siz < end)
        siz <<= 1, ++off;
    {
        for(int i = 0; i < len; ++i)
            A[i] = S[i] == '0';
        for(int i = 1; i <= P.size(); ++i)
            B[i] = 1;
        for(int i = 0; i < len; ++i)
            C[i] = S[i] == '1';
        int cur = 0;
        typedef std::deque<bool>::reverse_iterator
            IterT;
        for(IterT it = P.rbegin(); it != P.rend();
            ++it)
            D[++cur] = *it;
        for(int i = 0; i < P.size(); ++i)
            putchar(P[i] ? '*' : '0');
        puts("");
        std::deque<bool> empty;
        P.swap(empty);
    }
    for(int i = 1; i < siz; ++i)
        rev[i] = rev[i] >> 1 | (i & 1) << off;
    FFT(siz, A, root);
    FFT(siz, B, root);
    FFT(siz, C, root);
    FFT(siz, D, root);
    for(int i = 0; i < siz; ++i)
        A[i] = A[i] * B[i] + C[i] * D[i];
    FFT(siz, A, invR);
    FT eps = (plen - 0.5) * siz;
    int res = 0;
    for(int i = 0; i < len; ++i)
        if(A[i + plen].real() > eps)
            ++res;
    printf("%d\n", res);
    return 0;
}
