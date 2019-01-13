#include <cstdio>
#include <cstring>
#include <vector>
//#define CHECK
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
void NTT(int n, int* A, const int* w) {
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
                int &x = A[j + k + m], &y = A[j + k];
                int t = x * asInt64(w[k * fac]) % mod;
                x = sub(y, t);
                y = add(y, t);
            }
    }
}
typedef std::vector<int> Poly;
void DFT(int n, Poly& A) {
    NTT(n, A.data(), root);
}
void IDFT(int n, Poly& A, int rn) {
    NTT(n, A.data(), invR);
    Int64 div = powm(n, mod - 2);
    for(int i = 0; i < rn; ++i)
        A[i] = A[i] * div % mod;
    memset(A.data() + rn, 0, sizeof(int) * (n - rn));
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
            g[i] = (2 - asInt64(g[i]) * f[i]) % mod *
                g[i] % mod;
            if(g[i] < 0)
                g[i] += mod;
        }
        IDFT(p, g, n);
#ifdef CHECK
        for(int i = 0; i < n; ++i) {
            int sum = 0;
            for(int j = 0; j <= i; ++j)
                sum =
                    (sum + asInt64(sf[j]) * g[i - j]) %
                    mod;
            if(i == 0 && sum != 1)
                throw;
            if(i != 0 && sum != 0)
                throw;
        }
#endif
    }
}
Int64 inv2;
void sqrt(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = Residue::sqrt(sf[0]);
    else {
        int h = (n + 1) >> 1;
        sqrt(h, sf, g);

        int p = getSize(n);
        Poly f(p);
        copy(f, sf, n);
        DFT(p, f);

        Poly tg(p), ig(p);
        copy(tg, g, h);
        inv(n, tg, ig);
        tg.clear();
        DFT(p, ig);
        DFT(p, g);

        for(int i = 0; i < p; ++i)
            g[i] = inv2 *
                (g[i] + asInt64(f[i]) * ig[i] % mod) %
                mod;
        IDFT(p, g, n);
#ifdef CHECK
        for(int i = 0; i < n; ++i) {
            int sum = 0;
            for(int j = 0; j <= i; ++j)
                sum =
                    (sum + asInt64(g[j]) * g[i - j]) %
                    mod;
            if(sum != sf[i])
                throw;
        }
#endif
    }
}
void der(int n, Poly& f) {
    for(int i = 1; i < n; ++i)
        f[i - 1] = i * asInt64(f[i]) % mod;
    f[n - 1] = 0;
}
int lut[100005];
void preInv(int n) {
    static int cur = 1;
    while(cur < n) {
        ++cur;
        lut[cur] = asInt64(mod - mod / cur) *
            lut[mod % cur] % mod;
    }
}
void inte(int n, Poly& f) {
    preInv(n);
    for(int i = n; i >= 1; --i)
        f[i] = asInt64(lut[i]) * f[i - 1] % mod;
    f[0] = 0;
}
void ln(int n, Poly& sf, Poly& g) {
    int p = getSize(n);
    inv(n, sf, g);
    DFT(p, g);
    der(n, sf);
    DFT(p, sf);
    for(int i = 0; i < p; ++i)
        g[i] = asInt64(sf[i]) * g[i] % mod;
    IDFT(p, g, n);
    inte(n, g);
}
void exp(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = 1;
    else {
        int h = (n + 1) >> 1;
        exp(h, sf, g);

        int p = getSize(n);
        Poly tg(p), lng(p);
        copy(tg, g, h);
        ln(n, tg, lng);
        tg.clear();
        DFT(p, lng);
        DFT(p, g);

        Poly f(p);
        copy(f, sf, n);
        DFT(p, f);

        for(int i = 0; i < p; ++i) {
            g[i] = g[i] * asInt64(1 - lng[i] + f[i]) %
                mod;
            if(g[i] < 0)
                g[i] += mod;
        }
        IDFT(p, g, n);
    }
}
int main() {
    lut[1] = 1;
    inv2 = powm(2, mod - 2);
    int n = read() + 1;
    Int64 k = read();
    int end = n + 1;
    int p = getSize(end);
    init(p);
    Poly in(end), a(p), b(p);
    for(int i = 0; i < n; ++i)
        in[i] = read();
    sqrt(end, in, a);
    inv(end, a, b);
    inte(end, b);
    reset(a);
    exp(end, b, a);
    in[0] = 2;
    for(int i = 0; i < n; ++i)
        a[i] = sub(in[i], a[i]);
    reset(b);
    ln(end, a, b);
    b[0] = 1;
    reset(a);
    ln(end, b, a);
    for(int i = 0; i < end; ++i)
        a[i] = k * a[i] % mod;
    reset(b);
    exp(end, a, b);
    der(end, b);
    end = n - 1;
    for(int i = 0; i < end; ++i)
        printf("%d ", b[i]);
    return 0;
}
