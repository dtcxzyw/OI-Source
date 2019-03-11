#include <cmath>
#include <cstdio>
typedef long long Int64;
const int sqsiz = 320005;
int p[sqsiz], psiz = 0;
bool flag[sqsiz];
void pre(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!flag[i])
            p[++psiz] = i;
        for(int j = 1; j <= psiz && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j] == 0)
                break;
        }
    }
}
Int64 G[2][sqsiz], sqr, n;
Int64& getG(Int64 x) {
    if(x <= sqr)
        return G[0][x];
    return G[1][n / x];
}
Int64 q[sqsiz * 2];
int main() {
    scanf("%lld", &n);
    sqr = sqrt(n);
    pre(sqr);
    int m = 0;
    Int64 dv = 1;
    while(dv <= n) {
        Int64 val = n / dv;
        getG(val) = val - 1;
        q[++m] = val;
        dv = n / val + 1;
    }
    for(int i = 1; i <= psiz; ++i) {
        Int64 cp = p[i], cp2 = cp * cp;
        for(int j = 1; j <= m && cp2 <= q[j]; ++j) {
            Int64 x = q[j], &val = getG(x);
            val -= getG(x / cp) - (i - 1);
        }
    }
    printf("%lld\n", getG(n));
    return 0;
}
