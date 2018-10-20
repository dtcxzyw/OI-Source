#include <cmath>
#include <cstdio>
typedef double FT;
const FT p = 1e-12, g = 1e-3;
const int maxStep = 1 << 20;
FT f(FT x) {
    return (x - 3.0) * x * x * x + 2.0;
}
FT df(FT x) {
    return (4.0 * x - 9.0) * x * x;
}
int main() {
    FT cur = 6.0;
    int step;
    for(step = 0; step < maxStep; ++step) {
        FT delta = -g * df(cur);
        cur += delta;
        if(fabs(delta) < p)
            break;
    }
    printf("step=%d res=(%.12lf,%.12lf)\n", step, cur,
           f(cur));
    return 0;
}
