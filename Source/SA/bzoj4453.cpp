#include <algorithm>
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
typedef long long Int64;
Int64 makeKey(Int64 id, Int64 a, Int64 b) {
    return id << 40 | a << 20 | b;
}
template <int off>
int getKey(Int64 key) {
    return (key >> off) & 0xfffff;
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
int rk[size];
bool radixSort(int n) {
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
int sa[size], height[size];
void buildSA(int n) {
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
    for(int i = 1, h = 0; i <= n; ++i) {
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
int ilg2[size], S[17][size];
void buildST(int n) {
    memcpy(S[0] + 1, height + 1, sizeof(int) * n);
    for(int i = 2; i <= n; ++i)
        ilg2[i] = ilg2[i >> 1] + 1;
    for(int i = 1; i <= 16; ++i) {
        int end = n - (1 << i) + 1, off = 1 << (i - 1);
        for(int j = 1; j <= end; ++j)
            S[i][j] = std::min(S[i - 1][j],
                               S[i - 1][j + off]);
    }
}
int query(int l, int r) {
    int p = ilg2[r - l + 1];
    return std::min(S[p][l], S[p][r - (1 << p) + 1]);
}
int getLCP(int a, int b) {
    a = rk[a], b = rk[b];
    if(a > b)
        std::swap(a, b);
    return query(a + 1, b);
}
struct Query {
    int l, r, id;
    bool operator<(const Query& rhs) const {
        return l < rhs.l;
    }
} Q[size];
int ans[size];
struct Range {
    int val, l;
} st[size];
int find(int top, int pos) {
    int l = 1, r = top, ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(st[m].l <= pos)
            r = m - 1, ans = st[m].val;
        else
            l = m + 1;
    }
    return ans;
}
int main() {
    scanf("%s", buf + 1);
    int n = strlen(buf + 1);
    buildSA(n);
    buildST(n);
    int q;
    scanf("%d", &q);
    for(int i = 1; i <= q; ++i) {
        scanf("%d%d", &Q[i].l, &Q[i].r);
        Q[i].id = i;
    }
    std::sort(Q + 1, Q + q + 1);
    int top = 0;
    st[0].l = n + 1;
    for(int i = n, j = q; i >= 1; --i) {
        while(top &&
              (rk[i] > rk[st[top].val] ||
               st[top].val + getLCP(i, st[top].val) >=
                   st[top - 1].l))
            --top;
        if(top)
            st[top].l =
                st[top].val + getLCP(i, st[top].val);
        ++top;
        st[top].val = st[top].l = i;
        while(j >= 1 && Q[j].l == i) {
            ans[Q[j].id] = find(top, Q[j].r);
            --j;
        }
    }
    for(int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
