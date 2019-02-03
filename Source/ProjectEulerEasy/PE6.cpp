#include <cstdio>
typedef long long Int64;
int main() {
    Int64 n;
    scanf("%lld", &n);
    Int64 a = n * (n + 1) / 2;
    Int64 b = n * (n + 1) * (2 * n + 1) / 6;
    printf("%lld\n", a * a - b);
    return 0;
}
