#include <algorithm>
#include <cmath>
#include <iostream>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
int getRandom() {
    static int seed = 2354;
    return seed = seed * 48271LL % 2147483647;
}
typedef long double FT;
const FT eps = 1e-10;
const int size = 25;
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
int q[size];
bool init() {
    while(true) {
        int qcnt = 0;
        for(int i = 1; i <= m; ++i)
            if(A[i][0] < -eps)
                q[qcnt++] = i;
        if(qcnt == 0)
            break;
        int l = q[getRandom() % qcnt];
        qcnt = 0;
        for(int i = 1; i <= n; ++i)
            if(A[l][i] < -eps)
                q[qcnt++] = i;
        if(qcnt == 0)
            return false;
        int e = q[getRandom() % qcnt];
        pivot(l, e);
    }
    return true;
}
bool simplex() {
    if(!init()) {
        puts("Infeasible");
        return false;
    }
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
        if(l == 0) {
            puts("Unbounded");
            return false;
        }
        pivot(l, e);
    }
    return true;
}
FT ans[size];
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
        id[i] = i;
    std::cout.precision(14);
    if(simplex()) {
        std::cout << std::fixed << -A[0][0]
                  << std::endl;
        if(t) {
            for(int i = 1; i <= m; ++i)
                ans[id[n + i]] = A[i][0];
            for(int i = 1; i <= n; ++i)
                std::cout << std::fixed << ans[i]
                          << std::endl;
        }
    }
    return 0;
}
