#include <cmath>
#include <iostream>
typedef __int128 Int;
typedef long long Int64;
#define asInt static_cast<Int>
const int size = 8e7 + 5;
int p[size], pcnt = 0;
bool flag[size];
void pre(int n) {
    std::cout << "pre " << n << std::endl;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i])
            p[++pcnt] = i;
        for(int j = 1; j <= pcnt &&
            static_cast<Int64>(i) * p[j] <= n;
            ++j) {
            flag[i * p[j]] = true;
            if(i % p[j] == 0)
                break;
        }
    }
    std::cout << "prime " << pcnt << std::endl;
}
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
Int ans = 0;
Int64 n, cnt = 0;
void DFS(int pi, Int a, Int h) {
    Int cp = p[pi], cur = cp, sh = 1;
    a *= cp * cp;
    for(int e = 2; a <= n; a *= cp, cur *= cp, ++e) {
        Int nsh = cur * gcd(cp, e);
        Int ch = nsh - sh;
        sh = nsh;
        Int nh = h * ch;
        ans += nh * (n / a);
        if(((++cnt) & 0xfffff) == 0)
            std::cout << cnt << std::endl;
        for(int i = pi + 1; i <= pcnt; ++i) {
            Int np = p[i];
            if(a * np * np > n)
                break;
            DFS(i, a, nh);
        }
    }
}
void print(Int x) {
    if(x >= 10)
        print(x / 10);
    putchar('0' + x % 10);
}
int main() {
    std::cin >> n;
    pre(sqrt(n));
    ans = n;
    for(int i = 1; i <= pcnt; ++i)
        DFS(i, 1, 1);
    print(ans - 1);
    putchar('\n');
    std::cout << "Powerful Number Count " << cnt
              << std::endl;
    return 0;
}
