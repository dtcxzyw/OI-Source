#include <algorithm>
#include <cmath>
#include <cstdio>
typedef long long Int64;
const int psiz = 100000005;
int p[psiz], mu[psiz], mu2[psiz], fp[psiz], presiz;
Int64 ds[psiz];
bool flag[psiz];
void pre(int n) {
    presiz = n;
    mu[1] = ds[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            mu[i] = -1, ds[i] = 2, fp[i] = 1;
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j]) {
                mu[val] = -mu[i];
                ds[val] = ds[i] * 2;
                fp[val] = 1;
            } else {
                ds[val] =
                    ds[i] / (fp[i] + 1) * (fp[i] + 2);
                fp[val] = fp[i] + 1;
                break;
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        mu2[i] = mu2[i - 1] + (mu[i] ? 1 : 0);
        ds[i] += ds[i - 1];
    }
}
Int64 getMu2(Int64 n) {
    if(n <= presiz)
        return mu2[n];
    Int64 end = sqrt(n), res = 0;
    for(Int64 i = 1; i <= end; ++i)
        if(mu[i]) {
            Int64 div = n / (i * i);
            res += (mu[i] < 0 ? -div : div);
        }
    return res;
}
Int64 getDS(Int64 n) {
    if(n <= presiz)
        return ds[n];
    Int64 res = 0;
    for(Int64 i = 1; i <= n;) {
        Int64 div = n / i, j = n / div;
        res += div * (j - i + 1);
        i = j + 1;
    }
    return res;
}
Int64 solve(Int64 n) {
    Int64 res = 0, last = 0;
    for(Int64 i = 1; i <= n;) {
        Int64 div = n / i, j = n / div;
        Int64 cur = getMu2(j);
        res += (cur - last) * getDS(div);
        last = cur;
        i = j + 1;
    }
    return res;
}
Int64 q[10005];
int main() {
    int t;
    scanf("%d", &t);
    Int64 maxq = 0;
    for(int i = 1; i <= t; ++i) {
        scanf("%lld", &q[i]);
        maxq = std::max(maxq, q[i]);
    }
    pre(std::min(maxq, 100000000LL));
    for(int i = 1; i <= t; ++i)
        printf("%llu\n", solve(q[i]));
    return 0;
}
