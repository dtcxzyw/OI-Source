#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
const int size = 200005;
typedef double FT;
FT read() {
    char buf[32];
    int cnt = 0, c;
    do
        c = getchar();
    while(!isgraph(c));
    while(isgraph(c)) {
        buf[cnt++] = c;
        c = getchar();
    }
    buf[cnt] = '\0';
    return strtod(buf, 0);
}
struct Vec {
    FT x, y;
} P[size];
bool cmpX(const Vec& a, const Vec& b) {
    return a.x < b.x;
}
bool cmpY(const Vec& a, const Vec& b) {
    return a.y < b.y;
}
FT ans2 = 1e40, ans = 1e20;
void updateDis(const Vec& a, const Vec& b) {
    FT dx = a.x - b.x, dy = a.y - b.y;
    FT dis2 = dx * dx + dy * dy;
    if(dis2 < ans2) {
        ans2 = dis2;
        ans = sqrt(dis2);
    }
}
void solve(int b, int e) {
    if(e - b <= 3) {
        for(int i = b; i < e; ++i)
            for(int j = i + 1; j < e; ++j)
                updateDis(P[i], P[j]);
        std::sort(P + b, P + e, cmpY);
    } else {
        int mid = (b + e) >> 1;
        solve(b, mid);
        solve(mid, e);
        std::inplace_merge(P + b, P + mid, P + e,
                           cmpY);
        for(int i = b; i < e; ++i) {
            FT lim = P[i].y + ans;
            for(int j = i + 1; j < e && P[j].y < lim;
                ++j)
                updateDis(P[i], P[j]);
        }
    }
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        P[i].x = read();
        P[i].y = read();
    }
    std::sort(P, P + n, cmpX);
    solve(0, n);
    printf("%.4lf\n", ans);
    return 0;
}
