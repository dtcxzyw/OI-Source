#include <cstdio>
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    int x = 1, y = 1;
    for(int i = 10; i < 100; ++i)
        for(int j = i + 1; j < 100; ++j) {
            int a = i / 10, b = i % 10, c = j / 10,
                d = j % 10;
            bool flag = false;
            flag |= (a == c && i * d == b * j);
            flag |= (a == d && i * c == b * j);
            flag |= (b == c && i * d == a * j);
            flag |= (b == d && i * c == a * j);
            if(flag && b && d) {
                printf("%d %d\n", i, j);
                x *= i, y *= j;
            }
        }
    int d = gcd(x, y);
    printf("%d %d\n", x / d, y / d);
    return 0;
}
