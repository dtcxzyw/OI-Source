#include <climits>
#include <cstdio>
#include <cstring>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
#define asInt64 static_cast<Int64>
const int maxk = 105, mod = 1000000007;
const Int64 end =
    LLONG_MAX - asInt64(mod - 1) * (mod - 1);
struct Mat {
    Int64 A[maxk][maxk];
    int n, m;
    Mat(int n, int m) : n(n), m(m) {
        memset(A, 0, sizeof(A));
    }
    Int64* operator[](int id) {
        return A[id];
    }
    const Int64* operator[](int id) const {
        return A[id];
    }
    Mat operator*(const Mat& rhs) const {
        Mat res(n, rhs.m);
        for(int i = 0; i < n; ++i)
            for(int k = 0; k < m; ++k) {
                Int64 mul = A[i][k];
                for(int j = 0; j < rhs.m; ++j) {
                    res[i][j] += mul * rhs[k][j];
                    if(res[i][j] > end)
                        res[i][j] %= mod;
                }
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < rhs.m; ++j)
                res[i][j] %= mod;
        return res;
    }
};
Int64 val[maxk];
const int mask = (1 << 16) - 1;
int cnt[1 << 16];
void init() {
    for(int i = 0; i <= mask; ++i)
        cnt[i] = cnt[i >> 1] + (i & 1);
}
bool scan(Int64 val) {
    return (cnt[val & mask] + cnt[(val >> 16) & mask] +
            cnt[(val >> 32) & mask] +
            cnt[(val >> 48) & mask]) %
        3 ==
        0;
}
int main() {
    int n = read();
    Int64 d = read() - 1;
    for(int i = 0; i < n; ++i)
        val[i] = read();
    init();
    Mat res(1, n), trans(n, n);
    for(int i = 0; i < n; ++i) {
        res[0][i] = 1;
        for(int j = 0; j <= i; ++j)
            trans[j][i] = trans[i][j] =
                scan(val[i] ^ val[j]);
    }
    while(d) {
        if(d & 1)
            res = res * trans;
        d >>= 1, trans = trans * trans;
    }
    Int64 ans = 0;
    for(int i = 0; i < n; ++i)
        ans = (ans + res[0][i]) % mod;
    printf("%lld\n", ans);
    return 0;
}
