#include <cmath>
#include <cstdio>
#include <cstring>
const int size = 100005, maxk = 31;
int len[size], L, P;
typedef long double FT;
const FT maxl = 1e18;
FT dp[size];
FT powf(FT delta, int k) {
    FT res = 1;
    while(k) {
        if(k & 1)
            res = res * delta;
        k >>= 1, delta = delta * delta;
    }
    return res;
}
FT calc(int i, int j) {
    FT delta = len[j] - len[i] - L;
    return dp[i] + powf(fabsl(delta), P);
}
int k[size], q[size], n;
int getEdge(int x, int y) {
    int l = x, r = n + 1, res = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(calc(x, m) <= calc(y, m))
            res = m, l = m + 1;
        else
            r = m - 1;
    }
    return res + 1;
}
char buf[size][maxk];
int trans[size], pos[size];
int main() {
    int t;
    scanf("%d", &t);
    for(int x = 1; x <= t; ++x) {
        scanf("%d%d%d", &n, &L, &P);
        ++L;
        for(int i = 1; i <= n; ++i) {
            scanf("%s", buf[i]);
            len[i] = len[i - 1] + strlen(buf[i]) + 1;
        }
        int b = 1, e = 1;
        q[1] = 0;
        for(int i = 1; i <= n; ++i) {
            while(b < e && k[b] <= i)
                ++b;
            int p = q[b];
            trans[i] = p;
            dp[i] = calc(p, i);
            while(b < e &&
                  getEdge(q[e], i) <= k[e - 1])
                --e;
            k[e] = getEdge(q[e], i);
            q[++e] = i;
        }
        if(dp[n] > maxl)
            puts("Too hard to arrange");
        else {
            printf("%.0Lf\n", dp[n]);
            int cnt = 0;
            for(int i = n; i; i = trans[i])
                pos[++cnt] = i;
            pos[cnt + 1] = 0;
            for(int i = cnt; i >= 1; --i) {
                for(int j = pos[i + 1] + 1; j < pos[i];
                    ++j)
                    printf("%s ", buf[j]);
                puts(buf[pos[i]]);
            }
        }
        printf("--------------------");
        if(x != t)
            putchar('\n');
    }
    return 0;
}
