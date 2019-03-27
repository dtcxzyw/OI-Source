#include <cstdio>
namespace IO {
    char in[1 << 24];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    int getc() {
        static char* S = in;
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
const int size = 100005, mod = 10000;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int S[size], nxt[size], pw[size], n;
void pre(int x) {
    static int cur = 0;
    while(cur < x) {
        ++cur;
        pw[cur] = pw[cur - 1] * n % mod;
    }
}
int foo() {
    int m = read();
    for(int i = 0; i < m; ++i)
        S[i] = read();
    nxt[1] = 0;
    for(int i = 1, j = 0; i < m; ++i) {
        while(j && S[j] != S[i])
            j = nxt[j];
        if(S[j] == S[i])
            ++j;
        nxt[i + 1] = j;
    }
    pre(m);
    int p = m, res = 0;
    while(p) {
        res = add(res, pw[p]);
        p = nxt[p];
    }
    return res;
}
int main() {
    IO::init();
    n = read() % mod;
    pw[0] = 1;
    int t = read();
    for(int i = 1; i <= t; ++i)
        printf("%04d\n", foo());
    return 0;
}
