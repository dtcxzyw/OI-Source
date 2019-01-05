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
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, int k, int mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
const int size = 1 << 14, mod = 1004535809;
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
    tot = n;
    Int64 base = powm(3, (mod - 1) / n, mod);
    Int64 invBase = powm(base, mod - 2, mod);
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
int C[size];
void mul(int n, int siz, int* A, const int* B) {
    NTT(siz, A, root);
    int* D;
    if(A == B)
        D = A;
    else {
        memcpy(C, B, sizeof(int) * n);
        memset(C + n, 0, sizeof(int) * (siz - n));
        NTT(siz, C, root);
        D = C;
    }
    for(int i = 0; i < siz; ++i)
        A[i] = asInt64(A[i]) * D[i] % mod;
    NTT(siz, A, invR);
    Int64 div = powm(siz, mod - 2, mod);
    for(int i = 0; i < n; ++i)
        A[i] = add(A[i], A[i + n]) * div % mod;
    memset(A + n, 0, sizeof(int) * (siz - n));
}
int fac[15];
int calcG(int p) {
    int phi = p - 1, fcnt = 0;
    for(int i = 2; i <= phi; ++i)
        if(phi % i == 0) {
            fac[++fcnt] = i;
            do
                phi /= i;
            while(phi % i == 0);
        }
    for(int g = 2;; ++g) {
        bool flag = true;
        for(int i = 1; i <= fcnt; ++i)
            if(powm(g, (p - 1) / fac[i], p) == 1) {
                flag = false;
                break;
            }
        if(flag)
            return g;
    }
    return -1;
}
int x2g[8005], A[size], B[size];
int main() {
    int n = read();
    int p = read();
    int x = read();
    int s = read();
    int g = calcG(p), phi = p - 1, cur = 1;
    for(int i = 0; i < phi; ++i) {
        x2g[cur] = i;
        cur = cur * g % p;
    }
    while(s--) {
        int x = read();
        if(x)
            ++A[x2g[x]];
    }
    int siz = 1;
    while(siz < (phi << 1))
        siz <<= 1;
    init(siz);
    B[0] = 1;
    while(n) {
        if(n & 1)
            mul(phi, siz, B, A);
        n >>= 1;
        mul(phi, siz, A, A);
    }
    printf("%d\n", B[x2g[x]]);
    return 0;
}
