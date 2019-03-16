#include <cstdio>
namespace IO {
    const int size = 1 << 23;
    char buf[size], *S = buf;
    void init() {
        fread(buf, 1, size, stdin);
    }
    char getc() {
        return *S++;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 1000005, mod = 1000000007;
typedef long long Int64;
char buf[size];
int nxt[size], num[size];
int foo() {
    int len = 0, c;
    do
        c = IO::getc();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        buf[len++] = c;
        c = IO::getc();
    }
    buf[len] = '\0';
    Int64 res = 1;
    num[0] = 1, num[1] = 2;
    for(int i = 1, np = 2, j = 0, k = 0; i <= len;
        ++i, ++np) {
        while(j && buf[i] != buf[j])
            j = nxt[j];
        if(buf[i] == buf[j])
            ++j;
        nxt[np] = j;
        num[np] = num[j] + 1;
        while(k && buf[i] != buf[k])
            k = nxt[k];
        if(buf[i] == buf[k])
            ++k;
        int end = np >> 1;
        while(k > end)
            k = nxt[k];
        res = res * num[k] % mod;
    }
    return res;
}
int main() {
    IO::init();
    int n = read();
    for(int i = 1; i <= n; ++i)
        printf("%d\n", foo());
    return 0;
}
