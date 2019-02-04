#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int N = 1005, M = 10005;
typedef double FT;
const FT eps = 1e-8;
FT A[M][N];
int n, m;
void pivot(int l, int e) {
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
FT simplex() {
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
                FT cv = A[i][0] / A[i][e];
                if(cv < minv)
                    minv = cv, l = i;
            }
        pivot(l, e);
    }
    return -A[0][0];
}
int main() {
    n = read();
    m = read();
    for(int i = 1; i <= n; ++i)
        A[0][i] = read();
    for(int i = 1; i <= m; ++i) {
        int s = read();
        int t = read();
        for(int j = s; j <= t; ++j)
            A[i][j] = 1.0;
        A[i][0] = read();
    }
    printf("%.0lf\n", simplex());
    return 0;
}
