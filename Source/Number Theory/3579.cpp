#include <cmath>
#include <cstdio>
int foo(int a, int b, int c, int d) {
    --a, --c;
    int end = sqrt(b > d ? b : d), res = 0;
    for (int i = 1; i <= end; ++i) {
        int div[4] = {a / i, b / i, c / i, d / i};
        if (i > res && div[0] < div[1] && div[2] < div[3]) res = i;
        for (int j = 0; j < 4; ++j) {
            int x = div[j];
            if (x > res && a / x < b / x && c / x < d / x) res = x;
        }
    }
    return res;
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        printf("%d\n", foo(a, b, c, d));
    }
    return 0;
}
