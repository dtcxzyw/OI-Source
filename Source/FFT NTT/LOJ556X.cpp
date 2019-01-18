#include <algorithm>
#include <cstdio>
#include <cstring>
#include <memory>
#include <queue>
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
const int size = 1 << 18, mod = 998244353;
using Int64 = long long;
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
void NTT(int* A, int n, const int* w) {
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
struct Poly {
    int a, b;
    std::vector<int> A;
    Int64 mul;
    Poly(int n, const int* data, Int64 mul)
        : a(n), mul(mul) {
        A.assign(data, data + n + 1);
    }
    Poly(int a, int b) : a(a), b(b), A(0), mul(1) {}
    void init(int* B, int siz) const {
        if(A.size()) {
            int msiz = a + 1;
            memcpy(B, A.data(), sizeof(int) * msiz);
            memset(B + msiz, 0,
                   sizeof(int) * (siz - msiz));
        } else {
            memset(B, 0, sizeof(int) * siz);
            B[0] = 1;
            B[a] = add(B[a], b);
        }
        NTT(B, siz, root);
    }
    bool operator<(const Poly& rhs) const {
        return a > rhs.a;
    }
    void print(int n) {
        Int64 div = powm(mul, mod - 2);
        for(int i = 1; i <= a; ++i) {
            int res = A[i] * div % mod;
            printf("%d\n", res);
        }
        for(int i = a + 1; i <= n; ++i)
            puts("0");
    }
    void load(int n) {
        if(A.empty()) {
            A.resize(n + 1);
            A[0] = 1;
            A[a] = add(A[a], b);
        } else {
            Int64 div = powm(mul, mod - 2);
            for(int i = 0; i <= a; ++i)
                A[i] = A[i] * div % mod;
            A.resize(n + 1);
        }
    }
};
using SharedPoly = std::shared_ptr<Poly>;
int A[size], B[size];
SharedPoly doMul(const SharedPoly& lhs,
                 const SharedPoly& rhs, int modv) {
    int end = std::min(lhs->a + rhs->a, modv);
    int siz = getSize(lhs->a + rhs->a + 1);
    lhs->init(A, siz);
    if(lhs != rhs) {
        rhs->init(B, siz);
        for(int i = 0; i < siz; ++i)
            A[i] = asInt64(A[i]) * B[i] % mod;
    } else {
        for(int i = 0; i < siz; ++i)
            A[i] = asInt64(A[i]) * A[i] % mod;
    }
    NTT(A, siz, invR);
    return std::make_shared<Poly>(
        end, A, siz * lhs->mul % mod * rhs->mul % mod);
}
SharedPoly doMul(std::priority_queue<SharedPoly>& que,
                 int modv) {
    if(que.empty())
        return std::make_shared<Poly>(0, 0);
    while(que.size() > 1) {
        SharedPoly a = que.top();
        que.pop();
        SharedPoly b = que.top();
        que.pop();
        que.push(doMul(a, b, modv));
    }
    return que.top();
}
using PolyData = std::vector<int>;
void inv(int n, const PolyData& sf, PolyData& g) {
    if(n == 1)
        g[0] = powm(sf[0], mod - 2);
    else {
        int h = (n + 1) >> 1;
        inv(h, sf, g);
        int siz = getSize(n * 2);
        PolyData f(siz);
        memcpy(f.data(), sf.data(), sizeof(int) * n);
        NTT(f.data(), siz, root);
        NTT(g.data(), siz, root);
        for(int i = 0; i < siz; ++i) {
            g[i] = (2 - asInt64(f[i]) * g[i] % mod) *
                g[i] % mod;
            if(g[i] < 0)
                g[i] += mod;
        }
        NTT(g.data(), siz, invR);
        Int64 div = powm(siz, mod - 2);
        for(int i = 0; i < n; ++i)
            g[i] = g[i] * div % mod;
        memset(g.data() + n, 0,
               sizeof(int) * (siz - n));
    }
}
int main() {
    int n = read();
    int m = read();
    init(getSize((n + 1) * 2));
    std::priority_queue<SharedPoly> qA, qB;
    int minv = 1 << 30;
    while(m--) {
        int a = read();
        int b = read();
        if(a > n)
            continue;
        if(b)
            qA.push(std::make_shared<Poly>(a, b));
        else {
            minv = std::min(minv, a);
            qB.push(
                std::make_shared<Poly>(a, mod - 1));
        }
    }
    SharedPoly p1 = doMul(qA, n), p2 = doMul(qB, n);
    std::vector<int> invp(tot);
    p2->load(n);
    inv(n + 1, p2->A, invp);
    SharedPoly p3 =
        std::make_shared<Poly>(n, invp.data(), 1);
    doMul(p1, p3, n)->print(n);
    return 0;
}
