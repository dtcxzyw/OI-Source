#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
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
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 1 << 18, maxn = 100050,
          mod = 998244353;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int tot, root[size], invR[size];
void init(int n) {
    tot = n;
    Int64 base = powm(3, (mod - 1) / n);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for(int i = 1; i < n; ++i)
        root[i] = root[i - 1] * base % mod;
    for(int i = 1; i < n; ++i)
        invR[i] = invR[i - 1] * invBase % mod;
}
void NTT(int* A, int n, const int* w) {
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
                int &x = A[j + k], &y = A[j + k + m];
                int t = asInt64(w[k * fac]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
int getSize(int n) {
    n <<= 1;
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
}
typedef std::vector<int> Poly;
void DFT(int n, Poly& A) {
    NTT(A.data(), n, root);
}
void IDFT(int n, Poly& A, int rn) {
    NTT(A.data(), n, invR);
    Int64 div = powm(n, mod - 2);
    for(int i = 0; i < rn; ++i)
        A[i] = A[i] * div % mod;
    memset(A.data() + rn, 0, sizeof(int) * (n - rn));
}
void copy(Poly& dst, const Poly& src, int siz) {
    memcpy(dst.data(), src.data(), sizeof(int) * siz);
}
void inv(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = powm(sf[0], mod - 2);
    else {
        int h = (n + 1) >> 1;
        inv(h, sf, g);
        int p = getSize(n);
        DFT(p, g);

        Poly f(p);
        copy(f, sf, n);
        DFT(p, f);

        for(int i = 0; i < p; ++i) {
            g[i] = (2 - asInt64(g[i]) * f[i] % mod) *
                g[i] % mod;
            if(g[i] < 0)
                g[i] += mod;
        }

        IDFT(p, g, n);
    }
}
int lut[maxn];
void inte(int n, Poly& A) {
    for(int i = n - 1; i >= 1; --i)
        A[i] = asInt64(A[i - 1]) * lut[i] % mod;
    A[0] = 0;
}
void derv(int n, Poly& A) {
    for(int i = 1; i < n; ++i)
        A[i - 1] = i * asInt64(A[i]) % mod;
    A[n - 1] = 0;
}
void ln(int n, Poly& A) {
    int p = getSize(n);
    Poly IA(p);
    inv(n, A, IA);
    DFT(p, IA);

    derv(n, A);
    DFT(p, A);

    for(int i = 0; i < p; ++i)
        A[i] = asInt64(A[i]) * IA[i] % mod;

    IDFT(p, A, n);
    inte(n, A);
}
void exp(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = 1;
    else {
        int h = (n + 1) >> 1;
        exp(h, sf, g);
        int p = getSize(n);

        Poly lng(p);
        copy(lng, g, h);
        ln(n, lng);
        DFT(p, lng);

        Poly f(p);
        copy(f, sf, n);
        DFT(p, f);

        DFT(p, g);
        for(int i = 0; i < p; ++i) {
            g[i] = g[i] * asInt64(1 - lng[i] + f[i]) %
                mod;
            if(g[i] < 0)
                g[i] += mod;
        }
        IDFT(p, g, n);
    }
}
int cnt[maxn];
int main() {
    int n = read();
    int m = read();
    int end = n + 3;
    int p = getSize(end);
    init(p);
    int maxk = 0;
    while(m--) {
        int a = read();
        int b = read();
        if(a > n)
            continue;
        Int64 k = a * asInt64(b + 1);
        if(b && k < end) {
            --cnt[k];
            maxk = std::max(maxk, static_cast<int>(k));
        }
        ++cnt[a];
        maxk = std::max(maxk, a);
    }
    lut[1] = 1;
    for(int i = 2; i <= end; ++i)
        lut[i] = asInt64(mod - mod / i) *
            lut[mod % i] % mod;
    Poly f(p);
    for(int i = 1; i <= maxk; ++i)
        if(cnt[i]) {
            Int64 k = cnt[i];
            if(k < 0)
                k += mod;
            for(int j = i, c = 1; j < end; j += i, ++c)
                f[j] = (f[j] + k * lut[c]) % mod;
        }
    Poly g(p);
    exp(end, f, g);
    for(int i = 1; i <= n; ++i)
        printf("%d\n", g[i]);
    return 0;
}
