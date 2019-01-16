#include <algorithm>
#include <cstdio>
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
const int mod = 1000000007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
typedef long long Int64;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int A[1 << 22];
#define FWTBegin                         \
    for(int i = 2; i <= n; i <<= 1) {    \
        int m = i >> 1;                  \
        for(int j = 0; j < n; j += i)    \
            for(int k = 0; k < m; ++k) { \
                int &x = A[j + k], &y = A[j + k + m];

#define FWTEnd \
    }          \
    }

void FWT(int n) {
    FWTBegin x = add(x, y);
    FWTEnd
}
void IFWT(int n) {
    FWTBegin x = sub(x, y);
    FWTEnd
}
const int size = 1000005;
int p[80000], powk[size];
bool flag[size];
void pre(int n, int k) {
    powk[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            powk[i] = powm(i, k);
        }
        Int64 pki = powk[i];
        for(int j = 1; j <= pcnt && p[j] * i <= n;
            ++j) {
            int val = p[j] * i;
            flag[val] = true;
            powk[val] = powk[p[j]] * pki % mod;
            if(i % p[j] == 0)
                break;
        }
    }
}
int main() {
    int n = read();
    int m = read();
    int k = read();
    for(int i = 0; i < m; ++i)
        ++A[read()];
    int end = 1 << n;
    FWT(end);
    pre(m, k);
    for(int i = 0; i < end; ++i)
        A[i] = powk[A[i]];
    IFWT(end);
    Int64 res = (powm(m, k) - A[0] + mod) % mod;
    printf("%lld\n", res);
    return 0;
}
