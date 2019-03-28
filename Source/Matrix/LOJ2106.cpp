#include <cstdio>
typedef unsigned long long Int64;
const Int64 mod = 7528443412579576937;
Int64 add(Int64 a, Int64 b) {
    a += b;
    return a < mod ? a : a - mod;
}
Int64 mulm(Int64 a, Int64 k) {
    Int64 res = 0;
    while(k) {
        if(k & 1)
            res = add(res, a);
        k >>= 1, a = add(a, a);
    }
    return res;
}
struct Mat {
    Int64 A00, A01, A10, A11;
    Mat(Int64 A00, Int64 A01, Int64 A10, Int64 A11)
        : A00(A00), A01(A01), A10(A10), A11(A11) {}
    Mat operator*(const Mat& rhs) const {
        return Mat(add(mulm(A00, rhs.A00),
                       mulm(A01, rhs.A10)),
                   add(mulm(A00, rhs.A01),
                       mulm(A01, rhs.A11)),
                   add(mulm(A10, rhs.A00),
                       mulm(A11, rhs.A10)),
                   add(mulm(A10, rhs.A01),
                       mulm(A11, rhs.A11)));
    }
};
int main() {
    Int64 b, d, n;
    scanf("%llu%llu%llu", &b, &d, &n);
    if(n) {
        bool flag = n & 1;
        Int64 c = (d - b * b) / 4;
        Mat res(add(2 * c, b * b), b, b, 2),
            trans(b, 1, c, 0);
        while(n) {
            if(n & 1)
                res = res * trans;
            n >>= 1, trans = trans * trans;
        }
        Int64 ans = res.A11;
        if(c && !flag) {
            if(ans == 0)
                ans = mod - 1;
            else
                --ans;
        }
        printf("%llu\n", ans);
    } else
        puts("1");
    return 0;
}
