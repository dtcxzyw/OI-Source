#include <algorithm>
#include <cstdio>
typedef unsigned long long Int64;
Int64 mod;
struct Vec {
    Int64 s, c;
    Vec(Int64 s, Int64 c) : s(s), c(c) {}
};
struct Mat {
    Int64 A00, A01, A02, A12;
    Mat(Int64 A00, Int64 A01, Int64 A02, Int64 A12)
        : A00(A00), A01(A01), A02(A02), A12(A12) {}
    Mat operator*(const Mat& rhs) const {
        return Mat(
            A00 * rhs.A00 % mod,
            (A00 * rhs.A01 + A01) % mod,
            (A00 * rhs.A02 + A01 * rhs.A12 + A02) %
                mod,
            (A12 + rhs.A12) % mod);
    }
    Vec operator*(const Vec& rhs) const {
        return Vec((A00 * rhs.s + A01 * rhs.c + A02) %
                       mod,
                   (A12 + rhs.c) % mod);
    }
};
int main() {
    Int64 n;
    scanf("%llu%llu", &n, &mod);
    Vec res(0, 0);
    for(Int64 i = 1; i <= n; i *= 10) {
        Int64 end = std::min(n, i * 10 - 1);
        Int64 k = end - i + 1;
        Mat base(i * 10 % mod, 1, 1, 1);
        while(k) {
            if(k & 1)
                res = base * res;
            k >>= 1, base = base * base;
        }
    }
    printf("%llu\n", res.s);
    return 0;
}
