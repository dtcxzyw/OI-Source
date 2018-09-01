#include <cstdio>
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    int n, res = 0;
    scanf("%d", &n);
    while(n--) {
        int x;
        scanf("%d", &x);
        res = gcd(res, x);
    }
    printf("%d\n", res >= 0 ? res : -res);
    return 0;
}
