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
typedef long long Int64;
const int size = 1 << 22, mod = 998244353;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int A[size], C[2][23], D[1 << 17 | 1];
bool B[size];
int main() {
    int n = read();
    int m = read();
    int k = read();
    for(int i = 0; i < m; ++i)
        ++A[read()];
    int end = 1 << n;
    for(int i = 1; i < end; i <<= 1)
        for(int j = 0; j < end; ++j)
            if(j & i)
                A[j] = add(A[j], A[j ^ i]);
    B[0] = n & 1;
    for(int i = 1; i < end; ++i)
        B[i] = B[i >> 1] ^ (i & 1);
    C[0][0] = 1;
    D[0] = 1;
    for(int i = 1; i <= m; ++i) {
        int c = i & 1, l = c ^ 1, sum = 1;
        C[c][0] = 1;
        for(int j = 1; j <= k; ++j) {
            C[c][j] = add(C[l][j - 1], C[l][j]);
            sum = add(sum, C[c][j]);
        }
        D[i] = sum;
    }
    Int64 ans = 0;
    for(int i = 0; i < end; ++i) {
        int val = D[A[i]];
        if(B[i])
            ans -= val;
        else
            ans += val;
    }
    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
    return 0;
}
