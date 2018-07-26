//P4213
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = (1 << 20) + 5;
int psiz, prime[100000], mu[size] = {};
bool flag[size] = {};
Int64 phi[size];
void pre() {
    int pcnt = 0;
    phi[1] = 1, mu[1] = 1;
    for (int i = 2; i <= psiz; ++i) {
        if (!flag[i]) {
            prime[++pcnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; j <= pcnt; ++j) {
            int val = prime[j] * i;
            if (val > psiz) break;
            flag[val] = true;
            if (i % prime[j]) {
                phi[val] = phi[i] * (prime[j] - 1);
                mu[val] = -mu[i];
            } else {
                phi[val] = phi[i] * prime[j];
                break;
            }
        }
    }
    for (int i = 2; i <= psiz; ++i) phi[i] += phi[i - 1];
    for (int i = 2; i <= psiz; ++i) mu[i] += mu[i - 1];
}
typedef std::pair<Int64, int> Answer;
typedef std::map<int, Answer> Cache;
typedef Cache::iterator IterT;
typedef unsigned int UInt32;
Cache cache;
Answer calc(UInt32 x) {
    if (x <= psiz)
        return Answer(phi[x], mu[x]);
    else {
        Answer &res = cache[x];
        if (res.first == 0) {
            Int64 base1 = (asInt64(x) * (x + 1)) >> 1;
            int base2 = 1;
            for (UInt32 i = 2; i <= x;) {
                UInt32 div = x / i;
                UInt32 j = x / div;
                UInt32 cnt = j - i + 1;
                Answer res = calc(div);
                base1 -= cnt * res.first;
                base2 -= cnt * res.second;
                i = j + 1;
            }
            res = Answer(base1, base2);
        }
        return res;
    }
}
int input[10];
int main() {
    int t;
    scanf("%d", &t);
    int maxn = 0;
    for (int i = 0; i < t; ++i) {
        scanf("%d", &input[i]);
        maxn = std::max(maxn, input[i]);
    }
    psiz = std::min(1 << 20, maxn);
    pre();
    for (int i = 0; i < t; ++i) {
        Answer res = calc(input[i]);
        printf("%lld %d\n", res.first, res.second);
    }
    return 0;
}
