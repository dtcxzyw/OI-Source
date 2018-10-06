#include <algorithm>
#include <cctype>
#include <cstdio>
const int size = 1000005;
typedef long long Key;
Key makeKey(Key id, Key a, Key b) {
    return (id << 20 | a) << 20 | b;
}
template <int off>
int getKey(Key k) {
    return (k >> off) & 0xfffff;
}
int cnt[size];
template <Key* A, Key* B, int off>
void radixSortImpl(int n) {
    int maxw = 0;
    for(int i = 1; i <= n; ++i) {
        int cw = getKey<off>(A[i]);
        maxw = std::max(maxw, cw);
        ++cnt[cw];
    }
    for(int i = 1; i <= maxw; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; --i)
        B[cnt[getKey<off>(A[i])]--] = A[i];
    for(int i = 0; i <= maxw; ++i)
        cnt[i] = 0;
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
    int c, n = 0;
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
