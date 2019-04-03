#include <algorithm>
#include <cmath>
#include <cstdio>
const int maxN = 10005, maxM = 1005;
int A[maxM][maxN], N, M, q[maxN];
void pivot(int l, int e) {
    int qcnt = 0;
    for(int i = 0; i <= N; ++i)
        if(A[l][i])
            q[++qcnt] = i;
    for(int i = 0; i <= M; ++i)
        if(i != l) {
            int k = A[i][e];
            if(k == 0)
                continue;
            A[i][e] = 0;
            for(int j = 1; j <= qcnt; ++j) {
                int p = q[j];
                A[i][p] -= A[l][p] * k;
            }
        }
}
int simplex() {
    while(true) {
        int e = 0;
        for(int i = 1; i <= N; ++i)
            if(A[0][i] > 0) {
                e = i;
                break;
            }
        if(e == 0)
            break;
        int minv = 1 << 30;
        int l = 0;
        for(int i = 1; i <= M; ++i)
            if(A[i][e] > 0) {
                int fac = A[i][0] / A[i][e];
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
        scanf("%d", &A[i][0]);
    for(int i = 1; i <= N; ++i) {
        int l, r;
        scanf("%d%d%d", &l, &r, &A[0][i]);
        for(int j = l; j <= r; ++j)
            A[j][i] = 1;
    }
    printf("%d\n", simplex());
    return 0;
}
