#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
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
Key makeKey(Key id, Key a, Key b) {
    return id << 40 | a << 20 | b;
}
template <int off>
int getKey(Key id) {
    return (id >> off) & 0xfffff;
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
        if(cw != lw) {
            lw = cw;
            ++crk;
        }
        rk[id] = crk;
    }
    return crk == n;
}
int sa[size], height[size];
char str[size];
void calcSA(int n) {
    std::reverse(str + 1, str + n + 1);
    for(int i = 1; i <= n; ++i)
        A[i] = makeKey(i, str[i], 0);
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
            while(str[i + h] == str[k + h])
                ++h;
        }
        height[rk[i]] = h;
    }
}
int H[17][size], lg2[size];
void buildST(int n) {
    for(int i = 1; i <= n; ++i)
        H[0][i] = height[i];
    for(int i = 2; i <= n; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    for(int i = 1; i < 17; ++i) {
        int end = n - (1 << i) + 1, off = 1 << (i - 1);
        for(int j = 1; j <= end; ++j)
            H[i][j] = std::min(H[i - 1][j],
                               H[i - 1][j + off]);
    }
}
int query(int l, int r) {
    int p = lg2[r - l + 1];
    return std::min(H[p][l], H[p][r - (1 << p) + 1]);
}
std::set<int> pos;
typedef std::set<int>::iterator IterT;
void insert(int p, int& ans) {
    p = rk[p];
    IterT it = pos.insert(p).first;
    IterT pre = it, nxt = it;
    if(pre != pos.begin())
        ans = std::max(ans, query((*--pre) + 1, p));
    if(++nxt != pos.end())
        ans = std::max(ans, query(p + 1, *nxt));
}
int queryBlock(int l, int r, int ans) {
    for(int i = l; i <= r; ++i)
        insert(i, ans);
    for(int i = l; i <= r; ++i)
        pos.erase(rk[i]);
    return ans;
}
int bid[size];
struct Query {
    int l, r, id;
    bool operator<(const Query& rhs) const {
        return bid[l] == bid[rhs.l] ? r < rhs.r :
                                      l < rhs.l;
    }
} Q[size];
int ans[size];
int main() {
    int n = read();
    int m = read();
    scanf("%s", str + 1);
    calcSA(n);
    buildST(n);
    int end = n + 1;
    for(int i = 1; i <= m; ++i) {
        Q[i].id = i;
        int l = read();
        int r = read();
        Q[i].l = end - r;
        Q[i].r = end - l;
    }
    int bsiz = sqrt(1.0 * n * n / m) + 1;
    for(int i = 1; i <= n; ++i)
        bid[i] = i / bsiz;
    std::sort(Q + 1, Q + m + 1);
    int cans = 0;
    for(int i = 1, cr, bend; i <= m; ++i) {
        if(i == 1 || bid[Q[i].l] != bid[Q[i - 1].l]) {
            pos.clear();
            cans = 0;
            cr = (bid[Q[i].l] + 1) * bsiz;
            bend = cr - 1;
        }
        while(cr <= Q[i].r)
            insert(cr++, cans);
        ans[Q[i].id] = queryBlock(
            Q[i].l, std::min(Q[i].r, bend), cans);
    }
    for(int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
