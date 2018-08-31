#include <cstdio>
const int mod = 2147483647, p = mod - 1;
typedef long long Int64;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
bool test(int g) {
    int x = p;
    for(int i = 2; i * i <= x; ++i)
        if(x % i == 0) {
            do
                x /= i;
            while(x % i == 0);
            if(powm(g, p / i) == 1)
                return false;
        }
    if(x != 1)
        return powm(g, p / x) != 1;
    return true;
}
int main() {
    int g;
    scanf("%d", &g);
    puts(test(g) ? "Yes" : "No");
    return 0;
}
