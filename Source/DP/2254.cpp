#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 205;
char buf[size][size];
inline int iabs(int x) {
    return x >= 0 ? x : -x;
}
int dp[size][size];
struct Point {
    int p, v;
} q[size];
int n, m;
void solve(int x, int y, int t, int dx, int dy) {
    int b = 1, e = 0;
    for(int i = 0;
        1 <= x && x <= n && 1 <= y && y <= m;
        x += dx, y += dy, ++i) {
        if(buf[x][y] == 'x') {
            b = 1, e = 0;
            continue;
        }
        while(b <= e &&
              q[e].v + i - q[e].p <= dp[x][y])
            --e;
        ++e;
        q[e].v = dp[x][y];
        q[e].p = i;
        while(b < e && i - q[b].p > t)
            ++b;
        dp[x][y] = q[b].v + i - q[b].p;
    }
}
int main() {
    int x, y, k;
    scanf("%d%d%d%d%d", &n, &m, &x, &y, &k);
    for(int i = 1; i <= n; ++i)
        scanf("%s", buf[i] + 1);
    memset(dp, 0xc0, sizeof(dp));
    dp[x][y] = 0;
    for(int i = 1; i <= k; ++i) {
        int b, e, d;
        scanf("%d%d%d", &b, &e, &d);
        int t = e - b + 1;
        switch(d) {
            case 1:
                for(int i = 1; i <= m; ++i)
                    solve(n, i, t, -1, 0);
                break;
            case 2:
                for(int i = 1; i <= m; ++i)
                    solve(1, i, t, 1, 0);
                break;
            case 3:
                for(int i = 1; i <= n; ++i)
                    solve(i, m, t, 0, -1);
                break;
            case 4:
                for(int i = 1; i <= n; ++i)
                    solve(i, 1, t, 0, 1);
                break;
        }
    }
    int res = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            res = std::max(res, dp[i][j]);
    printf("%d\n", res);
    return 0;
}
