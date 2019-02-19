#pragma once
#include "PolyInv.hpp"
Int64 D;
struct Complex {
    Int64 a, b;
    Complex(Int64 a, Int64 b) : a(a), b(b) {}
    Complex operator*(const Complex& rhs) const {
        return Complex(
            (a * rhs.a + b * rhs.b % mod * D) % mod,
            (a * rhs.b + b * rhs.a) % mod);
    }
};
Int64 getRandom() {
    static int seed = 23462;
    return seed = seed * 48671LL % 2147483647;
}
Complex powm(Complex a, int k) {
    Complex res(1, 0);
    while(k) {
        if(k & 1)
            res = res * a;
        k >>= 1, a = a * a;
    }
    return res;
}
int sqrt(int x) {
    while(true) {
        Int64 b = getRandom() % mod;
        D = (b * b - x) % mod;
        if(D < 0)
            D += mod;
        if(powm(D, (mod - 1) / 2) == mod - 1) {
            Int64 res =
                powm(Complex(b, 1), (mod + 1) / 2).a;
            return std::min(res, mod - res);
        }
    }
}
constexpr Int64 inv2 = 499122177;
void getSqrt(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = sqrt(sf[0]);
    else {
        int h = (n + 1) >> 1;
        getSqrt(h, sf, g);

        int p = getSize(n);
        Poly f(p);
        copy(f, sf, n);
        DFT(p, f);

        Poly tg(p), ig(p);
        copy(tg, g, h);
        getInv(n, tg, ig);
        tg.clear();
        DFT(p, ig);
        DFT(p, g);

        for(int i = 0; i < p; ++i)
            g[i] = inv2 *
                (g[i] + asInt64(f[i]) * ig[i] % mod) %
                mod;
        IDFT(p, g, 0, n);
    }
}
constexpr Int64 negInv2 = mod - inv2;
void getSqrtFastImpl(int n, const Poly& sf, Poly& g,
                     Poly& ig, bool doInv = true) {
    if(n == 1) {
        g[0] = sqrt(sf[0]);
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
using SqrtFunc =
    std::function<void(int n, const Poly&, Poly&)>;
Duration benchmarkSqrt(int n, const SqrtFunc& sqrt) {
    int p = getSize(n);
    puts("Generating input data for PolySqrt...");
    Poly f = genData(n, p, mod);
    if(f[0] == 0)
        f[0] = 1;
    Int64 base = std::min(f[0], mod - f[0]);
    f[0] = base * base % mod;
    Poly g(p);
    puts("Calculating PolySqrt...");
    Duration t = time([&] { sqrt(n, f, g); });
    puts("Checking the result...");
    if(g[0] != base)
        throw WrongAnswer{};
    DFT(p, g);
    for(int i = 0; i < p; ++i)
        g[i] = asInt64(g[i]) * g[i] % mod;
    IDFT(p, g, 0, n);
    for(int i = 0; i < n; ++i)
        if(g[i] != f[i])
            throw WrongAnswer{};
    puts("Done.");
    return t;
}
