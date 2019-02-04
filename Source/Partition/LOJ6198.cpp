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
Key A[size], B[size];
int rk[size];
bool radixSort(int n) {
    radixSortImpl<A, B, 0>(n);
    radixSortImpl<B, A, 20>(n);
    Key lw = -1;
    int crk = 0;
    for(int i = 1; i <= n; ++i) {
        int id = A[i] >> 40;
        Key cw = A[i] & 0xffffffffff;
        if(lw != cw)
            ++crk, lw = cw;
        rk[id] = crk;
    }
    return crk == n;
}
char buf[size];
int sa[size], height[size];
void calcHeight(int n) {
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
int C[20][size], lg2[size];
int choose(int a, int b) {
    return height[a] < height[b] ? a : b;
}
void buildST(int n) {
    for(int i = 2; i <= n; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    for(int i = 1; i <= n; ++i)
        C[0][i] = i;
    for(int i = 1; i < 20; ++i) {
        int end = n - (1 << i) + 1, off = 1 << (i - 1);
        for(int j = 1; j <= end; ++j)
            C[i][j] =
                choose(C[i - 1][j], C[i - 1][j + off]);
    }
}
int getMaxPos(int l, int r) {
    int p = lg2[r - l + 1];
    return choose(C[p][l], C[p][r - (1 << p) + 1]);
}
struct Node {
    int ch[2], siz;
} T[size * 20];
int icnt = 0, root[size], maxd;
int insert(int src, int val, int d) {
    int id = ++icnt;
    T[id] = T[src];
    ++T[id].siz;
    if(d >= 0) {
        int& ch = T[id].ch[(val >> d) & 1];
        ch = insert(ch, val, d - 1);
    }
    return id;
}
int query(int b, int e, int val) {
    int res = 0;
    for(int d = maxd; d >= 0; --d) {
        int nc = ((val >> d) & 1) ^ 1;
        int nsiz =
            T[T[e].ch[nc]].siz - T[T[b].ch[nc]].siz;
        if(nsiz)
            res |= 1 << d;
        else
            nc ^= 1;
        b = T[b].ch[nc], e = T[e].ch[nc];
    }
    return res;
}
int res = 0, W[size], n;
void solve(int l, int r) {
    if(l >= r)
        return;
    int mp = getMaxPos(l + 1, r), len = height[mp];
    int ll = l, lr = mp - 1, rl = mp, rr = r;
    if(lr - ll > rr - rl) {
        std::swap(ll, rl);
        std::swap(lr, rr);
    }
    for(int i = ll; i <= lr; ++i)
        res = std::max(res, len + query(root[rl - 1],
                                        root[rr],
                                        W[sa[i]]));
    solve(ll, lr);
    solve(rl, rr);
}
int main() {
    scanf("%d%s", &n, buf + 1);
    for(int i = 1; i <= n; ++i)
        W[i] = read();
    for(int i = 1; i <= n; ++i)
        A[i] = makeKey(i, buf[i], 0);
    int off = 1;
    while(!radixSort(n)) {
        for(int i = 1; i <= n; ++i) {
            int ka = rk[i],
                kb = i + off <= n ? rk[i + off] : 0;
            A[i] = makeKey(i, ka, kb);
        }
        off <<= 1;
    }
    for(int i = 1; i <= n; ++i)
        sa[rk[i]] = i;
    calcHeight(n);
    buildST(n);
    maxd = lg2[n];
    for(int i = 1; i <= n; ++i)
        root[i] = insert(root[i - 1], W[sa[i]], maxd);
    solve(1, n);
    printf("%d\n", res);
    return 0;
}
