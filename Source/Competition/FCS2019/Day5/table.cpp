#include <algorithm>
#include <cmath>
#include <iostream>
int getRandom() {
    static int seed = 52346;
    return seed = seed * 48271LL % 2147483647;
}
typedef long double FT;
const FT eps = 1e-10L;
const int size = 205;
FT A[105 * 105][size];
int id[size + 105 * 105], n, m;
void pivot(int l, int e) {
    std::swap(id[n + l], id[e]);
    FT fac = A[l][e];
    A[l][e] = 1.0L;
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
int q[size * size];
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
int simplex() {
    if(!init())
        return -1;
    FT last = -A[0][0] - 1e5;
    while(true) {
        int e = 0;
        for(int i = 1; i <= n; ++i)
            if(A[0][i] > eps) {
                e = i;
                break;
            }
        if(e == 0)
            break;
        FT minv = 1e20L;
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
            return -1;
        pivot(l, e);
        FT cur = -A[0][0];
        if(cur - last < 1e-5L)
            break;
        last = cur;
    }
    return ceill(-A[0][0] - eps);
}
int X[size], Y[size];
bool flag[size][size];
int main() {
    int N, M, K;
    std::cin >> N >> M >> K;
    for(int i = 1; i <= N; ++i) {
        std::cin >> X[i];
        A[0][i] = X[i];
    }
    for(int i = 1; i <= M; ++i) {
        std::cin >> Y[i];
        A[0][N + i] = Y[i];
    }
    n = N + M;
    for(int i = 1; i <= K; ++i) {
        int x, y;
        std::cin >> x >> y;
        flag[x][y] = true;
    }
    m = 0;
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= M; ++j)
            if(!flag[i][j]) {
                ++m;
                A[m][0] = A[m][i] = A[m][N + j] = 1.0L;
            }
    for(int i = 1; i <= n; ++i)
        id[i] = i;
    int res = simplex();
    if(res != -1)
        std::cout << res << std::endl;
    else
        std::cout << "IIllIIll1£¡" << std::endl;
    return 0;
}
