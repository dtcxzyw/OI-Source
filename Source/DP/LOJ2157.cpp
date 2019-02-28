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
int getEdge(int x, int y) {
    int l = y, r = n + 1, res = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(calcF(m, x) >= calcF(m, y))
            res = m, l = m + 1;
        else
            r = m - 1;
    }
    return res + 1;
}
int B[size], k[size], q[size];
void dp() {
    int b = 1, e = 1;
    q[1] = 1;
    for(int i = 2; i <= n; ++i) {
        while(b < e && k[b] <= i)
            ++b;
        B[i] = std::max(B[i], static_cast<int>(ceil(
                                  calcF(i, q[b]))));
        while(b < e && k[e - 1] >= getEdge(q[e], i))
            --e;
        k[e] = getEdge(q[e], i);
        q[++e] = i;
    }
}
int main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i)
        fsqrt[i] = sqrt(i);
    dp();
    std::reverse(A + 1, A + n + 1);
    std::reverse(B + 1, B + n + 1);
    dp();
    for(int i = n; i >= 1; --i)
        printf("%d\n", std::max(B[i] - A[i], 0));
    return 0;
}
