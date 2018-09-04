// 3846
#include <cmath>
#include <cstdio>
#include <unordered_map>
typedef long long Int64;
Int64 powm(Int64 a, int k, Int64 mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
typedef std::unordered_map<int, int> HashTable;
typedef HashTable::iterator IterT;
HashTable map;
const int size = 1 << 16;
int main() {
    int p, b, n;
    scanf("%d%d%d", &p, &b, &n);
    int bsiz = sqrt(p) + 1;
    {
        Int64 cur = n;
        for(int i = 1; i <= bsiz; ++i) {
            cur = cur * b % p;
            map[cur] = i;
        }
    }
    Int64 cur = 1, base = powm(b, bsiz, p);
    int res = -1;
    for(int i = 1; i <= bsiz; ++i) {
        cur = cur * base % p;
        IterT it = map.find(cur);
        if(it != map.end()) {
            res = i * bsiz - it->second;
            break;
        }
    }
    if(res >= 0)
        printf("%d\n", res);
    else
        puts("no solution");
    return 0;
}
