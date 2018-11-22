#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int size = 2505;
struct Info {
    int a, b, l, p, f;
    void read() {
        scanf("%d%d%d%d%d", &a, &b, &l, &p, &f);
    }
} P[size];
int f[size][size << 1], l;
class Queue {
private:
    int A[size], b, e;

public:
    Queue() : b(0), e(0) {}
    void clear() {
        b = e = 0;
    }
    bool nonempty() const {
        return b < e;
    }
    void push(int x, int j) {
        while(b < e && f[A[e - 1]][j] >= f[x][j])
            --e;
        A[e++] = x;
        while(b < e && P[x + 1].l - P[A[b]].l > l)
            ++b;
    }
    int front() const {
        return A[b];
    }
} q[size << 1];
int dp[size][size];
bool flag[size];
void fail() {
    puts("Poor Coke!");
    exit(0);
}
int main() {
    int n, m, r;
    scanf("%d%d%d%d", &n, &m, &r, &l);
    r = std::min(2 * n, r);
    for(int i = 1; i <= n; ++i) {
        P[i].read();
        if(P[i].l - P[i - 1].l > l)
            fail();
    }
    for(int i = 1; i <= n; ++i) {
        int c = P[i].a;
        for(int j = 0; j < c; ++j)
            dp[i][j] = dp[i - 1][j];
        for(int j = c; j <= m; ++j)
            dp[i][j] =
                std::max(dp[i - 1][j],
                         dp[i - 1][j - c] + P[i].b);
    }
    {
        while(m && !dp[n][m])
            --m;
        int cp = m;
        for(int i = n; i >= 1; --i)
            if(dp[i][cp] != dp[i - 1][cp]) {
                flag[i] = true;
                cp -= P[i].a;
            }
    }
    memset(f, 0x3f, sizeof(f));
    f[0][r] = 0;
    q[r].push(0, r);
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= r; ++j) {
            if(P[i].p && j)
                f[i][j] = std::min(
                    f[i][j], f[i][j - 1] + P[i].p);
            if(q[j + 2].nonempty())
                f[i][j] = std::min(
                    f[i][j],
                    f[q[j + 2].front()][j + 2] +
                        P[i].f);
            if(flag[i])
                q[j].clear();
            q[j].push(i, j);
        }
    }
    int minv = 0x3f3f3f3f;
    for(int i = 0; i <= r; ++i)
        minv = std::min(minv, f[n][i]);
    if(minv == 0x3f3f3f3f)
        fail();
    else
        printf("%d %d\n", dp[n][m], dp[n][m] - minv);
    return 0;
}
