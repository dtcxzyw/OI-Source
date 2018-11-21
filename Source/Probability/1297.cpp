#include <algorithm>
#include <cstdio>
int main() {
    int n, A, B, C, a;
    scanf("%d%d%d%d%d", &n, &A, &B, &C, &a);
    double first = a % C + 1, last = a % C + 1,
           res = 0.0;
    for(int i = 2; i <= n; ++i) {
        a = (static_cast<long long>(a) * A + B) %
            100000001;
        double cur = a % C + 1;
        res += std::min(cur, last) / (cur * last);
        last = cur;
    }
    res += std::min(first, last) / (first * last);
    printf("%.3lf\n", res);
    return 0;
}
