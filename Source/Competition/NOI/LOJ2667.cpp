#include <cstdio>
namespace IO {
    const int size = 1 << 22;
    char buf[size];
    void init() {
        fread(buf, 1, size, stdin);
    }
    char getc() {
        static char* S = buf;
        return *S++;
    }
}
const int mod = 1000000007, phi = mod - 1;
typedef long long Int64;
struct Info {
    Int64 a, b;
    Info(Int64 a, Int64 b) : a(a), b(b) {}
    Int64 operator()(Int64 x) const {
        return (a * x + b) % mod;
    }
};
Info readPow() {
    Int64 resA = 0, resB = 0;
    int c;
    bool flag = false;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        resA = resA * 10LL + c - '0';
        if(resA >= phi + 1)
            resA %= phi, flag = true;
        resB = (resB * 10LL + c - '0') % mod;
        c = IO::getc();
    }
    resA %= phi;
    if(--resA == -1)
        resA += phi;
    if(--resB == -1)
        resB += mod;
    return Info(resA + (flag ? phi : 0), resB);
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
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
Info trans(const Info& p, int a, int b) {
    if(a == 0)
        return Info(p.a == 0, b);
    if(a == 1)
        return Info(1, b * p.b % mod);
    Int64 pa = powm(a, p.a);
    Int64 fac = (pa - 1) * powm(a - 1, mod - 2) % mod;
    if(fac < 0)
        fac += mod;
    return Info(pa, fac * b % mod);
}
int main() {
    IO::init();
    Info pn = readPow();
    Info pm = readPow();
    int a = read();
    int b = read();
    int c = read();
    int d = read();
    Info transA = trans(pm, a, b);
    Info transB = trans(pn, transA.a * c % mod,
                        (transA.b * c + d) % mod);
    printf("%lld\n", transA(transB(1)));
    return 0;
}
