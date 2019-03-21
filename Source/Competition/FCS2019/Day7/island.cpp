#include <cstdio>
#include <map>
const int size = 100005, mod = 998244353,
          inv2 = (mod + 1) / 2, inv6 = (mod + 1) / 6;
typedef long long Int64;
Int64 sum1(Int64 x) {
    return (x * (x + 1) / 2) % mod;
}
Int64 sum2(Int64 x) {
    return x * (x + 1) % mod * (2 * x + 1) % mod *
        inv6 % mod;
}
int dis(int a, int b) {
    return (a < b ? b - a : a - b) % mod;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int L[size], R[size];
struct Info {
    int cnt, sum;
    Info(int cnt, int sum) : cnt(cnt), sum(sum) {}
    Info operator+(const Info& rhs) const {
        return Info(add(cnt + rhs.cnt),
                    add(sum + rhs.sum));
    }
    Info trans(int dis) const {
        return Info(
            cnt, (asInt64(cnt) * dis + rhs.sum) % mod);
    }
};
typedef std::map<int, Info>::iterator IterT;
typedef std::map<std::pair<int, int>, Info>::iterator
    IterLT;
int main() {
    int n;
    char str[15];
    scanf("%d%s", &n, str);
    Int64 resA = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", &L[i], &R[i]);
        --R[i];
        Int64 len = R[i] - L[i] + 1;
        resA = (resA + sum2(len) - sum1(len)) % mod;
    }
    Int64 resB = 0;
    std::map<int, Info> P;
    std::map<std::pair<int, int>, Info> LP;
    for(int i = 2; i <= n; ++i) {
        int nl = std::max(L[i - 1], L[i]),
            nr = std::min(R[i - 1], R[i]);
        std::map<int, Info> CP;
        for(IterT it = P.begin(); it != P.end();
            ++it) {
            int cp =
                std::min(nr, std::max(nl, it->first));
            CP[cp] += it->second.trans(
                dis(it->first, cp) + 1);
        }
        std::swap(P, CP);
        std::map<std::pair<int, int>, Info> CLP;
        for(IterLT it = LP.begin(); it != LP.end();
            ++it) {
        }
        std::swap(CLP, LP);
    }
    Int64 res = (resA + resB * 2) % mod;
    if(res < 0)
        res += mod;
    printf("%lld\n", res);
    return 0;
}
