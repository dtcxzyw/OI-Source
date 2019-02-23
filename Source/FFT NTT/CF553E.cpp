#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
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
typedef double FT;
typedef std::complex<FT> Complex;
const int size = 1 << 17;
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
struct Edge {
    int u, v, c;
} E[105];
int dis[55];
void SSSP(int n, int m) {
    memset(dis, 0x3f, sizeof(dis));
    dis[n] = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            int u = E[j].u, v = E[j].v;
            if(dis[v] + E[j].c < dis[u])
                dis[u] = dis[v] + E[j].c;
        }
}
FT EV[55][size], S[105][size], P[105][size];
int M, T;
//[m+1,r]->[l,m]
Complex A[size], B[size];
void trans(int l, int m, int r) {
    for(int k = 1; k <= M; ++k) {
        int v = E[k].v;
        int off = std::min(r - l + 1, T),
            tot = off + r - m;
        int p = 1;
        while(p <= tot)
            p <<= 1;
        memset(A, 0, sizeof(Complex) * p);
        for(int i = 1; m + i <= r; ++i)
            A[i] = EV[v][m + i];
        memset(B, 0, sizeof(Complex) * p);
        for(int i = 0; i <= off; ++i)
            B[i] = P[k][off - i];
        FFT(p, A, root);
        FFT(p, B, root);
        for(int i = 0; i < p; ++i)
            A[i] *= B[i];
        FFT(p, A, invR);
        for(int i = m, j = off; i >= l; --i, --j) {
            FT x = A[j].real() / p;
            S[k][i] += x;
        }
    }
}
void solve(int l, int r) {
    if(l == r) {
        for(int i = 1; i <= M; ++i) {
            int u = E[i].u;
            EV[u][l] =
                std::min(EV[u][l], S[i][l] + E[i].c);
        }
    } else {
        int m = (l + r) >> 1;
        solve(m + 1, r);
        trans(l, m, r);
        solve(l, m);
    }
}
int main() {
    int n = read();
    M = read();
    T = read();
    int x = read();
    for(int i = 1; i <= M; ++i) {
        E[i].u = read();
        E[i].v = read();
        E[i].c = read();
        for(int j = 1; j <= T; ++j)
            P[i][j] = read() / 1e5;
    }
    int p = 1;
    while(p < ((T + 5) * 2))
        p <<= 1;
    init(p);
    SSSP(n, M);
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= T; ++j) {
            EV[i][j] = (i == n ? 0.0 : 1e50);
            EV[i][j + T] = x + dis[i];
        }
    }
    trans(0, T, 2 * T + 1);
    solve(0, T);
    printf("%.10lf\n", EV[1][0]);
    return 0;
}
