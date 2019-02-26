#include <climits>
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
const int maxn = 1005, maxk = 25, mod = 1000000007;
typedef long long Int64;
#define asInt64 static_cast<Int64>
const Int64 end =
    LLONG_MAX - asInt64(mod - 1) * (mod - 1);
struct Mat {
    Int64 A[maxk][maxk];
    int n;
    Mat(int n) : n(n) {
        memset(A, 0, sizeof(A));
    }
    const Int64* operator[](int id) const {
        return A[id];
    }
    Int64* operator[](int id) {
        return A[id];
    }
    Mat operator*(const Mat& rhs) const {
        Mat res(n);
        for(int i = 0; i <= n; ++i)
            for(int k = 0; k <= n; ++k) {
                Int64 mul = A[i][k];
                if(mul == 0)
                    continue;
                for(int j = 0; j <= n; ++j) {
                    res[i][j] += mul * rhs[k][j];
                    if(res[i][j] > end)
                        res[i][j] %= mod;
                }
            }
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= n; ++j)
                res[i][j] %= mod;
        return res;
    }
};
Mat powm(Mat A, int k) {
    Mat res(A.n);
    for(int i = 0; i <= A.n; ++i)
        res[i][i] = 1;
    while(k) {
        if(k & 1)
            res = res * A;
        k >>= 1, A = A * A;
    }
    return res;
}
int out[maxn][maxk], in[maxk][maxn];
Mat buildMat(int N, int K) {
    Mat res(K);
    for(int i = 0; i <= K; ++i)
        for(int k = 0; k <= N; ++k) {
            Int64 mul = in[i][k];
            if(mul == 0)
                continue;
            for(int j = 0; j <= K; ++j) {
                res[i][j] += mul * out[k][j];
                if(res[i][j] > end)
                    res[i][j] %= mod;
            }
        }
    for(int i = 0; i <= K; ++i)
        for(int j = 0; j <= K; ++j)
            res[i][j] %= mod;
    return res;
}
int main() {
    int n = read();
    int k = read();
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= k; ++j)
            out[i][j] = read() % mod;
        for(int j = 1; j <= k; ++j)
            in[j][i] = read() % mod;
    }
    int m = read();
    in[0][0] = out[0][0] = 1;
    for(int t = 0; t < m; ++t) {
        int u = read();
        int v = read();
        int d = read();
        if(d == 0)
            puts(u == v ? "1" : "0");
        else if(d == 1) {
            Int64 res = u == v;
            for(int i = 1; i <= k; ++i)
                res = (res +
                       asInt64(out[u][i]) * in[i][v]) %
                    mod;
            printf("%lld\n", res);
        } else {
            out[v][0] = 1;
            Mat base = buildMat(n, k);
            Mat pwb = powm(base, d);
            Int64 res = 0;
            for(int i = 0; i <= k; ++i)
                res =
                    (res +
                     asInt64(out[u][i]) * pwb[i][0]) %
                    mod;
            printf("%lld\n", res);
            out[v][0] = 0;
        }
    }
    return 0;
}
