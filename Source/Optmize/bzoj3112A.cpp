#include <algorithm>
#include <cmath>
#include <cstdio>
const int maxN = 10005, maxM = 1005;
typedef double FT;
const FT eps = 1e-8;
FT A[maxM][maxN];
int N, M, q[maxN];
void pivot(int l, int e) {
    FT fac = A[l][e];
    A[l][e] = 1.0;
    for(int i = 0; i <= N; ++i)
        A[l][i] /= fac;
    int qcnt = 0;
    for(int i = 0; i <= N; ++i)
        if(fabs(A[l][i]) > eps)
            q[++qcnt] = i;
    for(int i = 0; i <= M; ++i)
        if(i != l) {
            FT k = A[i][e];
            if(fabs(k) < eps)
                continue;
            A[i][e] = 0.0;
            for(int j = 1; j <= qcnt; ++j) {
                int p = q[j];
                A[i][p] -= A[l][p] * k;
            }
        }
}
FT simplex() {
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
    scanf("%d%d", &M, &N);
    for(int i = 1; i <= M; ++i)
        scanf("%lf", &A[i][0]);
    for(int i = 1; i <= N; ++i) {
        int l, r;
        scanf("%d%d%lf", &l, &r, &A[0][i]);
        for(int j = l; j <= r; ++j)
            A[j][i] = 1.0;
    }
    printf("%.0lf\n", simplex());
    return 0;
}
