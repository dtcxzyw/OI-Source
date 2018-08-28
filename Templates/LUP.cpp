#include <algorithm>
#include <cstdio>
#include <limits>
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
const int size = 405, mod = 1000000007;
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
Int64 inv(Int64 a) {
    Int64 res = 1;
    int k = mod - 2;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int A[size][size], P[size];
bool LUP(int n) {
    for(int i = 1; i <= n; ++i)
        P[i] = i;
    for(int i = 1; i <= n; ++i) {
        int x = 0;
        for(int j = i; j <= n; ++j)
            if(A[i][j]) {
                x = j;
                break;
            }
        if(x == 0)
            return false;
        if(i != x) {
            std::swap(P[i], P[x]);
            for(int j = 1; j <= n; ++j)
                std::swap(A[i][j], A[x][j]);
        }
        Int64 fac = inv(A[i][i]);
        for(int j = i + 1; j <= n; ++j) {
            A[j][i] = A[j][i] * fac % mod;
            Int64 mul = A[j][i];
            for(int k = i + 1; k <= n; ++k)
                A[j][k] = (A[j][k] - mul * A[i][k]) % mod;
        }
    }
    return true;
}
const Int64 limit =
    std::numeric_limits<Int64>::max() - asInt64(mod) * mod;
bool needMod(Int64 x) {
    x = (x >= 0 ? x : -x);
    return x >= limit;
}
int B[size][size], C[size], D[size];
void solve(int n, int m) {
    for(int i = 1; i <= n; ++i) {
        Int64 sum = (P[i] == m ? 1 : 0);
        for(int j = 1; j < i; ++j) {
            sum -= asInt64(A[i][j]) * C[j];
            if(needMod(sum))
                sum %= mod;
        }
        C[i] = sum % mod;
    }
    for(int i = n; i >= 1; --i) {
        Int64 sum = C[i];
        for(int j = i + 1; j <= n; ++j) {
            sum -= asInt64(A[i][j]) * D[j];
            if(needMod(sum))
                sum %= mod;
        }
        sum %= mod;
        D[i] = sum * inv(A[i][i]) % mod;
    }
    for(int i = 1; i <= n; ++i)
        B[i][m] = D[i];
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            A[i][j] = read();
    if(LUP(n)) {
        for(int i = 1; i <= n; ++i)
            solve(n, i);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                int val = B[i][j];
                printf("%d ", val >= 0 ? val : val + mod);
            }
            putchar('\n');
        }
    } else
        puts("No Solution");
    return 0;
}
