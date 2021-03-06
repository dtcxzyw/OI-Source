#pragma once
#include "NTT.hpp"
#include <functional>
void getInv(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = powm(sf[0], mod - 2);
    else {
        int h = (n + 1) >> 1;
        getInv(h, sf, g);

        int p = getSize(n);
        DFT(p, g);

        Poly f(p);
        copyPoly(f, sf, n);
        DFT(p, f);

        for(int i = 0; i < p; ++i) {
            g[i] = (2 - asInt64(f[i]) * g[i]) % mod *
                g[i] % mod;
            g[i] = clamp(g[i]);
        }
        IDFT(p, g, 0, n);
    }
}
void fastInvIter(int n, const Poly& sf,
                 const Poly& dftg, Poly& g) {
    int h = n >> 1;
    Poly f(n);
    copyPoly(f, sf, n);
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
        copyPoly(dftg, g, h);
        DFT(n, dftg);
        fastInvIter(n, sf, dftg, g);
    }
}
void getInvFast(int n, const Poly& sf, Poly& g) {
    int p = 1;
    while(p < n)
        p <<= 1;
    getInvFastImpl(p, sf, g);
    memset(data(g) + n, 0, sizeof(int) * (p - n));
}
using InvFunc =
    std::function<void(int n, const Poly&, Poly&)>;
Duration benchmarkInv(int n, const InvFunc& inv) {
    int p = getSize(n);
    puts("Generating input data for PolyInv...");
    Poly f = genData(n, p, mod);
    if(f[0] == 0)
        f[0] = 1;
    Poly g(p);
    puts("Calculating PolyInv...");
    Duration t = time([&] { inv(n, f, g); });
    puts("Checking the result...");
    DFT(p, f);
    DFT(p, g);
    for(int i = 0; i < p; ++i)
        f[i] = asInt64(f[i]) * g[i] % mod;
    IDFT(p, f, 0, n);
    if(f[0] != 1)
        throw WrongAnswer{};
    for(int i = 1; i < n; ++i)
        if(f[i] != 0)
            throw WrongAnswer{};
    puts("Done.");
    return t;
}
