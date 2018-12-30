#include <cctype>
#include <cstdio>
#include <cstring>
int maxi(int a, int b) {
    return a > b ? a : b;
}
const int size = 1000005;
typedef long long Key;
Key makeKey(Key a, Key b, Key c) {
    return a << 40 | b << 20 | c;
}
template <int off>
int getKey(Key k) {
    return (k >> off) & 0xfffff;
}
int cnt[size];
template <Key* A, Key* B, int off>
void radixSortImpl(int n) {
    int maxk = 0;
    for(int i = 1; i <= n; ++i) {
        int k = getKey<off>(A[i]);
        ++cnt[k];
        maxk = maxi(maxk, k);
    }
    for(int i = 1; i <= maxk; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; --i) {
        int k = getKey<off>(A[i]);
        B[cnt[k]--] = A[i];
    }
    memset(cnt, 0, sizeof(int) * (maxk + 1));
}
Key A[size], B[size];
int rk[size];
bool radixSort(int n) {
    radixSortImpl<A, B, 0>(n);
    radixSortImpl<B, A, 20>(n);
    int crk = 0;
    Key lw = 0;
    for(int i = 1; i <= n; ++i) {
        int id = A[i] >> 40;
        Key cw = A[i] & 0xffffffffff;
        if(lw != cw) {
            ++crk;
            lw = cw;
        }
        rk[id] = crk;
    }
    return crk == n;
}
int sa[size];
int main() {
    int n = 0, c;
    do
        c = getchar();
    while(!isgraph(c));
    while(isgraph(c)) {
        ++n;
        A[n] = makeKey(n, c, 0);
        c = getchar();
    }
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
    for(int i = 1; i <= n; ++i)
        printf("%d ", sa[i]);
    return 0;
}
