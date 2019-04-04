#include <cmath>
#include <cstdio>
const int size = 10005;
typedef double FT;
const FT eps = 1e-8;
struct Point {
    FT x, y, w;
} A[size];
FT dx, dy;
FT eval(FT x, FT y, int n) {
    FT fx = 0.0, fy = 0.0;
    for(int i = 0; i < n; ++i) {
        FT dx = A[i].x - x, dy = A[i].y - y,
           w = A[i].w;
        FT len = sqrt(dx * dx + dy * dy);
        if(len > eps) {
            dx /= len, dy /= len;
            fx += dx * w, fy += dy * w;
        }
    }
    dx = copysign(1.0, fx), dy = copysign(1.0, fy);
    return std::max(fabs(fx), fabs(fy));
}
FT getRandom(FT range) {
    static int seed = 53214123;
    seed = seed * 48271LL % 2147483647;
    return range * seed / 2147483647.0;
}
int main() {
    int n;
    scanf("%d", &n);
    FT cx = 0.0, cy = 0.0, sw = 0.0;
    for(int i = 0; i < n; ++i) {
        scanf("%lf%lf%lf", &A[i].x, &A[i].y, &A[i].w);
        cx += A[i].x * A[i].w, cy += A[i].y * A[i].w,
            sw += A[i].w;
    }
    cx /= sw, cy /= sw;
    FT mx = cx, my = cy, merr = eval(cx, cy, n);
    FT T = 100000.0, cerr = merr;
    FT step = 1.0;
    while(T > 1e-5) {
        FT nx = cx + dx * getRandom(T),
           ny = cy + dy * getRandom(T);
        FT nerr = eval(nx, ny, n);
        if(nerr < cerr) {
            cx = nx, cy = ny, cerr = nerr;
            if(nerr < merr)
                merr = nerr, mx = nx, my = ny;
        } else if(exp((cerr - nerr) / T) >
                  getRandom(1.0))
            cx = nx, cy = ny, cerr = nerr;
        FT k =
            exp(-1.0 / std::min(1000.0, step += 0.5));
        T *= k;
        printf("%lf %.10lf %lf %lf %lf\n", T, k, mx,
               my, merr);
    }
    printf("%.3lf %.3lf\n", mx, my);
    return 0;
}
