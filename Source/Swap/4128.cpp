#include <cstdio>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
int p;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % p;
        k >>= 1, a = a * a % p;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < p ? a : a - p;
}
const int size = 55;
int m, res = 0, fac[size], cnt[size], A[size], gv[size][size],
       C[size][size], pmv[size * size], inv[size], invF[size];
void DFS(int c, int r) {
    if(r) {
        for(int i = A[c - 1]; i <= r; ++i) {
            A[c] = i;
            ++cnt[i];
            DFS(c + 1, r - i);
            --cnt[i];
        }
    } else {
        int sum = 0;
        Int64 k = 1;
        for(int i = 1; i < c; ++i) {
            int u = A[i];
            for(int j = i + 1; j < c; ++j)
                sum += gv[u][A[j]];
            sum += u >> 1;
            k = k * inv[u] % p;
        }
        for(int i = 1; i <= A[c - 1]; ++i)
            if(cnt[i])
                k = k * invF[cnt[i]] % p;
        res = (res + k * powm(m, sum)) % p;
    }
}
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    int n;
    scanf("%d%d%d", &n, &m, &p);
    fac[0] = invF[0] = C[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        fac[i] = asInt64(fac[i - 1]) * i % p;
        inv[i] = powm(i, p - 2);
        invF[i] = asInt64(invF[i - 1]) * inv[i] % p;
        C[i][0] = 1;
        for(int j = 1; j <= n; ++j) {
            gv[i][j] = gcd(i, j);
            C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
        }
    }
    int end = n * n;
    pmv[0] = 1;
    for(int i = 1; i <= end; ++i)
        pmv[i] = asInt64(pmv[i - 1]) * m % p;
    A[0] = 1;
    DFS(1, n);
    printf("%d\n", res);
    return 0;
}
