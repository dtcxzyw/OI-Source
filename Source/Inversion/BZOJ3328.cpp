#include <cstdio>
typedef long long Int64;
Int64 p;
struct Mat {
    Int64 A[2][2];
    Mat operator*(const Mat& rhs) const {
        Mat res;
        res.A[0][0] = (A[0][0] * rhs.A[0][0] +
                       A[0][1] * rhs.A[1][0]) %
            p;
        res.A[0][1] = (A[0][0] * rhs.A[0][1] +
                       A[0][1] * rhs.A[1][1]) %
            p;
        res.A[1][0] = (A[1][0] * rhs.A[0][0] +
                       A[1][1] * rhs.A[1][0]) %
            p;
        res.A[1][1] = (A[1][0] * rhs.A[0][1] +
                       A[1][1] * rhs.A[1][1]) %
            p;
        return res;
    }
};
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % p;
        k >>= 1, a = a * a % p;
    }
    return res;
}
Mat powm(Mat a, Int64 k) {
    Mat res;
    res.A[0][0] = res.A[1][1] = 1;
    res.A[0][1] = res.A[1][0] = 0;
    while(k) {
        if(k & 1)
            res = res * a;
        k >>= 1, a = a * a;
    }
    return res;
}
int calcG(int p) {
    int fac[70];
    int x = p - 1, fcnt = 0;
    for(int i = 2; i <= x; ++i)
        if(x % i == 0) {
            do
                x /= i;
            while(x % i == 0);
            fac[++fcnt] = i;
        }
    for(int i = 2; i < p; ++i) {
        bool flag = true;
        for(int j = 1; j <= fcnt; ++j)
            if(powm(i, p / fac[j]) == 1) {
                flag = false;
                break;
            }
        if(flag)
            return i;
    }
    return -1;
}
int solve(Int64 n, int k) {
    int g = calcG(p);
    Int64 base = powm(g, (p - 1) / k);
    Int64 invK = powm(k, p - 2);
    Int64 res = 0, cur = 1;
    for(int i = 0; i < k; ++i, cur = cur * base % p) {
        Mat A;
        A.A[0][0] = 1, A.A[0][1] = cur,
        A.A[1][0] = cur, A.A[1][1] = (cur + 1) % p;
        res = (res + powm(A, n).A[1][1]) % p;
    }
    return res * invK % p;
}
int main() {
    int t;
    scanf("%d", &t);
    for(int i = 0; i < t; ++i) {
        Int64 n;
        int k;
        scanf("%lld%d%lld", &n, &k, &p);
        printf("%d\n", solve(n, k));
    }
    return 0;
}
