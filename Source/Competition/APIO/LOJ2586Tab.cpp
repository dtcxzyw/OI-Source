#include <algorithm>
#include <cmath>
#include <cstdio>
using Int64 = long long;
using FT = double;
const FT base = 1000000000;
std::pair<Int64, Int64> A[1005];
int main() {
    int n;
    scanf("%d", &n);
    FT pi2 = acos(-1.0);
    for(int i = 1; i <= n; ++i) {
        FT angle = pi2 / n * i;
        A[i].first = base * cos(angle);
        A[i].second = base * sin(angle);
    }
    std::random_shuffle(A + 1, A + n + 1);
    for(int i = 1; i <= n; ++i) {
        printf("{%lld,%lld},", A[i].first,
               A[i].second);
    }
    return 0;
}
