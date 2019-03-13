#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
const int size = 1000005;
int p[size], mu[size], smu[size], presiz, pcnt = 0;
bool flag[size];
void pre(int n) {
    presiz = n;
    mu[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j])
                mu[val] = -mu[i];
            else
                break;
        }
    }
    for(int i = 1; i <= n; ++i)
        smu[i] = smu[i - 1] + mu[i];
}
namespace HashTable {
    const int modu = 131101, modv = 131071,
              magic = 0x3f3f3f3f;
    std::pair<int, int> LUT[modu];
    int reuse = 0, load = 0;
    void init() {
        memset(LUT, 0x3f, sizeof(LUT));
    }
    int& find(int x) {
        int hu = x % modu, hv = x % modv + 1, cur = hu;
        while(true) {
            if(LUT[cur].first == magic) {
                --reuse, ++load;
                LUT[cur].first = x;
            }
            if(LUT[cur].first == x) {
                ++reuse;
                return LUT[cur].second;
            }
            cur += hv;
            if(cur >= modu)
                cur -= modu;
        }
    }
}
int getMu(int x) {
    if(x <= presiz)
        return smu[x];
    int& res = HashTable::find(x);
    if(res != HashTable::magic)
        return res;
    res = 1;
    for(int i = 2; i <= x;) {
        int div = x / i, j = x / div;
        res -= (j - i + 1) * getMu(div);
        i = j + 1;
    }
    return res;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
struct Info {
    int n, m, k;
    Info(int n, int m, int k) : n(n), m(m), k(k) {}
    bool operator<(const Info& rhs) const {
        if(n != rhs.n)
            return n < rhs.n;
        if(m != rhs.m)
            return m < rhs.m;
        return k < rhs.k;
    }
};
std::map<Info, Int64> cache;
Int64 solve(int n, int m, int k) {
    if(n == 0 || m == 0)
        return 0;
    Info key(n, m, k);
    std::map<Info, Int64>::iterator it =
        cache.find(key);
    if(it != cache.end())
        return it->second;
    Int64& res = cache[key];
    if(k == 1) {
        int end = std::min(n, m), last = 0;
        for(int i = 1; i <= end;) {
            int dn = n / i, dm = m / i,
                j = std::min(n / dn, m / dm);
            int cur = getMu(j);
            res += asInt64(dn) * dm * (cur - last);
            last = cur;
            i = j + 1;
        }
    } else {
        for(int i = 1; i <= k && i <= m; ++i)
            if(k % i == 0)
                res += mu[i] * solve(m / i, n, i);
    }
    return res;
}
int main() {
    HashTable::init();
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int end = std::min(n, m);
    int npsiz = pow(end, 2.0 / 3.0);
    pre(std::max(k, npsiz));
    printf("%lld\n", solve(n, m, k));
    return 0;
}
