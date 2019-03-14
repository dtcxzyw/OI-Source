#include <algorithm>
#include <cstdio>
typedef double FT;
const FT eps = 1e-8;
const int size = 2005;
FT A[size], B[size], C[size];
struct Res {
    FT fv;
    int a, b;
    Res(FT fv, int a, int b) : fv(fv), a(a), b(b) {}
};
void CAS(FT& fv, int& da, int& db, FT cv, int a,
         int b) {
    if(cv > fv)
        fv = cv, da = a, db = b;
}
Res solve(int n, FT ka, FT kb) {
    FT kc = ka + kb, cfv = 0.0;
    int ca = 0, cb = 0;
    for(int i = 1; i <= n; ++i) {
        FT nfv = 0.0;
        int da = 0, db = 0;
        CAS(nfv, da, db, A[i] - ka, 1, 0);
        CAS(nfv, da, db, B[i] - kb, 0, 1);
        CAS(nfv, da, db, C[i] - kc, 1, 1);
        ca += da, cb += db, cfv += nfv;
    }
    return Res(cfv, ca, cb);
}
int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    for(int i = 1; i <= n; ++i)
        scanf("%lf", &A[i]);
    for(int i = 1; i <= n; ++i)
        scanf("%lf", &B[i]);
    for(int i = 1; i <= n; ++i)
        C[i] = A[i] + B[i] - A[i] * B[i];
    FT la = 0.0, ra = 1.0, ans;
    while(ra - la > eps) {
        FT ma = (la + ra) / 2.0;
        FT lb = 0.0, rb = 1.0;
        while(rb - lb > eps) {
            FT mb = (lb + rb) / 2.0;
            Res res = solve(n, ma, mb);
            (res.b >= b ? lb : rb) = mb;
        }
        Res res = solve(n, ma, lb);
        (res.a >= a ? la : ra) = ma;
        ans = res.fv + a * ma + b * lb;
    }
    printf("%.8lf\n", ans);
    return 0;
}
