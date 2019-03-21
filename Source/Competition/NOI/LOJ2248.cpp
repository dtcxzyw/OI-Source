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
typedef long long Int64;
Int64 x0, a, b, c, d;
int genRandom(int i) {
    x0 = ((a * x0 + b) % d * x0 + c) % d;
    return x0 % i + 1;
}
const int size = 5005;
int maxL[size], maxR[size];
void modify(int* A, int x, int n, int val) {
    while(x <= n) {
        if(A[x] < val)
            A[x] = val;
        else
            return;
        x += x & -x;
    }
}
bool query(int* A, int x, int end) {
    int res = 0;
    while(x) {
        res = std::max(res, A[x]);
        if(res >= end)
            return false;
        x -= x & -x;
    }
    return true;
}
int A[size * size], B[size * size], C[size * 2];
int main() {
    scanf("%lld%lld%lld%lld%lld", &x0, &a, &b, &c, &d);
    int n = read();
    int m = read();
    int q = read();
    int siz = n * m;
    for(int i = 1; i <= siz; ++i)
        A[i] = i;
    for(int i = 1; i <= siz; ++i)
        std::swap(A[i], A[genRandom(i)]);
    for(int i = 1; i <= q; ++i)
        std::swap(A[read()], A[read()]);
    for(int i = 1; i <= siz; ++i)
        B[A[i]] = i;
    int cnt = 0, end = n + m - 1;
    for(int i = 1;; ++i) {
        int pos = B[i];
        int x = (pos - 1) / m + 1,
            y = (pos - 1) % m + 1;
        if(query(maxL, x, y) &&
           query(maxR, n - x + 1, m - y + 1)) {
            C[++cnt] = i;
            if(cnt == end)
                break;
            if(x < n)
                modify(maxL, x + 1, n, y - 1);
            if(x > 1)
                modify(maxR, n - x + 2, n, m - y);
        }
    }
    for(int i = 1; i <= end; ++i)
        printf("%d ", C[i]);
    return 0;
}
