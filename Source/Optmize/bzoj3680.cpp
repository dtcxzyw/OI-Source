#include <algorithm>
#include <cmath>
#include <cstdio>
const int size = 10005;
typedef long double FT;
struct Point {
    FT x, y, w;
} A[size];
int n;
FT eval(FT x, FT y) {
    FT res = 0.0;
    for(int i = 0; i < n; ++i) {
        FT dx = A[i].x - x, dy = A[i].y - y,
           w = A[i].w;
        FT len = sqrtl(dx * dx + dy * dy);
        res += len * w;
    }
    return res;
}
FT getRandom(FT range) {
    static int seed = 35432;
    seed = seed * 48271LL % 2147483647;
    return range * seed / 2147483648.0L;
}
int main() {
    scanf("%d", &n);
    FT sx = 0.0, sy = 0.0, sw = 0.0;
    for(int i = 0; i < n; ++i) {
        scanf("%Lf%Lf%Lf", &A[i].x, &A[i].y, &A[i].w);
        sx += A[i].x * A[i].w, sy += A[i].y * A[i].w,
            sw += A[i].w;
    }
    sx /= sw, sy /= sw;
    FT mx = sx, my = sy, merr = eval(sx, sy);
    FT cx = sx, cy = sy, cerr = merr;
    const FT pi = acosl(-1.0);
    FT T = 100000.0;
    while(T > 1e-8) {
        FT angle = getRandom(2.0 * pi),
           len = getRandom(std::max(1e-3L, T));
        FT nx = cx + cosl(angle) * len,
           ny = cy + sinl(angle) * len;
        FT nerr = eval(nx, ny);
        if(nerr < cerr) {
            cx = nx, cy = ny, cerr = nerr;
            if(nerr < merr)
                merr = nerr, mx = nx, my = ny;
        } else if(expl((cerr - nerr) / T) >
                  getRandom(1.0))
            cx = nx, cy = ny, cerr = nerr;
        T *= 0.99;
    }
    printf("%.3Lf %.3Lf\n", mx, my);
    return 0;
}
