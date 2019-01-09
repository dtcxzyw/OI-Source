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
const int size = 1 << 17, maxn = 100005,
          mod = 998244353;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
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
int getSize(int n) {
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
}
typedef std::vector<int> Poly;
void DFT(int n, const Poly& src, int* A) {
    int rn = src.size();
    memcpy(A, src.data(), sizeof(int) * rn);
    memset(A + rn, 0, sizeof(int) * (n - rn));
    NTT(n, A, root);
}
int w[maxn], A[size], B[size];
Int64 scale = 1;
Poly solve(int l, int r) {
    if(l == r) {
        Poly res(w[l] + 1);
        res[0] = 1, res[w[l]] = mod - 1;
        return res;
    } else {
        int m = (l + r) >> 1;
        Poly ls = solve(l, m), rs = solve(m + 1, r);
        int siz = ls.size() + rs.size() - 1,
            p = getSize(siz);
        scale = scale * p % mod;
        DFT(p, ls, A);
        DFT(p, rs, B);
        for(int i = 0; i < p; ++i)
            A[i] = asInt64(A[i]) * B[i] % mod;
        NTT(p, A, invR);
        Poly res(siz);
        memcpy(res.data(), A, sizeof(int) * siz);
        return res;
    }
}
int inv[maxn];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        w[i] = read();
    int sw = 0;
    for(int i = 2; i <= n; ++i)
        sw += w[i];
    init(getSize(sw + 1));
    Poly res = solve(2, n);
    inv[1] = 1;
    int end = sw + w[1];
    for(int i = 2; i <= end; ++i)
        inv[i] = asInt64(mod - mod / i) *
            inv[mod % i] % mod;
    Int64 sum = 0;
    for(int i = 0; i <= sw; ++i)
        sum = (sum + asInt64(res[i]) * inv[i + w[1]]) %
            mod;
    printf("%lld\n", sum * powm(scale, mod - 2) % mod *
               w[1] % mod);
    return 0;
}
