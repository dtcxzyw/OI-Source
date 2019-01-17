#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
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
void NTT(int* A, int n, const int* w) {
    for(int i = 0, j = 0; i < n; ++i) {
        if(i < j)
            std::swap(A[i], A[j]);
        for(int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
    for(int i = 2; i <= n; ++i) {
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
    int a, b, *A;
    Poly(int n, int* A) : a(n), A(A) {}
    Poly(int a, int b) : a(a), b(b), A(0) {}
    void init(int* B, int siz) const {
        if(A) {
            int msiz = a + 1;
            memcpy(B, A, sizeof(int) * msiz);
            memset(B + msiz, 0,
                   sizeof(int) * (siz - msiz));
        } else {
            memset(B, 0, sizeof(int) * siz);
            B[0] = 1, B[a] = b;
        }
        NTT(B, siz, root);
    }
    void uninit() {
        delete A;
    }
    bool operator<(const Poly& rhs) const {
        return a > rhs.a;
    }
};
int A[size], B[size];
Int64 mul;
Poly operator*(const Poly& lhs, const Poly& rhs) {
    int end = lhs.a + rhs.a + 1;
    int siz = getSize(end);
    lhs.init(A, siz);
    rhs.init(B, siz);
    for(int i = 0; i < siz; ++i)
        A[i] = asInt64(A[i]) * B[i] % mod;
    NTT(A, siz, invR);
    Poly c(end - 1, new int[end]);
    memcpy(c.A, A, sizeof(int) * end);
    mul = mul * siz % mod;
}
Poly doMul(std::priority_queue<Poly>& que) {
    mul = 1;
    while(que.size() > 1) {
        Poly a = que.top();
        que.pop();
        Poly b = que.top();
        que.pop();
        que.push(a * b);
        a.uninit();
        b.uninit();
    }
    Poly p = que.top();
    Int64 div = powm(mul, mod - 2);
    for(int i = 0; i <= p.a; ++i)
        p.A[i] = p.A[i] * div % mod;
    return p;
}
std::pair<int, int> X[100005];
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        X[i].first = read();
        X[i].second = read();
    }
    std::sort(A + 1, A + n + 1);
    int siz = 0;
    for(int i = 1, l = 1; i <= n; ++i) {
        while(X[i].first != X[i + 1].first) {
            if(X[l].second == 0)
                X[++siz] =
                    std::make_pair(X[l].first, 0);
            else {
                ++siz;
                X[siz].first = X[l].first,
                X[siz].second = 0;
                for(int k = l; k <= i; ++k)
                    X[siz].second = add(X[siz].second,
                                        X[k].second);
            }
            l = i + 1;
        }
    }
    std::priority_queue<Poly> A, B;
    int minv = 1 << 30;
    for(int i = 1; i <= n; ++i) {
        int a = X[i].first;
        int b = X[i].second;
        if(b)
            A.push(Poly(a, b));
        else {
            minv = std::min(minv, a);
            B.push(Poly(a, 1));
        }
    }
    Poly p1 = doMul(A), p2 = doMul(B);
    int k = n / minv;
    while(k--) {
        if(k & 1) {
            Poly tmp = p1 * p2;
            p1.uninit();
            p1 = tmp;
        }
        k >>= 1;
    }
    return 0;
}
