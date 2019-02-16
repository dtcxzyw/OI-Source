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
        copy(f, sf, n);
        DFT(p, f);

        for(int i = 0; i < p; ++i) {
            g[i] = (2 - asInt64(f[i]) * g[i]) % mod *
                g[i] % mod;
            g[i] = clamp(g[i]);
        }
        IDFT(p, g, n);
    }
}
using InvFunc =
    std::function<void(int n, const Poly&, Poly&)>;
Clock::duration benchmarkInv(int n,
                             const InvFunc& inv) {
    int p = getSize(n);
    puts("Generating input data for PolyInv...");
    Poly f = genData(n, p, mod);
    Poly g(p);
    puts("Calculating PolyInv...");
    Clock::duration t = time([&] { inv(n, f, g); });
    puts("Checking the result...");
    DFT(p, f);
    DFT(p, g);
    for(int i = 0; i < p; ++i)
        f[i] = asInt64(f[i]) * g[i] % mod;
    IDFT(p, f, n);
    if(f[0] != 1)
        throw WrongAnswer{};
    for(int i = 1; i < n; ++i)
        if(f[i] != 0)
            throw WrongAnswer{};
    puts("Done.");
    return t;
}
