#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 300005;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 makeKey(Int64 id, Int64 a, Int64 b) {
    return id << 40 | a << 20 | b;
}
template <int off>
int getKey(Int64 w) {
    return (w >> off) & 0xfffff;
}
int cnt[size];
template <Int64* A, Int64* B, int off>
void radixSortImpl(int n) {
    int maxw = 0;
    for(int i = 1; i <= n; ++i) {
        int w = getKey<off>(A[i]);
        ++cnt[w];
        maxw = std::max(maxw, w);
    }
    for(int i = 1; i <= maxw; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; --i) {
        int w = getKey<off>(A[i]);
        B[cnt[w]--] = A[i];
    }
    memset(cnt, 0, sizeof(int) * (maxw + 1));
}
Int64 A[size], B[size];
int rk[size];
bool radixSort(int n) {
    radixSortImpl<A, B, 0>(n);
    radixSortImpl<B, A, 20>(n);
    int crk = 0;
    Int64 lw = -1;
    for(int i = 1; i <= n; ++i) {
        int id = A[i] >> 40;
        Int64 cw = A[i] & 0xffffffffff;
        if(lw != cw) {
            ++crk;
            lw = cw;
        }
        rk[id] = crk;
    }
    return crk == n;
}
char buf[size];
int sa[size], height[size];
void calcSA(int n) {
    for(int i = 1; i <= n; ++i)
        A[i] = makeKey(i, buf[i], 0);
    int off = 1;
    while(!radixSort(n)) {
        for(int i = 1; i <= n; ++i) {
            int bk = i + off <= n ? rk[i + off] : 0;
            A[i] = makeKey(i, rk[i], bk);
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
        height[rk[i]] = h;
    }
}
int H[19][size], MaxW[19][size], MinW[19][size],
    lg2[size];
int choose(int a, int b) {
    return height[a] < height[b] ? a : b;
}
void buildST(int n) {
    for(int i = 2; i <= n; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    for(int i = 1; i <= n; ++i)
        H[0][i] = i;
    for(int i = 1; i < 19; ++i) {
        int end = n - (1 << i) + 1, off = 1 << (i - 1);
        for(int j = 1; j <= end; ++j) {
            H[i][j] =
                choose(H[i - 1][j], H[i - 1][j + off]);
            MaxW[i][j] = std::max(
                MaxW[i - 1][j], MaxW[i - 1][j + off]);
            MinW[i][j] = std::min(
                MinW[i - 1][j], MinW[i - 1][j + off]);
        }
    }
}
int queryMinPos(int l, int r) {
    int p = lg2[r - l + 1];
    return choose(H[p][l], H[p][r - (1 << p) + 1]);
}
int queryMax(int l, int r) {
    int p = lg2[r - l + 1];
    return std::max(MaxW[p][l],
                    MaxW[p][r - (1 << p) + 1]);
}
int queryMin(int l, int r) {
    int p = lg2[r - l + 1];
    return std::min(MinW[p][l],
                    MinW[p][r - (1 << p) + 1]);
}
Int64 ansC[size], ansM[size];
void solve(int l, int r) {
    if(l >= r)
        return;
    int pos = queryMinPos(l + 1, r), lcp = height[pos];
    Int64 lc = pos - l, lmin = queryMin(l, pos - 1),
          lmax = queryMax(l, pos - 1);
    Int64 rc = r - pos + 1, rmin = queryMin(pos, r),
          rmax = queryMax(pos, r);
    ansC[lcp] += lc * rc;
    ansM[lcp] = std::max(
        ansM[lcp], std::max(lmin * rmin, lmax * rmax));
    solve(l, pos - 1);
    solve(pos, r);
}
int main() {
    int n = read();
    scanf("%s", buf + 1);
    calcSA(n);
    for(int i = 1; i <= n; ++i) {
        int p = rk[i];
        MaxW[0][p] = MinW[0][p] = read();
    }
    buildST(n);
    memset(ansM, 0xc0, sizeof(Int64) * (n + 1));
    solve(1, n);
    for(int i = n; i >= 1; --i) {
        ansC[i - 1] += ansC[i];
        ansM[i - 1] = std::max(ansM[i - 1], ansM[i]);
    }
    for(int i = 0; i < n; ++i) {
        if(ansC[i] == 0)
            ansM[i] = 0;
        printf("%lld %lld\n", ansC[i], ansM[i]);
    }
    return 0;
}
