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
const int size = 100005;
int h[20][size], lg2[size];
int query(int l, int r) {
    int p = lg2[r - l + 1];
    return std::max(h[p][l], h[p][r - (1 << p) + 1]);
}
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        h[0][i] = read();
    for(int i = 2; i <= n; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    for(int i = 1; i < 20; ++i) {
        int off = 1 << (i - 1), end = n - (1 << i) + 1;
        for(int j = 1; j <= end; ++j)
            h[i][j] = std::max(h[i - 1][j],
                               h[i - 1][j + off]);
    }
    int k = sqrt(n) + 1;
    for(int i = 1; i <= n; ++i) {
        int maxh = h[0][i];
        for(int j = 1; j <= k; ++j) {
            int l = i - (j - 1) * (j - 1),
                ll = i - j * j;
            if(l > 1)
                maxh = std::max(
                    maxh,
                    query(std::max(ll, 1), l - 1) + j);
        }
        for(int j = 1; j <= k; ++j) {
            int r = i + (j - 1) * (j - 1),
                rr = i + j * j;
            if(r < n)
                maxh = std::max(
                    maxh,
                    query(r + 1, std::min(rr, n)) + j);
        }
        printf("%d\n", maxh - h[0][i]);
    }
    return 0;
}
