#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 100005;
typedef long long Key;
template <int off>
int getKey(Key k) {
    return (k >> off) & 0xfffff;
}
Key makeKey(Key id, Key a, Key b) {
    return id << 40 | a << 20 | b;
}
int maxi(int a, int b) {
    return a > b ? a : b;
}
int mini(int a, int b) {
    return a < b ? a : b;
}
Key A[size], B[size];
int cnt[size];
template <Key* A, Key* B, int off>
void radixSortImpl(int n) {
    int maxw = 0;
    for(int i = 1; i <= n; ++i) {
        int w = getKey<off>(A[i]);
        ++cnt[w];
        maxw = maxi(maxw, w);
    }
    for(int i = 1; i <= maxw; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; --i) {
        int w = getKey<off>(A[i]);
        B[cnt[w]--] = A[i];
    }
    memset(cnt, 0, sizeof(int) * (maxw + 1));
}
int rk[size];
bool radixSort(int n) {
    radixSortImpl<A, B, 0>(n);
    radixSortImpl<B, A, 20>(n);
    Key cw = -1;
    int rcnt = 0;
    for(int i = 1; i <= n; ++i) {
        int id = A[i] >> 40;
        Key w = A[i] & 0xffffffffff;
        if(cw != w)
            cw = w, ++rcnt;
        rk[id] = rcnt;
    }
    return rcnt == n;
}
int sa[size], height[size];
char buf[size];
void build(int n) {
    for(int i = 1; i <= n; ++i)
        A[i] = makeKey(i, buf[i], 0);
    int off = 1;
    while(!radixSort(n)) {
        for(int i = 1; i <= n; ++i) {
            int sec = i + off <= n ? rk[i + off] : 0;
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
        height[rk[i]] = h;
    }
}
int main() {
    int n, m;
    scanf("%d%d%s", &n, &m, buf + 1);
    build(n);
    while(m--) {
        int a = read();
        int b = read();
        int c = read();
        int d = read();
        int rc = rk[c], ans = 0,
            maxl = mini(b - a, d - c) + 1;
        int cmin = maxl;
        for(int i = rc; i >= 1 && cmin > ans; --i) {
            if(a <= sa[i] && sa[i] <= b)
                ans = maxi(ans,
                           mini(cmin, b - sa[i] + 1));
            cmin = mini(cmin, height[i]);
        }
        cmin = maxl;
        for(int i = rc + 1; i <= n && cmin > ans;
            ++i) {
            cmin = mini(cmin, height[i]);
            if(a <= sa[i] && sa[i] <= b)
                ans = maxi(ans,
                           mini(cmin, b - sa[i] + 1));
        }
        printf("%d\n", ans);
    }
    return 0;
}
