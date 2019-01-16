#include <cmath>
#include <cstdio>
#include <map>
typedef unsigned long long Int64;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, Int64 k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res *= a;
        k >>= 1, a *= a;
    }
    return res;
}
const int size = 22000000;
int p[1400000], end;
Int64 phi[size];
bool flag[size];
void pre() {
    phi[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= end; ++i) {
        if(!flag[i])
            p[++pcnt] = i, phi[i] = i - 1;
        for(int j = 1; j <= pcnt && i * p[j] <= end;
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
    for(int i = 1; i <= end; ++i)
        phi[i] += phi[i - 1];
}
typedef std::map<Int64, Int64> Cache;
typedef Cache::iterator IterT;
Cache cache;
Int64 query(Int64 x) {
    if(x <= end)
        return phi[x];
    IterT it = cache.find(x);
    if(it != cache.end())
        return it->second;
    Int64 res = x & 1 ? x * ((x + 1) >> 1) :
                        (x >> 1) * (x + 1);
    for(Int64 i = 2; i <= x;) {
        Int64 div = x / i, j = x / div;
        res -= (j - i + 1) * query(div);
        i = j + 1;
    }
    return cache[x] = res;
}
int main() {
    Int64 n, m;
    scanf("%llu%llu", &n, &m);
    end = fmax(1e6, pow(n, 2.0 / 3.0));
    pre();
    Int64 res = 0, last = 0;
    for(Int64 i = 1; i <= m;) {
        Int64 div = m / i, j = m / div, val = query(j);
        res += (val - last) * powm(div, n);
        last = val, i = j + 1;
    }
    printf("%llu\n", res);
    return 0;
}
