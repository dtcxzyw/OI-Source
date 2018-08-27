#include <cmath>
#include <cstdio>
const double r = 0.57721566490153286060651209;
int main() {
    long long n, m;
    scanf("%lld%lld", &n, &m);
    double base = m / 2.0, sum = 0.0;
    if(n <= 10000) {
        for(int i = 1; i <= n; ++i)
            sum += base / i;
    } else
        sum = base * (log(n + 1.0) + r);
    printf("%d\n", static_cast<int>(sum - 1e-10));
    return 0;
}
