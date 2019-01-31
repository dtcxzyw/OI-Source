#include <cmath>
#include <iostream>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 1e6 + 5, mod = 1000000007, maxk = 55;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int p[size], pcnt = 0;
bool flag[size];
void pre(int n) {
    std::cout << "pre " << n << std::endl;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i])
            p[++pcnt] = i;
        for(int j = 1;
            j <= pcnt && asInt64(i) * p[j] <= n; ++j) {
            flag[i * p[j]] = true;
            if(i % p[j] == 0)
                break;
        }
    }
    std::cout << "prime " << pcnt << std::endl;
}
struct Poly {
    Int64 fac[maxk];
    int end;
    void init(int k) {
        Int64 val[maxk];
        end = k + 1;
        for(int i = 0; i <= end; ++i) {
            val[i] = 1;
            for(int j = 0; j < k; ++j)
                val[i] = val[i] * i % mod;
        }
        for(int i = 1; i <= end; ++i)
            val[i] = (val[i - 1] + val[i]) % mod;
        Int64 kt[maxk];
        for(int i = 0; i <= end; ++i)
            fac[i] = 0;
        for(int i = 0; i <= end; ++i) {
            kt[0] = val[i];
            for(int j = 1; j <= end; ++j)
                kt[j] = 0;
            for(int j = 0; j <= end; ++j)
                if(i != j) {
                    for(int k = end; k >= 1; --k)
                        kt[k] =
                            (kt[k - 1] - j * kt[k]) %
                            mod;
                    kt[0] = -j * kt[0] % mod;
                    Int64 div = powm(i - j, mod - 2);
                    for(int k = 0; k <= end; ++k)
                        kt[k] = kt[k] * div % mod;
                }
            for(int j = 0; j <= end; ++j)
                fac[j] = (fac[j] + kt[j]) % mod;
        }
    }
    Int64 operator()(Int64 x) const {
        x %= mod;
        Int64 res = 0;
        for(int i = end; i >= 0; --i)
            res = (res * x + fac[i]) % mod;
        return res;
    }
} poly;
Int64 ans = 0, n, pw[size];
void DFS(int pi, Int64 a, Int64 h) {
    Int64 cp = p[pi];
    Int64 base = pw[pi];
    Int64 ch = (base - base * base) % mod;
    h = h * ch % mod;
    for(a *= cp * cp; a <= n; a *= cp) {
        ans = (ans + h * poly(n / a)) % mod;
        for(int i = pi + 1; i <= pcnt; ++i) {
            Int64 np = p[i];
            if(a * np > n || a * np * np > n)
                break;
            DFS(i, a, h);
        }
    }
}
int main() {
    int k;
    std::cin >> n >> k;
    pre(sqrt(n));
    for(int i = 1; i <= pcnt; ++i)
        pw[i] = 1;
    for(int i = 1; i <= k; ++i) {
        std::cout << "Processing " << i << std::endl;
        poly.init(i);
        for(int j = 1; j <= pcnt; ++j)
            pw[j] = pw[j] * p[j] % mod;
        ans = (ans + poly(n)) % mod;
        for(int j = 1; j <= pcnt; ++j)
            DFS(j, 1, 1);
    }
    if(ans < 0)
        ans += mod;
    std::cout << ans << std::endl;
    return 0;
}
