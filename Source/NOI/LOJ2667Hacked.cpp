#include <algorithm>
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
std::pair<Int64, Int64> readPow() {
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
    return std::make_pair(
        resA + (flag ? 2LL * phi : 0), resB);
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
struct Mat {
    Int64 A00, A01, A10, A11;
    Mat(Int64 A00, Int64 A01, Int64 A10, Int64 A11)
        : A00(A00), A01(A01), A10(A10), A11(A11) {}
    Mat operator*(const Mat& rhs) const {
        return Mat(
            (A00 * rhs.A00 + A01 * rhs.A10) % mod,
            (A00 * rhs.A01 + A01 * rhs.A11) % mod,
            (A10 * rhs.A00 + A11 * rhs.A10) % mod,
            (A10 * rhs.A01 + A11 * rhs.A11) % mod);
    }
};
int main() {
    IO::init();
    std::pair<Int64, Int64> pn = readPow();
    std::pair<Int64, Int64> pm = readPow();
    int a = read();
    int b = read();
    int c = read();
    int d = read();
    Int64 n = c != 1 ? pn.first : pn.second,
          m = a != 1 ? pm.first : pm.second;
    Mat A(1, 0, 0, 1), B(a, 0, b, 1);
    while(m) {
        if(m & 1)
            A = A * B;
        m >>= 1, B = B * B;
    }
    Mat C(1, 1, 0, 0), D = A * Mat(c, 0, d, 1);
    while(n) {
        if(n & 1)
            C = C * D;
        n >>= 1, D = D * D;
    }
    C = C * A;
    printf("%lld\n", C.A00);
    return 0;
}
