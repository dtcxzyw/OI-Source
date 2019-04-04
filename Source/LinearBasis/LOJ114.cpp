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
void print(Int64 x) {
    if(x >= 10)
        print(x / 10);
    putchar('0' + x % 10);
}
const int maxB = 50;
Int64 B[maxB + 5];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i) {
        Int64 x = read();
        for(int i = maxB; i >= 0; --i)
            if(x & (1LL << i)) {
                if(B[i])
                    x ^= B[i];
                else {
                    B[i] = x;
                    break;
                }
            }
    }
    for(int i = maxB; i >= 0; --i) {
        for(int j = i - 1; j >= 0; --j)
            if(B[i] & (1LL << j))
                B[i] ^= B[j];
    }
    int cnt = 0;
    for(int i = 0; i <= maxB; ++i)
        if(B[i])
            B[cnt++] = B[i];
    Int64 maxS = 1LL << cnt;
    int m = read();
    while(m--) {
        Int64 k = read() - (n != cnt);
        if(k < maxS) {
            Int64 res = 0;
            for(int i = 0; i < cnt; ++i)
                if(k & (1LL << i))
                    res ^= B[i];
            print(res);
            putchar('\n');
        } else
            puts("-1");
    }
    return 0;
}
