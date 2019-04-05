#include <cmath>
#include <cstdio>
const int size = 10005;
typedef long double FT;
struct Point {
    FT x, y, w;
} A[size];
FT eval(FT x, FT y, int n) {
    FT res = 0.0;
    for(int i = 0; i < n; ++i) {
        FT dx = A[i].x - x, dy = A[i].y - y,
           w = A[i].w;
        FT len = sqrtl(dx * dx + dy * dy);
        res += len * w;
    }
    return res;
}
const FT eps = 1e-8;
int main() {
    freopen("data/2.in", "r", stdin);
    int n;
    scanf("%d", &n);
    FT sx = 0.0, sy = 0.0, sw = 0.0;
    for(int i = 0; i < n; ++i) {
        scanf("%Lf%Lf%Lf", &A[i].x, &A[i].y, &A[i].w);
        sx += A[i].x * A[i].w, sy += A[i].y * A[i].w,
            sw += A[i].w;
    }
    sx /= sw, sy /= sw;
    FT cx = sx, cy = sy;
    const FT delta = 1e-9, gamma = 1e-8;
    while(true) {
        FT base = eval(cx, cy, n);
        FT dx = (eval(cx + delta, cy, n) - base) *
            (gamma / delta);
        FT dy = (eval(cx, cy + delta, n) - base) *
            (gamma / delta);
        cx -= dx, cy -= dy;
        if(std::max(fabsl(dx), fabsl(dy)) < eps)
            break;
        printf("%Lf %Lf\n", cx, cy);
    }
    printf("%.3Lf %.3Lf\n", cx, cy);
    return 0;
}
