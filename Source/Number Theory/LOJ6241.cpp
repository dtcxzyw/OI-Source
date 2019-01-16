#include <climits>
#include <cstdio>
typedef long long Int64;
const Int64 maxv = LLONG_MAX / 10;
const int mod = 998244353;
namespace IO {
    char buf[1 << 23], *cur;
    void init() {
        fread(buf, sizeof(buf), 1, stdin);
        cur = buf - 1;
    }
    int getc() {
        return *++cur;
    }
    Int64 read() {
        int c;
        do
            c = getc();
        while(c < '0' || c > '9');
        Int64 res = 0;
        while('0' <= c && c <= '9') {
            res = res * 10 + c - '0';
            if(res >= maxv)
                res %= mod;
            c = getc();
        }
        res %= mod;
        return res;
    }
}
int main() {
    IO::init();
    int t = IO::read();
    while(t--) {
        Int64 res = IO::read();
        printf("%lld\n", res * (res + 1) / 2 % mod);
    }
    return 0;
}
