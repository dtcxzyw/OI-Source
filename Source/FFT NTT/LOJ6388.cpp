#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <deque>
typedef double FT;
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
Complex A[size], B[size], C[size];
char S[1505 * 1505], Op[5000005];
int offset[128], ox[128], oy[128];
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0, cp = 0; i < n; ++i, cp += m)
        scanf("%s", S + cp);
    std::deque<bool> P;
    int l, r, t, b;
    {
        int minx = 0, maxx = 0, miny = 0, maxy = 0,
            cx = 0, cy = 0, lx = 0, ly = 0;
        P.push_back(false);
        int cpos = 0;
        scanf("%s", Op + 1);
        offset['w'] = -m, offset['s'] = m;
        offset['a'] = -1, offset['d'] = 1;
        ox['w'] = ox['s'] = 0, ox['a'] = -1,
        ox['d'] = 1;
        oy['w'] = -1, oy['s'] = 1,
        oy['a'] = oy['d'] = 0;
        for(int i = 1; i <= k; ++i) {
            int op = Op[i];
            int off = offset[op];
            int end = cpos + off;
            cx += ox[op], cy += oy[op];
            minx = std::min(minx, cx);
            maxx = std::max(maxx, cx);
            miny = std::min(miny, cy);
            maxy = std::max(maxy, cy);
            if(off > 0) {
                while(end >= P.size())
                    P.push_back(true);
                P[end] = false;
                cpos = end;
            } else {
                if(end >= 0)
                    P[end] = false, cpos = end;
                else {
                    end = -end;
                    for(int j = 0; j < end; ++j)
                        P.push_front(true);
                    P[0] = false, cpos = 0;
                    lx = cx, ly = cy;
                }
            }
        }
        l = lx - minx, r = lx + (m - 1 - maxx);
        t = ly - miny, b = ly + (n - 1 - maxy);
    }
    int len = n * m, plen = P.size();
    {
        for(int i = 0; i < len; ++i)
            A[i].real(S[i] == '0');
        for(int i = 1; i <= P.size(); ++i)
            A[i].imag(1.0);
        for(int i = 0; i < len; ++i)
            B[i].real(S[i] == '1');
        int cur = 0;
        typedef std::deque<bool>::reverse_iterator
            IterT;
        for(IterT it = P.rbegin(); it != P.rend();
            ++it)
            B[++cur].imag(*it);
        std::deque<bool> empty;
        P.swap(empty);
    }
    int siz = 1, off = -1, end = len + plen;
    while(siz < end)
        siz <<= 1, ++off;
    init(siz);
    for(int i = 1; i < siz; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << off;
    FFT(siz, A, root);
    FFT(siz, B, root);
    C[0] = 4.0 *
        (A[0].real() * A[0].imag() +
         B[0].real() * B[0].imag());
    for(int i = 1; i < siz; ++i) {
        FT x1 = A[i].real(), y1 = A[i].imag();
        FT x2 = A[siz - i].real(),
           y2 = A[siz - i].imag();
        FT x3 = B[i].real(), y3 = B[i].imag();
        FT x4 = B[siz - i].real(),
           y4 = B[siz - i].imag();
        Complex a(x1 + x2, y1 - y2);
        Complex b(y1 + y2, x2 - x1);
        Complex c(x3 + x4, y3 - y4);
        Complex d(y3 + y4, x4 - x3);
        C[i] = a * b + c * d;
    }
    FFT(siz, C, invR);
    FT eps = (plen - 0.5) * siz * 4.0;
    int res = 0;
    for(int y = 0, id = plen; y < n; ++y)
        for(int x = 0; x < m; ++x, ++id) {
            if(l <= x && x <= r && t <= y && y <= b &&
               C[id].real() > eps)
                ++res;
        }
    printf("%d\n", res);
    return 0;
}
