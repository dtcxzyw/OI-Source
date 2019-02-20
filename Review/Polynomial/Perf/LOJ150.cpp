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
const int mod = 998244353;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
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
namespace Residue {
    Int64 i2;
    struct Complex {
        Int64 a, b;
        Complex(Int64 a, Int64 b) : a(a), b(b) {}
        Complex operator*(const Complex& rhs) const {
            return Complex(
                (a * rhs.a + b * rhs.b % mod * i2) %
                    mod,
                (a * rhs.b + b * rhs.a) % mod);
        }
    };
    Complex powm(Complex a, int k) {
        Complex res(1, 0);
        while(k) {
            if(k & 1)
                res = res * a;
            k >>= 1, a = a * a;
        }
        return res;
    }
    Int64 getRandom() {
        static int seed = 2523;
        return (seed = seed * 48271LL % 2147483647) %
            mod;
    }
    int sqrt(int x) {
        if(x == 0)
            return 0;
        while(true) {
            Int64 b = getRandom();
            i2 = sub(b * b % mod, x);
            if(::powm(i2, (mod - 1) / 2) == mod - 1) {
                int a = powm(Complex(b, 1),
                             (mod + 1) / 2)
                            .a,
                    b = mod - a;
                return a < b ? a : b;
            }
        }
        return -1;
    }
}
const int size = 1 << 18;
using NTTFac = std::vector<int>;
NTTFac root[20], invR[20], rev[20];
void initImpl(int k) {
    int siz = 1 << k;
    Int64 base = powm(3, (mod - 1) / siz);
    Int64 invBase = powm(base, mod - 2);
    NTTFac &rt = root[k], &irt = invR[k];
    rt.resize(siz), irt.resize(siz);
    rt[0] = irt[0] = 1;
    for(int i = 1; i < siz; ++i)
        rt[i] = rt[i - 1] * base % mod;
    for(int i = 1; i < siz; ++i)
        irt[i] = irt[i - 1] * invBase % mod;
    NTTFac& A = rev[k];
    A.resize(siz);
    int off = k - 1;
    for(int i = 0; i < siz; ++i)
        A[i] = A[i >> 1] >> 1 | ((i & 1) << off);
}
void init(int n) {
    for(int i = 0; (1 << i) <= n; ++i)
        initImpl(i);
}
void NTT(int n, int* A, const NTTFac* w) {
    int p = 0;
    while(1 << p != n)
        ++p;
    NTTFac& R = rev[p];
    for(int i = 0; i < n; ++i)
        if(i < R[i])
            std::swap(A[i], A[R[i]]);
    for(int i = 2, cp = 1; i <= n; i <<= 1, ++cp) {
        int m = i >> 1;
        const NTTFac& fac = w[cp];
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + m + k];
                int t = asInt64(fac[k]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
typedef std::vector<int> Poly;
void DFT(int n, Poly& A) {
    NTT(n, A.data(), root);
}
void IDFT(int n, Poly& A, int b, int e, bool lc = true,
          bool hc = true) {
    NTT(n, A.data(), invR);
    Int64 div = powm(n, mod - 2);
    for(int i = b; i < e; ++i)
        A[i] = A[i] * div % mod;
    if(lc)
        memset(A.data(), 0, sizeof(int) * b);
    if(hc)
        memset(A.data() + e, 0, sizeof(int) * (n - e));
}
void copy(Poly& dst, const Poly& src, int siz) {
    memcpy(dst.data(), src.data(), sizeof(int) * siz);
}
void reset(Poly& x) {
    memset(x.data(), 0, sizeof(int) * x.size());
}
int getSize(int x) {
    x <<= 1;
    int p = 1;
    while(p < x)
        p <<= 1;
    return p;
}
void fastInvIter(int n, const Poly& sf,
                 const Poly& dftg, Poly& g) {
    int h = n >> 1;
    Poly f(n);
    copy(f, sf, n);
    DFT(n, f);

    for(int i = 0; i < n; ++i)
        f[i] = asInt64(f[i]) * dftg[i] % mod;
    IDFT(n, f, h, n);

    DFT(n, f);
    for(int i = 0; i < n; ++i)
        f[i] = asInt64(f[i]) * dftg[i] % mod;
    IDFT(n, f, h, n, false);

    for(int i = h; i < n; ++i)
        g[i] = (f[i] ? mod - f[i] : 0);
}
void getInvFastImpl(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = powm(sf[0], mod - 2);
    else {
        int h = n >> 1;
        getInvFastImpl(h, sf, g);
        Poly dftg(n);
        copy(dftg, g, h);
        DFT(n, dftg);
        fastInvIter(n, sf, dftg, g);
    }
}
void getInvFast(int n, const Poly& sf, Poly& g) {
    int p = 1;
    while(p < n)
        p <<= 1;
    getInvFastImpl(p, sf, g);
    memset(g.data() + n, 0, sizeof(int) * (p - n));
}
const Int64 negInv2 = 499122176LL;
void getSqrtFastImpl(int n, const Poly& sf, Poly& g,
                     Poly& ig, bool doInv = true) {
    if(n == 1) {
        g[0] = Residue::sqrt(sf[0]);
        ig[0] = powm(g[0], mod - 2);
    } else {
        int h = n >> 1;
        getSqrtFastImpl(h, sf, g, ig);

        // shared
        Poly dftig(n);
        copy(dftig, ig, h);
        DFT(n, dftig);

        // sqrt
        {
            // g_0^2-f
            Poly tg(n);
            copy(tg, g, h);
            DFT(n, tg);
            for(int i = 0; i < n; ++i)
                tg[i] = asInt64(tg[i]) * tg[i] % mod;
            IDFT(n, tg, h, n);
            for(int i = h; i < n; ++i)
                tg[i] = sub(tg[i], sf[i]);
            //(g_0^2-f)*ig
            DFT(n, tg);
            for(int i = 0; i < n; ++i)
                tg[i] =
                    asInt64(tg[i]) * dftig[i] % mod;
            IDFT(n, tg, h, n, false);

            for(int i = h; i < n; ++i)
                g[i] = negInv2 * tg[i] % mod;
        }
        // inv
        if(doInv)
            fastInvIter(n, g, dftig, ig);
    }
}
void getSqrtFast(int n, const Poly& sf, Poly& g) {
    int p = 1;
    while(p < n)
        p <<= 1;
    Poly ig(p);
    getSqrtFastImpl(p, sf, g, ig, false);
    memset(g.data() + n, 0, sizeof(int) * (p - n));
}
int lut[size + 10];
void preInv(int n) {
    static int cur = 1;
    while(cur < n) {
        ++cur;
        lut[cur] = asInt64(mod - mod / cur) *
            lut[mod % cur] % mod;
    }
}
void getExpFastImpl(int n, const Poly& sf, Poly& g,
                    Poly& ig, bool doInv = true) {
    if(n == 1) {
        g[0] = ig[0] = 1;
    } else {
        int h = n >> 1;
        getExpFastImpl(h, sf, g, ig);

        // shared
        Poly dftig(n);
        copy(dftig, ig, h);
        DFT(n, dftig);

        // exp
        {
            // ln g-f
            Poly A(n);
            for(int i = 1; i < h; ++i)
                A[i - 1] = asInt64(g[i]) * i % mod;
            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * dftig[i] % mod;
            IDFT(n, A, h - 1, n - 1, false);

            Poly B(n), dftg(n);
            copy(dftg, g, h);
            DFT(n, dftg);
            for(int i = 0; i < n; ++i)
                B[i] =
                    asInt64(dftg[i]) * dftig[i] % mod;
            IDFT(n, B, h, n);

            Poly f(n);
            for(int i = 1; i < h; ++i)
                f[i - 1] = asInt64(sf[i]) * i % mod;
            DFT(n, f);
            DFT(n, B);
            for(int i = 0; i < n; ++i)
                B[i] = asInt64(B[i]) * f[i] % mod;
            IDFT(n, B, h - 1, n - 1, false);

            for(int i = n - 1; i >= h; --i) {
                Int64 x = sub(A[i - 1], B[i - 1]);
                A[i] = lut[i] * x % mod;
            }
            memset(A.data(), 0, sizeof(int) * h);

            for(int i = h; i < n; ++i)
                A[i] = sub(A[i], sf[i]);

            //(ln g-f)*g
            DFT(n, A);
            for(int i = 0; i < n; ++i)
                A[i] = asInt64(A[i]) * dftg[i] % mod;
            IDFT(n, A, h, n, false);

            for(int i = h; i < n; ++i)
                g[i] = (A[i] ? mod - A[i] : 0);
        }
        // inv
        if(doInv)
            fastInvIter(n, g, dftig, ig);
    }
}
void getExpFast(int n, const Poly& sf, Poly& g) {
    int p = 1;
    while(p < n)
        p <<= 1;
    Poly ig(p);
    getExpFastImpl(p, sf, g, ig, false);
    memset(g.data() + n, 0, sizeof(int) * (p - n));
}
void der(int n, Poly& f) {
    for(int i = 1; i < n; ++i)
        f[i - 1] = i * asInt64(f[i]) % mod;
    f[n - 1] = 0;
}
void inte(int n, Poly& f) {
    for(int i = n - 1; i >= 1; --i)
        f[i] = asInt64(lut[i]) * f[i - 1] % mod;
    f[0] = 0;
}
void getLnFast(int n, Poly& sf, Poly& g) {
    int p = getSize(n);
    getInvFast(n, sf, g);
    DFT(p, g);
    der(n, sf);
    DFT(p, sf);
    for(int i = 0; i < p; ++i)
        g[i] = asInt64(sf[i]) * g[i] % mod;
    IDFT(p, g, 0, n);
    inte(n, g);
}
int main() {
    int n = read() + 1;
    Int64 k = read();
    int end = n + 1;
    int p = getSize(end);
    lut[1] = 1;
    preInv(p);
    init(p);
    Poly in(end), a(p), b(p);
    for(int i = 0; i < n; ++i)
        in[i] = read();
    getSqrtFast(end, in, a);
    getInvFast(end, a, b);
    inte(end, b);
    reset(a);
    getExpFast(end, b, a);
    in[0] = 2;
    for(int i = 0; i < n; ++i)
        a[i] = sub(in[i], a[i]);
    reset(b);
    getLnFast(end, a, b);
    b[0] = 1;
    reset(a);
    getLnFast(end, b, a);
    for(int i = 0; i < end; ++i)
        a[i] = k * a[i] % mod;
    reset(b);
    getExpFast(end, a, b);
    der(end, b);
    end = n - 1;
    for(int i = 0; i < end; ++i)
        printf("%d ", b[i]);
    return 0;
}
