#include <cmath>
#include <cstdio>
#include <unordered_map>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 10000005, mod = 1000000007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int p[size], phi[size], pcnt = 0, pn;
bool flag[size];
void pre() {
    phi[1] = 1;
    for(int i = 2; i <= pn; ++i) {
        if(!flag[i])
            p[++pcnt] = i, phi[i] = i - 1;
        for(int j = 1; j <= pcnt && i * p[j] <= pn;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j])
                phi[val] = phi[i] * (p[j] - 1);
            else {
                phi[val] = phi[i] * p[j];
                break;
            }
        }
    }
    for(int i = 1; i <= pn; ++i)
        phi[i] = add(phi[i], phi[i - 1]);
}
typedef std::unordered_map<Int64, int> Cache;
Cache cache;
Int64 phiSum(Int64 x) {
    if(x <= pn)
        return phi[x];
    Cache::iterator it = cache.find(x);
    if(it != cache.end())
        return it->second;
    Int64 val = x % mod,
          res = ((val * (val + 1)) >> 1) % mod;
    for(Int64 i = 2; i <= x;) {
        Int64 d = x / i, j = x / d;
        res = (res - (j - i + 1) % mod * phiSum(d)) %
            mod;
        i = j + 1;
    }
    if(res < 0)
        res += mod;
    return cache[x] = res;
}
Int64 n, res = 0;
void DFS(int pi, Int64 a, Int64 h) {
    Int64 cp = p[pi];
    a *= cp;
    if(pi != 1)
        a *= cp;
    Int64 sum = pi == 1 ? cp - 1 : (cp - 1) * cp;
    for(int e = pi == 1 ? 1 : 2; a <= n;
        ++e, a *= cp) {
        Int64 hp = ((cp ^ e) - sum) % mod;
        if(hp < 0)
            hp += mod;
        sum = (sum * cp + hp * (cp - 1)) % mod;
        Int64 nh = h * hp % mod;
        res = (res + nh * phiSum(n / a)) % mod;
        for(int i = pi + 1; i <= pcnt; ++i) {
            Int64 np = p[i];
            if(a * np > n || a * np * np > n)
                break;
            DFS(i, a, nh);
        }
    }
}
int main() {
    scanf("%lld", &n);
    const double ratio = 0.7;
    pn =
        std::max(std::min(static_cast<double>(n), 1e6),
                 pow(n, ratio) + 1);
    pre();
    res = phiSum(n);
    DFS(1, 1, 1);
    for(int i = 2; i <= pcnt; ++i) {
        if(asInt64(p[i]) * p[i] > n)
            break;
        DFS(i, 1, 1);
    }
    printf("%lld\n", res);
    return 0;
}
