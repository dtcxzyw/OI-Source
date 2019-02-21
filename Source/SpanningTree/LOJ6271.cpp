#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 105, mod = 1000000007;
typedef long long Int64;
#define asInt64 static_cast<Int64>
const Int64 inv2 = (mod + 1) / 2, sqrt3 = 82062379,
            inv3 = (mod + 1) / 3;
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
struct Complex {
    int a, b;
    Complex() {}
    Complex(int a, int b) : a(a), b(b) {}
    Complex& operator+=(const Complex& rhs) {
        a = add(a, rhs.a);
        b = add(b, rhs.b);
        return *this;
    }
    Complex operator+(const Complex& rhs) const {
        Complex res = *this;
        return res += rhs;
    }
    Complex& operator-=(const Complex& rhs) {
        a = sub(a, rhs.a);
        b = sub(b, rhs.b);
        return *this;
    }
    Complex operator-(const Complex& rhs) const {
        Complex res = *this;
        return res -= rhs;
    }
    Complex& operator*=(const Complex& rhs) {
        int ca =
            (asInt64(a) * rhs.a - asInt64(b) * rhs.b) %
            mod;
        int cb =
            (asInt64(a) * rhs.b + asInt64(b) * rhs.a) %
            mod;
        a = (ca < 0 ? ca + mod : ca);
        b = cb;
        return *this;
    }
    Complex operator*(const Complex& rhs) const {
        Complex res = *this;
        return res *= rhs;
    }
    Complex inv() const {
        Int64 len =
            (asInt64(a) * a + asInt64(b) * b) % mod;
        Int64 norm = powm(len, mod - 2);
        return Complex(a * norm % mod,
                       (b ? mod - b : 0) * norm % mod);
    }
    Complex conj() const {
        return Complex(a, b ? mod - b : 0);
    }
    operator bool() const {
        return a | b;
    }
} w[3], invW[3];
const int maxB = 9;
struct Edge {
    int u, v, w;
} E[size * size];
int bin[maxB];
int getBit(int x, int i) {
    return x / bin[i] % 3;
}
Complex A[size][size];
Complex det(int n) {
    Complex res(1, 0);
    for(int i = 1; i < n; ++i) {
        int x = 0;
        for(int j = i; j < n; ++j)
            if(A[j][i]) {
                x = j;
                break;
            }
        if(x == 0)
            return Complex(0, 0);
        if(i != x) {
            for(int j = i; j < n; ++j)
                std::swap(A[i][j], A[x][j]);
            res.a = mod - res.a;
        }
        Complex div = A[i][i].inv();
        for(int j = i + 1; j < n; ++j) {
            Complex fac = A[j][i] * div;
            for(int k = i; k < n; ++k)
                A[j][k] -= A[i][k] * fac;
        }
    }
    for(int i = 1; i < n; ++i)
        res *= A[i][i];
    return res;
}
Int64 solve(int n, int m, int bit) {
    Complex c[3];
    for(int i = 0; i < 3; ++i) {
        memset(A, 0, sizeof(A));
        Complex r[3];
        r[0] = Complex(1, 0), r[1] = w[i],
        r[2] = w[i * 2 % 3];
        for(int j = 0; j < m; ++j) {
            int u = E[j].u;
            int v = E[j].v;
            int w = getBit(E[j].w, bit);
            A[u][u] += r[w];
            A[v][v] += r[w];
            A[u][v] -= r[w];
            A[v][u] -= r[w];
        }
        c[i] = det(n);
    }
    Complex d[3];
    d[0] = c[0] + c[1] + c[2];
    d[1] = c[0] + c[1] * invW[1] + c[2] * invW[2];
    d[2] = c[0] + c[1] * invW[2] + c[2] * invW[1];
    return inv3 * add(d[1].a, add(d[2].a, d[2].a)) %
        mod;
}
int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    int n = read();
    int m = read();
    int maxw = 0;
    for(int i = 0; i < m; ++i) {
        E[i].u = read();
        E[i].v = read();
        E[i].w = read();
        if(E[i].w > maxw)
            maxw = E[i].w;
    }
    bin[0] = 1;
    for(int i = 1; i < maxB; ++i)
        bin[i] = bin[i - 1] * 3;
    w[0] = Complex(1, 0);
    w[1] = Complex(mod - inv2, inv2 * sqrt3 % mod);
    w[2] = w[1].conj();
    for(int i = 0; i < 3; ++i)
        invW[i] = w[i].conj();
    Int64 res = 0;
    for(int i = 0; i < maxB && bin[i] <= maxw; ++i)
        res = (res + solve(n, m, i) * bin[i]) % mod;
    printf("%lld\n", res);
    return 0;
}
