// TODO:4820
#include <cstdio>
typedef __int128 Int128;
int main() {
    long long n, m;
    scanf("%lld%lld", &n, &m);
    Int128 base = static_cast<Int128>(n) * m;
    Int128 ans = base / (n + 1);
    printf("%d\n", base % (n + 1) ? ans : ans - 1);
    return 0;
}
