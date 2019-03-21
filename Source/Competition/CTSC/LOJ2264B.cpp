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
const int size = 1 << 9, mask = size - 1,
          mod = 1000000007;
typedef long long Int64;
Int64 LUT[size][size];
int main() {
    int n = read();
    Int64 res = 0;
    for(int i = 1; i <= n; ++i) {
        int A = read();
        int hb = A >> 9, lb = A & mask;
        Int64 dpv = 0;
        for(int j = lb; j <= mask; j = (j + 1) | lb)
            dpv += LUT[hb][j];
        res += dpv;
        ++dpv;
        for(int j = hb; j; j = (j - 1) & hb)
            LUT[j][lb] += dpv;
        LUT[0][lb] += dpv;
    }
    printf("%lld\n", res % mod);
    return 0;
}
