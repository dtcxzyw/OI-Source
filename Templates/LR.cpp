#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int size = 1 << 16, mod = 998244353;
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res ? (flag ? mod - res : res) : 0;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
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
                int &x = A[j + k], &y = A[j + k + m];
                int t = asInt64(w[k * fac]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
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
int getSize(int n) {
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
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
        int p = getSize(2 * n);
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
    }
}
int k, p;
Poly invGR, G;
void polyMod(Poly& A) {
    Poly B(p);
    std::reverse_copy(A.begin() + k,
                      A.begin() + 2 * k - 1,
                      B.begin());
    DFT(p, B);
    for(int i = 0; i < p; ++i)
        B[i] = asInt64(B[i]) * invGR[i] % mod;
    IDFT(p, B, k - 1);
    std::reverse(B.begin(), B.begin() + k - 1);
    DFT(p, B);
    for(int i = 0; i < p; ++i)
        B[i] = asInt64(B[i]) * G[i] % mod;
    IDFT(p, B, k);
    for(int i = 0; i < k; ++i)
        A[i] = sub(A[i], B[i]);
    memset(A.data() + k, 0, sizeof(int) * (k - 1));
}
struct LazyPoly {
    Poly poly;
    int k;
    void init() {
        if(poly.empty()) {
            poly.resize(p);
            poly[k] = 1;
        }
    }
};
int main() {
    int n = read();
    k = read();
    p = getSize(2 * k);
    init(p);
    G.resize(p);
    G[0] = 1;
    for(int i = 1; i <= k; ++i) {
        int x = read();
        G[i] = (x ? mod - x : 0);
    }
    invGR.resize(p);
    inv(k - 1, G, invGR);
    DFT(p, invGR);
    std::reverse(G.begin(), G.begin() + k + 1);
    DFT(p, G);
    LazyPoly res, mul;
    res.k = 0, mul.k = 1;
    while(n) {
        if(n & 1) {
            if(res.poly.empty() && mul.poly.empty() &&
               res.k + mul.k < k)
                res.k += mul.k;
            else {
                res.init();
                mul.init();
                DFT(p, res.poly);
                Poly tmp = mul.poly;
                DFT(p, tmp);
                for(int i = 0; i < p; ++i)
                    res.poly[i] =
                        asInt64(res.poly[i]) * tmp[i] %
                        mod;
                IDFT(p, res.poly, 2 * k - 1);
                polyMod(res.poly);
            }
        }
        n >>= 1;
        if(mul.poly.empty() && mul.k * 2 < k)
            mul.k *= 2;
        else {
            mul.init();
            DFT(p, mul.poly);
            for(int i = 0; i < p; ++i)
                mul.poly[i] = asInt64(mul.poly[i]) *
                    mul.poly[i] % mod;
            IDFT(p, mul.poly, 2 * k - 1);
            polyMod(mul.poly);
        }
    }
    res.init();
    int ans = 0;
    for(int i = 0; i < k; ++i)
        ans = (ans + asInt64(res.poly[i]) * read()) %
            mod;
    printf("%d\n", ans);
    return 0;
}
