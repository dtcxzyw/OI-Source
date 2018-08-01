#include <algorithm>
#include <cstdio>
const int size = 2005, mod = 666623333;
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
std::pair<int, int> A[size];
bool cmp(std::pair<int, int> a, std::pair<int, int> b) {
    return a.first == b.first ? a.second > b.second : a.first < b.first;
}
int L[size], R[size], dp[size], w[size];
int main() {
    int n, x, q;
    scanf("%d%d%d", &n, &x, &q);
    for (int i = 1; i <= q; ++i)
        scanf("%d%d", &A[i].first, &A[i].second);
    {
        std::sort(A + 1, A + q + 1, cmp);
        int cur = 0;
        for (int i = 1; i <= q; ++i) {
            while (cur && A[cur].second >= A[i].second) --cur;
            A[++cur] = A[i];
        }
        q = cur;
    }
    {
        int lp = 1, rp = 0;
        for (int i = 1; i <= n; ++i) {
            while (rp < q && A[rp + 1].first <= i) ++rp;
            while (lp <= rp && A[lp].second < i) ++lp;
            L[i] = lp, R[i] = rp;
        }
    }
    int res = 0;
    Int64 invx = powm(x, mod - 2);
    for (int i = 1; i <= x; ++i) {
        Int64 p = (i - 1) * invx % mod;
        Int64 np = sub(1, p);
        Int64 inp = powm(np, mod - 2);
        Int64 inpp = inp;
        dp[0] = 1, w[0] = 1;
        int beg = 0, cur = 1;
        Int64 fac = p;
        for (int j = 1; j <= n; ++j) {
            while (beg < j && R[beg] < L[j] - 1) cur = sub(cur, w[beg++]);
            dp[j] = cur * fac % mod;
            w[j] = dp[j] * asInt64(inpp) % mod;
            cur = add(cur, w[j]);
            fac = fac * np % mod;
            inpp = inpp * inp % mod;
        }
        fac = 1;
        int pi = 0;
        for (int j = n; j >= 1 && R[j] == q; --j) {
            pi = (pi + dp[j] * fac) % mod;
            fac = fac * np % mod;
        }
        res = add(res, sub(1, pi));
    }
    printf("%d\n", res);
    return 0;
}
