#include <algorithm>
#include <cstdio>
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
const int size = 2000005;
const Int64 inf = 1LL << 60;
Int64 A[size], sum[size];
int q[size];
int main() {
    int n = read();
    Int64 p = read(), csum = 0;
    int d = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + A[i];
    for(int i = n; i >= 1; --i)
        sum[i] = sum[i] - (i > d ? sum[i - d] : 0);
    int l = 1, b = 1, e = 0, maxl = 0;
    for(int r = 1; r <= n; ++r) {
        csum += A[r];
        while(b <= e && sum[r] >= sum[q[e]])
            --e;
        q[++e] = r;
        while(b <= e && csum - sum[q[b]] > p) {
            csum -= A[l++];
            while(b <= e && q[b] - d + 1 < l)
                ++b;
        }
        maxl = std::max(maxl, r - l + 1);
    }
    printf("%d\n", maxl);
    return 0;
}
