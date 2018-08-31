#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
int getRand() {
    static int seed = 347;
    return seed = seed * 48271LL % 2147483647;
}
const int size = 1 << 23, pool = 1 << 10;
int cnt[pool];
int main() {
    for(int i = 1; i <= size; ++i)
        ++cnt[getRand() >> 21];
    int minv = 1 << 30, maxv = 0, avg = size / pool;
    double s2 = 0.0;
    for(int i = 0; i < pool; ++i) {
        minv = std::min(minv, cnt[i]);
        maxv = std::max(maxv, cnt[i]);
        double delta = cnt[i] - avg;
        s2 += delta * delta;
    }
    s2 /= pool;
    printf("minc=%d maxc=%d except=%d s2=%.3lf\n",
           minv, maxv, avg, sqrt(s2));
    return 0;
}
