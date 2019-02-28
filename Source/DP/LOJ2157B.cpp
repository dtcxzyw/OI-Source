#include <algorithm>
#include <cmath>
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
const int size = 500005;
int A[size];
typedef double FT;
FT fsqrt[size];
inline FT calcF(int i, int j) {
    return A[j] + fsqrt[i - j];
}
int n;
FT B[size];
void dp(int l, int r, int b, int e) {
    if(l > r)
        return;
    int m = (l + r) >> 1;
    FT maxv = 0.0, end = std::min(e, m), pos = m;
    for(int i = b; i <= end; ++i) {
        FT val = calcF(m, i);
        if(val > maxv)
            maxv = val, pos = i;
    }
    B[m] = std::max(B[m], maxv);
    dp(l, m - 1, b, pos);
    dp(m + 1, r, pos, e);
}
int main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i)
        fsqrt[i] = sqrt(i);
    dp(1, n, 1, n);
    std::reverse(A + 1, A + n + 1);
    std::reverse(B + 1, B + n + 1);
    dp(1, n, 1, n);
    for(int i = n; i >= 1; --i)
        printf("%d\n",
               static_cast<int>(ceil(B[i])) - A[i]);
    return 0;
}
