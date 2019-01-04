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
const int size = 1 << 18, mod = 998244353;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
Int64 inv3, inv23;
int cube(int x) {
    const int k = (2 * mod - 1) / 3;
    return powm(x, k);
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
    const int g = 3;
    tot = n;
    Int64 base = powm(g, (mod - 1) / n);
    root[0] = invR[0] = 1;
    for(int i = 1; i < n; ++i)
        root[i] = root[i - 1] * base % mod;
    Int64 invBase = powm(base, mod - 2);
    for(int i = 1; i < n; ++i)
        invR[i] = invR[i - 1] * invBase % mod;
}
void NTT(int n, int* A, const int* w, int rn = 0) {
    for(int i = 0, j = 0; i < n; ++i) {
        if(i > j)
            std::swap(A[i], A[j]);
        int l = n >> 1;
        while((j ^= l) < l)
            l >>= 1;
    }
    for(int i = 2; i <= n; i <<= 1) {
        int m = i >> 1, fac = tot / i;
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                int t = A[j + k + m] *
                    asInt64(w[k * fac]) % mod;
                A[j + k + m] = sub(A[j + k], t);
                A[j + k] = add(A[j + k], t);
            }
    }
    if(w == invR) {
        Int64 k = powm(n, mod - 2);
        for(int i = 0; i < rn; ++i)
            A[i] = A[i] * k % mod;
        memset(A + rn, 0, sizeof(int) * (n - rn));
    }
}
typedef std::vector<int> Poly;
void inv(int n, const Poly& f, Poly& g) {
    if(n == 1)
        g[0] = powm(f[0], mod - 2);
    else {
        int p = 1;
        while(p < (n << 1))
            p <<= 1;
        inv((n + 1) >> 1, f, g);
        NTT(p, g.data(), root);

        Poly cf(p);
        memcpy(cf.data(), f.data(), sizeof(int) * n);
        NTT(p, cf.data(), root);
        for(int i = 0; i < p; ++i) {
            g[i] = (2 - asInt64(g[i]) * cf[i] % mod) *
                g[i] % mod;
            if(g[i] < 0)
                g[i] += mod;
        }
        NTT(p, g.data(), invR, n);
    }
}
void cube(int n, const Poly& f, Poly& g) {
    if(n == 1)
        g[0] = cube(f[0]);
    else {
        int p = 1;
        while(p < (n << 1))
            p <<= 1;
        cube((n + 1) >> 1, f, g);

        Poly tg(p), ig(p);
        memcpy(tg.data(), g.data(),
               sizeof(int) * ((n + 1) >> 1));
        NTT(p, tg.data(), root);
        for(int i = 0; i < p; ++i)
            tg[i] = asInt64(tg[i]) * tg[i] % mod;
        NTT(p, tg.data(), invR, n);
        inv(n, tg, ig);
        tg.clear();
        NTT(p, ig.data(), root);

        Poly cf(p);
        memcpy(cf.data(), f.data(), sizeof(int) * n);
        NTT(p, cf.data(), root);

        NTT(p, g.data(), root);
        for(int i = 0; i < p; ++i) {
            g[i] = (inv23 * g[i] +
                    inv3 * cf[i] % mod * ig[i]) %
                mod;
        }
        NTT(p, g.data(), invR, n);
    }
}
int main() {
    inv3 = powm(3, mod - 2);
    inv23 = 2 * inv3 % mod;
    int n = read() + 1;
    int siz = 1;
    while(siz < (n << 1))
        siz <<= 1;
    Poly in(siz);
    for(int i = 0; i < n; ++i)
        in[i] = read();
    Poly res(siz);
    init(siz);
    cube(n, in, res);
    for(int i = 0; i < n; ++i)
        printf("%d ", res[i]);
    return 0;
}
