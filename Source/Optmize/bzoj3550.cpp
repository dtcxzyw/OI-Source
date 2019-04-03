#include <algorithm>
#include <cstdio>
const int maxN = 205;
typedef double FT;
const FT eps = 1e-8;
FT A[maxN * 5][maxN * 3];
int N, M;
void pivot(int l, int e) {
    FT fac = A[l][e];
    A[l][e] = 1.0;
    for(int i = 0; i <= N; ++i)
        A[l][i] /= fac;
    for(int i = 0; i <= M; ++i)
        if(i != l) {
            FT k = A[i][e];
            A[i][e] = 0.0;
            for(int j = 0; j <= N; ++j)
                A[i][j] -= A[l][j] * k;
        }
}
int getRandom() {
    static int seed = 154354;
    return seed = seed * 48271LL % 2147483647;
}
int q[maxN * 5];
bool init() {
    while(true) {
        int qsiz = 0;
        for(int i = 1; i <= M; ++i)
            if(A[i][0] < -eps)
                q[qsiz++] = i;
        if(qsiz == 0)
            return true;
        int l = q[getRandom() % qsiz];
        qsiz = 0;
        for(int i = 1; i <= N; ++i)
            if(A[l][i] < -eps)
                q[qsiz++] = i;
        if(qsiz == 0)
            return false;
        int e = q[getRandom() % qsiz];
        pivot(l, e);
    }
}
FT simplex() {
    if(!init())
        return -1;
    while(true) {
        int e = 0;
        for(int i = 1; i <= N; ++i)
            if(A[0][i] > eps) {
                e = i;
                break;
            }
        if(e == 0)
            break;
        FT minv = 1e20;
        int l = 0;
        for(int i = 1; i <= M; ++i)
            if(A[i][e] > eps) {
                FT fac = A[i][0] / A[i][e];
                if(fac < minv)
                    l = i, minv = fac;
            }
        if(l == 0)
            return -1;
        pivot(l, e);
    }
    return -A[0][0];
}
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int lim = 2 * n + 1;
    N = 3 * n, M = N + lim;
    for(int i = 1; i <= N; ++i)
        scanf("%lf", &A[0][i]);
    for(int i = 1; i <= N; ++i)
        A[i][0] = A[i][i] = 1.0;
    for(int i = 1; i <= lim; ++i) {
        int id = N + i;
        A[id][0] = k;
        for(int j = 0; j < n; ++j)
            A[id][i + j] = 1.0;
    }
    printf("%.0lf\n", simplex());
    return 0;
}
