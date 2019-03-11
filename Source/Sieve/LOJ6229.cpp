#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 1000005, mod = 1000000007;
const Int64 inv6 = (mod + 1) / 6, inv2 = (mod + 1) / 2;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int p[size], sf[size], presiz;
bool flag[size];
void pre(int n) {
    sf[1] = 1;
    presiz = n;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            sf[i] = (1 - asInt64(i) * i) % mod;
            if(sf[i] < 0)
                sf[i] += mod;
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j])
                sf[val] =
                    asInt64(sf[i]) * sf[p[j]] % mod;
            else {
                sf[val] = sf[i];
                break;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        sf[i] = add(sf[i - 1], sf[i]);
}
Int64 getSG(Int64 x) {
    return x * (x + 1) % mod * (2 * x + 1) % mod;
}
namespace HashTable {
    const int modu = 4001, modv = 3989;
    std::pair<int, int> LUT[modu];
    void init() {
        memset(LUT, -1, sizeof(LUT));
    }
    int& find(int x) {
        int ha = x % modu, hb = 1 + x % modv, cur = ha;
        while(true) {
            if(LUT[cur].first == -1)
                LUT[cur].first = x;
            if(LUT[cur].first == x)
                return LUT[cur].second;
            cur += hb;
            if(cur >= modu)
                cur -= modu;
        }
    }
}
Int64 getSF(int x) {
    if(x <= presiz)
        return sf[x];
    int& cache = HashTable::find(x);
    if(cache != -1)
        return cache;
    Int64 res = x;
    for(int i = 2; i <= x;) {
        int div = x / i;
        int j = x / div;
        res = (res -
               (getSG(j) - getSG(i - 1)) * inv6 % mod *
                   getSF(div)) %
            mod;
        i = j + 1;
    }
    cache = res;
    return res;
}
int main() {
    HashTable::init();
    int n;
    scanf("%d", &n);
    pre(std::min(1000000, n));
    Int64 res = 0;
    for(int i = 1; i <= n;) {
        int div = n / i;
        int j = n / div;
        Int64 tot = asInt64(div) * (div + 1) % mod *
            inv2 % mod;
        tot = tot * tot % mod;
        res = (res + tot * (getSF(j) - getSF(i - 1))) %
            mod;
        i = j + 1;
    }
    res = (res + n) % mod * inv2 % mod;
    if(res < 0)
        res += mod;
    printf("%lld\n", res);
    return 0;
}
