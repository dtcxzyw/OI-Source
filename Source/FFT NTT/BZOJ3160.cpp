#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, int k, Int64 mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
namespace Conv {
    const int size = 1 << 18, mod = 998244353;
    int tot, root[size], invR[size];
    int add(int a, int b) {
        a += b;
        return a < mod ? a : a - mod;
    }
    int sub(int a, int b) {
        a -= b;
        return a >= 0 ? a : a + mod;
    }
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
    int cw[size];
    void NTT(int n, int* A, const int* w) {
        for(int i = 0, j = 0; i < n; ++i) {
            if(i < j)
                std::swap(A[i], A[j]);
            for(int l = n >> 1; (j ^= l) < l; l >>= 1)
                ;
        }
        for(int i = 2; i <= n; i <<= 1) {
            int m = i >> 1, fac = tot / i;
            for(int j = 0; j < m; ++j)
                cw[j] = w[j * fac];
            for(int j = 0; j < n; j += i)
                for(int k = 0; k < m; ++k) {
                    int &x = A[j + k],
                        &y = A[j + k + m];
                    int t = asInt64(y) * cw[k] % mod;
                    y = sub(x, t);
                    x = add(x, t);
                }
        }
    }
    int A[size];
    void selfConv(int n) {
        int p = 1;
        while(p <= n)
            p <<= 1;
        NTT(p, A, root);
        for(int i = 0; i < p; ++i)
            A[i] = asInt64(A[i]) * A[i] % mod;
        NTT(p, A, invR);
        Int64 div = powm(p, mod - 2, mod);
        for(int i = 1; i <= n; ++i)
            A[i] = A[i] * div % mod;
    }
}
const int maxn = 100005, mod = 1000000007;
char buf[maxn], bm[maxn * 2];
int R[maxn * 2];
int manacher(int n) {
    int cnt = 0;
    bm[cnt++] = '*';
    bm[cnt++] = '-';
    for(int i = 1; i <= n; ++i) {
        bm[cnt++] = buf[i];
        bm[cnt++] = '-';
    }
    int maxr = 0, mi = 0, res = 0;
    for(int i = 1; i < cnt; ++i) {
        R[i] = (maxr > i ?
                    std::min(maxr - i, R[2 * mi - i]) :
                    1);
        while(bm[i - R[i]] == bm[i + R[i]])
            ++R[i];
        if(maxr < i + R[i])
            maxr = i + R[i], mi = i;
        res += R[i] >> 1;
        if(res >= mod)
            res -= mod;
    }
    return res;
}
int C[maxn * 2], p2[maxn];
int main() {
    int c, n = 0;
    do
        c = getchar();
    while(c != 'a' && c != 'b');
    while(c == 'a' || c == 'b') {
        buf[++n] = c;
        c = getchar();
    }
    int end = n << 1, p = 1;
    while(p <= end)
        p <<= 1;
    Conv::init(p);
    for(int ch = 'a'; ch <= 'b'; ++ch) {
        memset(Conv::A, 0, sizeof(Conv::A));
        for(int i = 1; i <= n; ++i)
            Conv::A[i] = buf[i] == ch;
        Conv::selfConv(end);
        for(int i = 1; i <= end; ++i)
            C[i] += (Conv::A[i] + 1) >> 1;
    }
    int maxc = 0;
    for(int i = 1; i <= end; ++i)
        maxc = std::max(maxc, C[i]);
    p2[0] = 1;
    for(int i = 1; i <= maxc; ++i) {
        p2[i] = p2[i - 1] << 1;
        if(p2[i] >= mod)
            p2[i] -= mod;
    }
    int res = mod - end;
    for(int i = 1; i <= end; ++i) {
        res += p2[C[i]];
        if(res >= mod)
            res -= mod;
    }
    res = (res - manacher(n) + mod) % mod;
    printf("%d\n", res);
    return 0;
}
