#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 500005;
char buf[size];
struct Key {
    int id, k[2];
    Key() {}
    Key(int id, int a, int b) : id(id) {
        k[0] = a, k[1] = b;
    }
    bool operator!=(const Key& rhs) const {
        return k[0] != rhs.k[0] || k[1] != rhs.k[1];
    }
} A[size], B[size];
int rk[size], sa[size], cnt[size];
template <int b, Key* A, Key* B>
void radixSortImpl(int n) {
    int maxw = 0;
    for(int i = 1; i <= n; ++i) {
        int cw = A[i].k[b];
        maxw = std::max(maxw, cw);
        ++cnt[cw];
    }
    for(int i = 1; i <= maxw; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; --i) {
        int cw = A[i].k[b];
        B[cnt[cw]--] = A[i];
    }
    memset(cnt, 0, sizeof(int) * (maxw + 1));
}
bool radixSort(int n) {
    radixSortImpl<1, A, B>(n);
    radixSortImpl<0, B, A>(n);
    int crk = 0;
    for(int i = 1; i <= n; ++i) {
        if(A[i] != A[i - 1])
            ++crk;
        rk[A[i].id] = crk;
    }
    return crk == n;
}
void calcSA(int n) {
    int off = 1;
    while(!radixSort(n)) {
        for(int i = 1; i <= n; ++i) {
            int k = i + off <= n ? rk[i + off] : 0;
            A[i] = Key(i, rk[i], k);
        }
        off <<= 1;
    }
    for(int i = 1; i <= n; ++i)
        sa[rk[i]] = i;
}
int height[size];
void calcHeight(int n) {
    int h = 0;
    for(int i = 1; i <= n; ++i) {
        if(rk[i] == 1)
            h = 0;
        else {
            if(h)
                --h;
            int k = sa[rk[i] - 1];
            while(buf[i + h] == buf[k + h])
                ++h;
        }
        height[rk[i]] = h;
    }
}
void read(int& cnt) {
    int c;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        ++cnt;
        buf[cnt] = c;
        A[cnt] = Key(cnt, c, 0);
        c = getchar();
    }
}
bool check(int n, int lcp, int sp) {
    int end = n + 1;
    bool mins = false, maxs = false;
    for(int r = 1; r <= end; ++r) {
        if(height[r] < lcp) {
            if(mins && maxs)
                return true;
            mins = maxs = false;
        } else {
            (sa[r - 1] < sp ? mins : maxs) = true;
            (sa[r] < sp ? mins : maxs) = true;
        }
    }
    return false;
}
int main() {
    int cnt = 0;
    read(cnt);
    int asiz = cnt;
    ++cnt;
    buf[cnt] = -1;
    A[cnt] = Key(cnt, -1, 0);
    read(cnt);
    calcSA(cnt);
    calcHeight(cnt);
    int bsiz = cnt - asiz - 1;
    int l = 1, r = std::min(asiz, bsiz), ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(check(cnt, m, asiz + 1))
            ans = m, l = m + 1;
        else
            r = m - 1;
    }
    printf("%d\n", ans);
    return 0;
}
