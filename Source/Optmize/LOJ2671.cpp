#include <cmath>
#include <cstdio>
typedef double FT;
const int size = 10005, IA = 15, IB = 70;
FT s[size], k[size], sk[size], vf[size], v[size];
inline FT f(int i, FT lambda, FT v) {
    return 2.0 * lambda * k[i] * (v - vf[i]) * v * v +
        1.0;
}
inline FT df(int i, FT lambda, FT v) {
    return 2.0 * lambda * k[i] *
        (3.0 * v - 2.0 * vf[i]) * v;
}
const FT eps = 1e-13;
void getV(int n, FT lambda) {
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < IA; ++j) {
            FT delta = f(i, lambda, v[i]) /
                df(i, lambda, v[i]);
            if(fabs(delta) < eps)
                break;
            v[i] -= delta;
        }
    }
}
int main() {
    int n;
    FT EU;
    scanf("%d%lf", &n, &EU);
    for(int i = 1; i <= n; ++i) {
        scanf("%lf%lf%lf", &s[i], &k[i], &vf[i]);
        sk[i] = s[i] * k[i];
        v[i] = 200.0;
    }
    FT l = -1.0, r = 0.0;
    for(int i = 0; i < IB; ++i) {
        FT m = (l + r) * 0.5;
        getV(n, m);
        FT E = 0.0;
        for(int j = 1; j <= n; ++j) {
            FT dv = v[j] - vf[j];
            E += sk[j] * dv * dv;
        }
        (E < EU ? l : r) = m;
    }
    getV(n, l);
    FT t = 0.0;
    for(int i = 1; i <= n; ++i)
        t += s[i] / v[i];
    printf("%.8lf\n", t);
    return 0;
}
