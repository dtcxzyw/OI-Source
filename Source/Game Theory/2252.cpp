#include <algorithm>
#include <cmath>
#include <cstdio>
int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    if(a > b)
        std::swap(a, b);
    double phi = 0.5 * (sqrt(5.0) + 1.0);
    bool flag = a != static_cast<int>((b - a) * phi);
    puts(flag ? "1" : "0");
    return 0;
}
