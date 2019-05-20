#include <algorithm>
#include <cmath>
#include <iostream>
typedef float FT __attribute__((mode(TF)));
const FT epsA = 1e-10, epsB = 1e-20, epsC = 1e-30,
         zero = 0, one = 1;
FT mabs(FT val) {
    return val >= zero ? val : -val;
}
const int size = 25;
FT A[size][size];
int idn[size], idm[size], n, m;
void pivot(int l, int e) {
    std::swap(idm[l], idn[e]);
    FT fac = A[l][e];
    A[l][e] = one;
    for(int i = 0; i <= n; ++i)
        A[l][i] /= fac;
    for(int i = 0; i <= m; ++i)
        if(i != l) {
            FT k = A[i][e];
            A[i][e] = zero;
            for(int j = 0; j <= n; ++j)
                A[i][j] -= k * A[l][j];
        }
}
bool init() {
    idm[0] = idn[0] = 1 << 30;
    while(true) {
        int l = 0;
        for(int i = 1; i <= m; ++i)
            if(A[i][0] < -epsA && idm[i] < idm[l])
                l = i;
        if(l == 0)
            return true;
        int e = 0;
        for(int i = 1; i <= n; ++i)
            if(A[l][i] < -epsA && idn[i] < idn[e])
                e = i;
        if(e == 0)
            return false;
        pivot(l, e);
    }
}
bool simplex() {
    if(!init()) {
        std::cout << "Infeasible" << std::endl;
        return false;
    }
    while(true) {
        int e = 0;
        for(int i = 1; i <= n; ++i)
            if(A[0][i] > epsB && idn[i] < idn[e])
                e = i;
        if(e == 0)
            break;
        FT minv = 1e200;
        int l = 0;
        for(int i = 1; i <= m; ++i)
            if(A[i][e] > epsB) {
                FT val = A[i][0] / A[i][e];
                if(l == 0 || val < minv ||
                   (mabs(val - minv) < epsC &&
                    idm[i] < idm[l]))
                    minv = val, l = i;
            }
        if(l == 0) {
            std::cout << "Unbounded" << std::endl;
            return false;
        }
        pivot(l, e);
    }
    return true;
}
FT ans[size * 2];
typedef long long Int64;
std::istream& operator>>(std::istream& in, FT& val) {
    Int64 tmp;
    in >> tmp;
    val = tmp;
    // if(static_cast<Int64>(val) != tmp)
    //    throw;
    return in;
}
typedef long double IOFT;
std::ostream& operator<<(std::ostream& out, FT val) {
    return out << static_cast<IOFT>(val);
}
int main() {
    int t;
    std::cin >> n >> m >> t;
    for(int i = 1; i <= n; ++i)
        std::cin >> A[0][i];
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j)
            std::cin >> A[i][j];
        std::cin >> A[i][0];
    }
    for(int i = 1; i <= n; ++i)
        idn[i] = i;
    for(int i = 1; i <= m; ++i)
        idm[i] = n + i;
    std::cout.precision(14);
    if(simplex()) {
        std::cout << std::fixed << -A[0][0]
                  << std::endl;
        if(t) {
            for(int i = 1; i <= m; ++i)
                ans[idm[i]] = A[i][0];
            for(int i = 1; i <= n; ++i)
                std::cout << std::fixed << ans[i]
                          << ' ';
        }
    }
    return 0;
}
