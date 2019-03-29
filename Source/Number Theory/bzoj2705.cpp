#include <cstdio>
typedef long long Int64;
Int64 fac[50], fp[50], n, fcnt = 0, res = 0;
void DFS(int cur, Int64 x, Int64 px) {
    if(cur == 0)
        res += px * (n / x);
    else {
        DFS(cur - 1, x, px);
        x *= fac[cur], px *= fac[cur] - 1;
        for(int i = 1; i <= fp[cur];
            ++i, x *= fac[cur], px *= fac[cur])
            DFS(cur - 1, x, px);
    }
}
int main() {
    scanf("%lld", &n);
    Int64 x = n;
    for(int i = 2; 1LL * i * i <= x; ++i)
        if(x % i == 0) {
            fac[++fcnt] = i;
            do
                x /= i, ++fp[fcnt];
            while(x % i == 0);
        }
    if(x != 1) {
        fac[++fcnt] = x;
        fp[fcnt] = 1;
    }
    DFS(fcnt, 1, 1);
    printf("%lld\n", res);
    return 0;
}
