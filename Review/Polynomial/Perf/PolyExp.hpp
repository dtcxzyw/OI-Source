#include "PolyInv.hpp"
void der(int n, Poly& f) {
    for(int i = 1; i < n; ++i)
        f[i - 1] = i * asInt64(f[i]) % mod;
    f[n - 1] = 0;
}
int lut[size + 10];
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
    for(int i = n - 1; i >= 1; --i)
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
