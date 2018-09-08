#include <cstdio>
int foo(int p, int e, int i, int d) {
    const int k1 = 5544, k2 = 14421, k3 = 1288,
              mod = 21252;
    int res = (k1 * p + k2 * e + k3 * i) % mod - d;
    while(res <= 0)
        res += mod;
    return res;
}
int main() {
    int p, e, i, d, cnt = 0;
    while(scanf("%d%d%d%d", &p, &e, &i, &d) != EOF &&
          p >= 0) {
        printf("Case %d: the next triple peak occurs "
               "in %d days.\n",
               ++cnt, foo(p, e, i, d));
    }
    return 0;
}
