#include <algorithm>
#include <cstdio>
#include <vector>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 505, mod = 1000000007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
std::vector<int> cnt[size];
int C[size][size], fac[size];
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
void pre(int n, int m) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = asInt64(fac[i - 1]) * i % mod;
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
    }
    cnt[0].push_back(1);
    for (int i = 1; i <= n; ++i) {
        int lsiz = cnt[i - 1].size();
        int cur = std::min(m, i * (i - 1) / 2);
        cnt[i].resize(cur + 1);
        cnt[i][0] = 1;
        for (int j = 1; j <= cur; ++j) {
            cnt[i][j] = cnt[i][j - 1];
            if (j < lsiz) cnt[i][j] = add(cnt[i][j], cnt[i - 1][j]);
            int off = j - i;
            if (0 <= off && off < lsiz)
                cnt[i][j] = sub(cnt[i][j], cnt[i - 1][off]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        int siz = cnt[i].size();
        for (int j = 1; j < siz; ++j)
            cnt[i][j] = add(cnt[i][j - 1], cnt[i][j]);
    }
}
int query(int n, int m) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        Int64 val = asInt64(C[n][i]) * fac[n - i] % mod;
        int cur = cnt[i].size() - 1;
        res = (res + val * val % mod * cnt[i][std::min(cur, m)] % mod * (n - i + 1)) % mod;
    }
    return res;
}
struct Query {
    int n, m;
} Q[10005];
int main() {
    int t = read();
    int maxn = 0, maxm = 0;
    for (int i = 0; i < t; ++i) {
        Q[i].n = read();
        maxn = std::max(maxn, Q[i].n);
        Q[i].m = read();
        maxm = std::max(maxm, Q[i].m);
    }
    pre(maxn, maxm);
    for (int i = 0; i < t; ++i)
        printf("%d\n", query(Q[i].n, Q[i].m));
    return 0;
}
