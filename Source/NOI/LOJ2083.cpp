#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 30005;
typedef long long Int64;
Int64 makeKey(Int64 id, Int64 a, Int64 b) {
    return id << 40 | a << 20 | b;
}
template <int off>
int getKey(Int64 x) {
    return (x >> off) & 0xfffff;
}
int cnt[size];
template <Int64* A, Int64* B, int off>
void radixSortImpl(int n) {
    int maxw = 0;
    for(int i = 1; i <= n; ++i) {
        int cw = getKey<off>(A[i]);
        ++cnt[cw];
        maxw = std::max(maxw, cw);
    }
    for(int i = 1; i <= maxw; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; --i) {
        int cw = getKey<off>(A[i]);
        B[cnt[cw]--] = A[i];
    }
    memset(cnt, 0, sizeof(int) * (maxw + 1));
}
Int64 A[size], B[size];
bool radixSort(int* rk, int n) {
    radixSortImpl<A, B, 0>(n);
    radixSortImpl<B, A, 20>(n);
    int crk = 0;
    Int64 lw = -1;
    for(int i = 1; i <= n; ++i) {
        int id = A[i] >> 40;
        Int64 cw = A[i] & 0xffffffffff;
        if(lw != cw)
            lw = cw, ++crk;
        rk[id] = crk;
    }
    return crk == n;
}
char buf[size];
int lg2[size];
struct String {
    int rk[size], sa[size], height[15][size];
    void buildSA(int n) {
        for(int i = 1; i <= n; ++i)
            A[i] = makeKey(i, buf[i], 0);
        int off = 1;
        while(!radixSort(rk, n)) {
            for(int i = 1; i <= n; ++i) {
                int sec =
                    i + off <= n ? rk[i + off] : 0;
                A[i] = makeKey(i, rk[i], sec);
            }
            off <<= 1;
        }
        for(int i = 1; i <= n; ++i)
            sa[rk[i]] = i;
        int h = 0;
        for(int i = 1; i <= n; ++i) {
            if(rk[i] == 1)
                h = 0;
            else {
                int k = sa[rk[i] - 1];
                if(h)
                    --h;
                while(buf[i + h] == buf[k + h])
                    ++h;
            }
            height[0][rk[i]] = h;
        }
        for(int i = 1; i < 15; ++i) {
            int end = n - (1 << i) + 1, off = 1
                << (i - 1);
            for(int j = 1; j <= end; ++j)
                height[i][j] =
                    std::min(height[i - 1][j],
                             height[i - 1][j + off]);
        }
    }
    int getLCP(int l, int r) {
        l = rk[l], r = rk[r];
        if(l > r)
            std::swap(l, r);
        ++l;
        int p = lg2[r - l + 1];
        return std::min(height[p][l],
                        height[p][r - (1 << p) + 1]);
    }
} SA, SB;
int AA[size], BB[size];
Int64 foo() {
    memset(AA, 0, sizeof(AA));
    memset(BB, 0, sizeof(BB));
    scanf("%s", buf + 1);
    int n = strlen(buf + 1);
    SA.buildSA(n);
    std::reverse(buf + 1, buf + n + 1);
    SB.buildSA(n);
    for(int len = 1; len * 2 <= n; ++len) {
        for(int j = 2 * len; j <= n; j += len) {
            int k = j - len;
            int lcp = std::min(len, SA.getLCP(k, j)),
                lcs = std::min(
                    len,
                    SB.getLCP(n - k + 1, n - j + 1));
            if(lcp + lcs <= len)
                continue;
            int num = lcp + lcs - len;
            ++AA[j + lcp - num], --AA[j + lcp];
            ++BB[k - lcs + 1], --BB[k - lcs + 1 + num];
        }
    }
    for(int i = 1; i <= n; ++i)
        AA[i] += AA[i - 1];
    for(int i = 1; i <= n; ++i)
        BB[i] += BB[i - 1];
    Int64 res = 0;
    for(int i = 1; i <= n; ++i)
        res += AA[i] * BB[i + 1];
    return res;
}
int main() {
    for(int i = 2; i < size; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; ++i)
        printf("%lld\n", foo());
    return 0;
}
