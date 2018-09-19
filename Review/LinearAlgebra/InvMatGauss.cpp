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
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 405, mod = 1000000007;
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
int A[size][size], P[size][size], B[size][size];
bool gauss(int n) {
    for(int i = 1; i <= n; ++i) {
        int x = 0;
        for(int j = i; j <= n; ++j)
            if(A[j][i]) {
                x = i;
                break;
            }
        if(x == 0)
            return false;
        if(x != i) {
            for(int j = i; j <= n; ++j)
                std::swap(A[i][j], A[x][j]);
            for(int j = 1; j <= n; ++j)
                std::swap(P[i][j], P[x][j]);
        }
        Int64 invi = inv(A[i][i]);
        for(int j = i + 1; j <= n; ++j) {
            Int64 fac = A[j][i] * invi % mod;
            for(int k = i; k <= n; ++k)
                A[j][k] =
                    (A[j][k] - A[i][k] * fac) % mod;
            for(int k = 1; k <= n; ++k)
                P[j][k] =
                    (P[j][k] - P[i][k] * fac) % mod;
        }
    }
    return true;
}
const Int64 limit = std::numeric_limits<Int64>::max() -
    asInt64(mod) * mod;
bool needMod(Int64 x) {
    x = (x >= 0 ? x : -x);
    return x >= limit;
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            A[i][j] = read();
    for(int i = 1; i <= n; ++i)
        P[i][i] = 1;
    if(gauss(n)) {
        for(int i = 1; i <= n; ++i) {
            for(int j = n; j >= 1; --j) {
                Int64 sum = P[j][i];
                for(int k = j + 1; k <= n; ++k) {
                    sum -= asInt64(A[j][k]) * B[k][i];
                    if(needMod(sum))
                        sum %= mod;
                }
                B[j][i] =
                    sum % mod * inv(A[j][j]) % mod;
            }
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                int res = B[i][j];
                printf("%d ",
                       res >= 0 ? res : res + mod);
            }
            putchar('\n');
        }
    } else
        puts("No Solution");
    return 0;
}
