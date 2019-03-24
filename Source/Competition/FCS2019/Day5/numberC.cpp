#include <cmath>
#include <cstdio>
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 35005;
int p[size], mu[size];
bool flag[size];
void pre(int n) {
    mu[1] = 1;
    int pcnt = 0;
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
}
Int64 queryMu2(int n) {
    Int64 res = 0;
    for(int i = 1; i * i <= n; ++i)
        res += asInt64(mu[i]) * (n / (i * i));
    return res;
}
Int64 query(int n) {
    Int64 res = 0, last = 0;
    for(int i = 1; i <= n;) {
        int d = n / i, j = n / d;
        Int64 cur = queryMu2(j);
        res += (last - cur + asInt64(j - i + 1)) * d;
        last = cur;
        i = j + 1;
    }
    return res;
}
int main() {
    int L, R;
    scanf("%d%d", &L, &R);
    pre(sqrt(R) + 1);
    printf("%lld\n", query(R) - query(L - 1));
    return 0;
}
