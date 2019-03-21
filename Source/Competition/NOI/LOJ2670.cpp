#include <cstring>
#include <iostream>
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 m;
Int64 addm(Int64 a, Int64 b) {
    a += b;
    return a < m ? a : a - m;
}
Int64 mulm(Int64 a, Int64 b) {
    Int64 res =
        (a * b -
         static_cast<Int64>(
             static_cast<long double>(a) / m * b) *
             m) %
        m;
    return res < 0 ? res + m : res;
}
Int64 powm(Int64 a, Int64 k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = mulm(res, a);
        k >>= 1, a = mulm(a, a);
    }
    return res;
}
struct Mat {
    Int64 A[2][2];
    Mat operator*(const Mat& rhs) const {
        Mat res;
        res.A[0][0] = addm(mulm(A[0][0], rhs.A[0][0]),
                           mulm(A[0][1], rhs.A[1][0]));
        res.A[0][1] = addm(mulm(A[0][0], rhs.A[0][1]),
                           mulm(A[0][1], rhs.A[1][1]));
        res.A[1][0] = addm(mulm(A[1][0], rhs.A[0][0]),
                           mulm(A[1][1], rhs.A[1][0]));
        res.A[1][1] = addm(mulm(A[1][0], rhs.A[0][1]),
                           mulm(A[1][1], rhs.A[1][1]));
        return res;
    }
};
Int64 sum(Int64 a, Int64 n) {
    Mat A, B;
    A.A[0][0] = A.A[0][1] = 1,
    A.A[1][0] = A.A[1][1] = 0;
    B.A[0][0] = B.A[0][1] = a, B.A[1][0] = 0,
    B.A[1][1] = 1;
    --n;
    while(n) {
        if(n & 1)
            A = A * B;
        n >>= 1, B = B * B;
    }
    return A.A[0][1];
}
int main() {
    Int64 a, c, x0, n, g;
    std::cin >> m >> a >> c >> x0 >> n >> g;
    a %= m, c %= m, x0 %= m;
    Int64 apn = powm(a, n);
    Int64 A = mulm(apn, x0);
    Int64 B = mulm(c, sum(a, n));
    printf("%lld\n", (A + B) % m % g);
    return 0;
}
