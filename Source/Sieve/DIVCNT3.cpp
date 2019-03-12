#include <algorithm>
#include <cmath>
#include <cstdio>
typedef long long Int64;
const int sqsiz = 320005;
int p[sqsiz], pcnt = 0;
bool flag[sqsiz];
void pre(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!flag[i])
            p[++pcnt] = i;
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j] == 0)
                break;
        }
    }
}
Int64 G[2][sqsiz], n, sqn;
Int64& getG(Int64 x) {
    if(x <= sqn)
        return G[0][x];
    return G[1][n / x];
}
Int64 S(Int64 i, int j) {
    if(i <= 1 || p[j] > n)
        return 0;
    Int64 res = getG(i) - 4 * (j - 1);
    for(int k = j; k <= pcnt; ++k) {
        Int64 cp = p[k], p1 = cp, p2 = p1 * p1;
        if(p2 > i)
            break;
        for(int e = 4; p2 <= i;
            e += 3, p1 = p2, p2 *= cp) {
            res += e * S(i / p1, k + 1) + (e + 3);
        }
    }
    return res;
}
Int64 q[sqsiz * 2];
Int64 solve(Int64 x) {
    n = x, sqn = sqrt(x);
    Int64 dv = 1;
    int m = 0;
    while(dv <= n) {
        Int64 val = n / dv;
        getG(val) = val - 1;
        q[++m] = val;
        dv = n / val + 1;
    }
    for(int i = 1; i <= pcnt; ++i) {
        Int64 cp = p[i], cp2 = cp * cp;
        if(cp2 > n)
            break;
        for(int j = 1; j <= m && q[j] >= cp2; ++j) {
            Int64 k = q[j], &val = getG(k);
            val -= getG(k / cp) - (i - 1);
        }
    }
    for(int i = 1; i <= m; ++i)
        getG(q[i]) *= 4;
    return S(n, 1) + 1;
}
Int64 A[10005];
int main() {
    int t;
    scanf("%d", &t);
    Int64 maxq = 0;
    for(int i = 1; i <= t; ++i) {
        scanf("%lld", &A[i]);
        maxq = std::max(maxq, A[i]);
    }
    pre(sqrt(maxq));
    for(int i = 1; i <= t; ++i)
        printf("%llu\n", solve(A[i]));
    return 0;
}
