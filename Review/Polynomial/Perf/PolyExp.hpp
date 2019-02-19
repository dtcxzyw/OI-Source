#include "PolyInv.hpp"
void der(int n, Poly& f) {
    for(int i = 1; i < n; ++i)
        f[i - 1] = i * asInt64(f[i]) % mod;
    f[n - 1] = 0;
}
int lut[size];
void preInv(int n) {
    static int cur = 1;
    lut[1] = 1;
    while(cur < n) {
        ++cur;
        lut[cur] = asInt64(mod - mod / cur) *
            lut[mod % cur] % mod;
    }
}
void inte(int n, Poly& f) {
    for(int i = n; i >= 1; --i)
        f[i] = asInt64(lut[i]) * f[i - 1] % mod;
    f[0] = 0;
}
void getLn(int n, Poly& sf, Poly& g) {
    int p = getSize(n);
    getInv(n, sf, g);
    DFT(p, g);
    der(n, sf);
    DFT(p, sf);
    for(int i = 0; i < p; ++i)
        g[i] = asInt64(sf[i]) * g[i] % mod;
    IDFT(p, g, 0, n);
    inte(n, g);
}
void getExp(int n, const Poly& sf, Poly& g) {
    if(n == 1)
        g[0] = 1;
    else {
        int h = (n + 1) >> 1;
        getExp(h, sf, g);

        int p = getSize(n);
        Poly tg(p), lng(p);
        copy(tg, g, h);
        getLn(n, tg, lng);
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
        IDFT(p, g, 0, n);
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
            // ln g-f!!!
            Poly tg(n);
            for(int i = 1; i < h; ++i)
                tg[i - 1] = asInt64(g[i]) * i % mod;
            DFT(n, tg);
            for(int i = 0; i < n; ++i)
                tg[i] =
                    asInt64(tg[i]) * dftig[i] % mod;

            IDFT(n, tg, h - 1, n - 1);
            for(int i = n - 1; i >= h; --i)
                tg[i] =
                    asInt64(lut[i]) * tg[i - 1] % mod;
            tg[h - 1] = 0;
            for(int i = h; i < n; ++i)
                tg[i] = sub(tg[i], sf[i]);

            Poly dftg(n);
            copy(dftg, g, h);
            DFT(n, dftg);

            //(ln g-f)*g
            DFT(n, tg);
            for(int i = 0; i < n; ++i)
                tg[i] = asInt64(tg[i]) * dftg[i] % mod;
            IDFT(n, tg, h, n, false);

            for(int i = h; i < n; ++i)
                g[i] = (tg[i] ? mod - tg[i] : 0);
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
using ExpFunc =
    std::function<void(int n, const Poly&, Poly&)>;
Duration benchmarkExp(int n, const ExpFunc& exp) {
    n -= 3;
    int p = getSize(n);
    preInv(p);
    puts("Generating input data for PolyExp...");
    Poly f = genData(n, p, mod);
    f[0] = 0;
    Poly g(p);
    puts("Calculating PolyExp...");
    Duration t = time([&] { exp(n + 3, f, g); });
    puts("Checking the result...");
    Poly lg(p);
    getLnFast(n + 3, g, lg);
    for(int i = 0; i < n; ++i)
        if(f[i] != lg[i])
            throw WrongAnswer{};
    puts("Done.");
    return t;
}
