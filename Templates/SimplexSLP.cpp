#include <algorithm>
#include <cmath>
#include <iostream>
typedef long double FT;
const FT eps = 1e-10;
const int size = 25, maxStep = 2000;
struct LP {
    FT A[size][size];
    int id[size * 2], n, m;
    void pivot(int l, int e) {
        std::swap(id[n + l], id[e]);
        FT fac = A[l][e];
        A[l][e] = 1.0;
        for(int i = 0; i <= n; ++i)
            A[l][i] /= fac;
        for(int i = 0; i <= m; ++i)
            if(i != l) {
                FT k = A[i][e];
                A[i][e] = 0.0;
                for(int j = 0; j <= n; ++j)
                    A[i][j] -= k * A[l][j];
            }
    }
    bool simplex(int m) {
        while(true) {
            int e = 0;
            for(int i = 1; i <= n; ++i)
                if(A[0][i] > eps) {
                    e = i;
                    break;
                }
            if(e == 0)
                break;
            FT minv = 1e20;
            int l = 0;
            for(int i = 1; i <= m; ++i)
                if(A[i][e] > eps) {
                    FT val = A[i][0] / A[i][e];
                    if(val < minv) {
                        minv = val;
                        l = i;
                    }
                }
            if(l == 0)
                return false;
            pivot(l, e);
        }
        return true;
    }
} A, B;
int getRandom() {
    static int seed = 2354;
    return seed = seed * 48271LL % 2147483647;
}
int q[size];
int initRandom() {
    int res = 0;
    for(int i = 0; i < maxStep; ++i) {
        int qcnt = 0;
        for(int i = 1; i <= A.m; ++i)
            if(A.A[i][0] < -eps)
                q[qcnt++] = i;
        if(qcnt == 0) {
            res = 1;
            break;
        }
        int l = q[getRandom() % qcnt];
        qcnt = 0;
        for(int i = 1; i <= A.n; ++i)
            if(A.A[l][i] < -eps)
                q[qcnt++] = i;
        if(qcnt == 0)
            return -1;
        int e = q[getRandom() % qcnt];
        A.pivot(l, e);
    }
    return res;
}
bool init() {
    int res = initRandom();
    if(res != 0)
        return res == 1;
    int k = 1;
    for(int i = 2; i <= A.m; ++i)
        if(A.A[i][0] < A.A[k][0])
            k = i;
    if(A.A[k][0] > -eps)
        return true;
    B = A;
    ++B.n, ++B.m;
    B.id[B.n] = B.n;
    for(int i = 1; i < B.n; ++i)
        B.A[0][i] = 0.0;
    for(int i = 0; i <= B.m; ++i)
        B.A[i][B.n] = -1.0;
    for(int i = 0; i <= A.n; ++i)
        B.A[B.m][i] = A.A[0][i];
    B.pivot(k, B.n);
    B.simplex(B.m - 1);
    FT ans = -B.A[0][0];
    if(ans < -eps)
        return false;
    for(int i = 1; i <= B.m; ++i)
        if(B.id[B.n + i] == B.n) {
            for(int j = 1; j <= B.n; ++j)
                if(fabsl(B.A[i][j]) > eps) {
                    B.pivot(i, j);
                    break;
                }
            break;
        }
    for(int i = 1; i <= B.n; ++i)
        if(B.id[i] == B.n) {
            for(int j = 1; j < i; ++j)
                A.id[j] = B.id[j];
            for(int j = i + 1; j <= B.n; ++j)
                A.id[j - 1] = B.id[j];
            for(int j = 1; j <= A.m; ++j)
                A.id[j + A.n] = B.id[j + B.n];
            for(int j = 1; j <= B.m; ++j) {
                int nj = j == B.m ? 0 : j;
                for(int k = 0; k < i; ++k)
                    A.A[nj][k] = B.A[j][k];
                for(int k = i + 1; k <= B.n; ++k)
                    A.A[nj][k - 1] = B.A[j][k];
            }
            break;
        }
    return true;
}
bool simplex() {
    if(!init()) {
        std::cout << "Infeasible" << std::endl;
        return false;
    }
    if(!A.simplex(A.m)) {
        std::cout << "Unbounded" << std::endl;
        return false;
    }
    return true;
}
FT ans[size];
int main() {
    int t;
    std::cin >> A.n >> A.m >> t;
    for(int i = 1; i <= A.n; ++i)
        std::cin >> A.A[0][i];
    for(int i = 1; i <= A.m; ++i) {
        for(int j = 1; j <= A.n; ++j)
            std::cin >> A.A[i][j];
        std::cin >> A.A[i][0];
    }
    for(int i = 1; i <= A.n; ++i)
        A.id[i] = i;
    std::cout.precision(14);
    if(simplex()) {
        std::cout << std::fixed << -A.A[0][0]
                  << std::endl;
        if(t) {
            for(int i = 1; i <= A.m; ++i)
                ans[A.id[A.n + i]] = A.A[i][0];
            for(int i = 1; i <= A.n; ++i)
                std::cout << std::fixed << ans[i]
                          << ' ';
        }
    }
    return 0;
}
