#include <climits>
#include <cstdio>
#include <cstring>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int mod = 65537;
const Int64 end = LLONG_MAX - asInt64(mod) * mod;
Int64 powm(Int64 a, Int64 k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
const int size = 6005;
Int64 X[size];
void mul(int m, int* A, int* B) {
    memset(X, 0, sizeof(X));
    for(int i = 0; i < m; ++i)
        if(A[i])
            for(int j = 0; j < m; ++j)
                X[i + j] += asInt64(A[i]) * B[j];
    for(int i = 2 * m; i >= m; --i) {
        X[i] %= mod;
        if(X[i])
            for(int j = 1; j <= m; ++j)
                X[i - j] += X[i];
    }
    for(int i = 0; i < m; ++i)
        A[i] = X[i] % mod;
}
int A[size], B[size];
int fooA(Int64 n, int m) {
    A[m != 1] = B[0] = 1;
    while(n) {
        if(n & 1)
            mul(m, B, A);
        n >>= 1;
        if(n)
            mul(m, A, A);
    }
    Int64 res = 0;
    for(int i = 0, j = 1; i < m; ++i, j = j * 2 % mod)
        res = (res + asInt64(B[i]) * j) % mod;
    return res;
}
int fac[mod], invFac[mod];
Int64 C(int n, int m) {
    return asInt64(fac[n]) * invFac[m] *
        invFac[n - m] % mod;
}
struct Comb {
    int a, b;
    Comb(Int64 x) : a(x / mod), b(x % mod) {}
    bool operator>=(const Comb& rhs) const {
        return a == rhs.a ? b >= rhs.b : a > rhs.a;
    }
    void operator-=(const Comb& rhs) {
        b -= rhs.b;
        if(b < 0)
            --a, b += mod;
        a -= rhs.a;
    }
    void operator++() {
        ++b;
        if(b == mod)
            b = 0, ++a;
    }
};
Int64 lucas(Comb n, Comb m) {
    int n1 = n.a % mod, m1 = m.a;
    int n2 = n.b, m2 = m.b;
    if(n1 < m1 || n2 < m2)
        return 0;
    return C(n1, m1) * C(n2, m2) % mod;
}
Int64 val[32];
Int64 calc(Comb n, Comb m) {
    Int64 rn = asInt64(n.a) * mod + n.b,
          rm = asInt64(m.a) * mod + m.b;
    for(int i = 0; i < 32; ++i) {
        val[i] = powm(2, rn + (32 - i) * (rm + 1));
        if((i & 1) && val[i])
            val[i] = mod - val[i];
    }
    Int64 res = 0;
    int cur = 0;
    for(Comb i = 0; n >= i;
        n -= m, ++i, cur = (cur + 1) & 31) {
        res += lucas(n, i) * val[cur];
        if(res >= end)
            res %= mod;
    }
    return res % mod;
}
int fooB(Int64 n, Int64 m) {
    fac[0] = 1;
    for(int i = 1; i < mod; ++i)
        fac[i] = asInt64(fac[i - 1]) * i % mod;
    invFac[0] = invFac[1] = 1;
    for(int i = 2; i < mod; ++i)
        invFac[i] = asInt64(mod - mod / i) *
            invFac[mod % i] % mod;
    for(int i = 1; i < mod; ++i)
        invFac[i] =
            asInt64(invFac[i - 1]) * invFac[i] % mod;
    return ((calc(n + 1, m) - calc(n, m)) % mod +
            mod) %
        mod;
}
int main() {
    Int64 n, m;
    scanf("%lld%lld", &n, &m);
    printf("%d\n",
           m <= 3000 ? fooA(n, m) : fooB(n, m));
    return 0;
}
