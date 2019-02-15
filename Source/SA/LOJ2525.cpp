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
int mini(int a, int b) {
    return a < b ? a : b;
}
int maxi(int a, int b) {
    return a > b ? a : b;
}
const int maxn = 100005, size = 2 * maxn, block = 50;
char buf[size];
typedef long long Int64;
namespace SA {
    template <int off>
    int getKey(Int64 x) {
        return (x >> off) & 0xfffff;
    }
    Int64 makeKey(Int64 id, Int64 a, Int64 b) {
        return id << 40 | a << 20 | b;
    }
    int cnt[size];
    template <Int64* A, Int64* B, int off>
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
    Int64 A[size], B[size];
    bool radixSort(int n) {
        radixSortImpl<A, B, 0>(n);
        radixSortImpl<B, A, 20>(n);
        int crk = 0;
        Int64 lw = -1;
        for(int i = 1; i <= n; ++i) {
            int id = A[i] >> 40;
            Int64 cw = A[i] & 0xffffffffff;
            if(lw != cw) {
                lw = cw;
                ++crk;
            }
            rk[id] = crk;
        }
        return crk == n;
    }
    int sa[size], height[size];
    void calcSA(int n) {
        for(int i = 1; i <= n; ++i)
            A[i] = makeKey(i, buf[i], 0);
        int off = 1;
        while(!radixSort(n)) {
            for(int i = 1; i <= n; ++i) {
                int bk =
                    i + off <= n ? rk[i + off] : 0;
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
}  // namespace SA
namespace LCP {
    int C[20][size], lg2[size], siz;
    void buildST(int n) {
        siz = n;
        memcpy(C[0] + 1, SA::height + 1,
               sizeof(int) * n);
        for(int i = 2; i <= n; ++i)
            lg2[i] = lg2[i >> 1] + 1;
        for(int i = 1; i < 20; ++i) {
            int end = n - (1 << i) + 1,
                off = 1 << (i - 1);
            for(int j = 1; j <= end; ++j)
                C[i][j] = mini(C[i - 1][j],
                               C[i - 1][j + off]);
        }
    }
    int query(int l, int r) {
        int p = lg2[r - l + 1];
        return mini(C[p][l], C[p][r - (1 << p) + 1]);
    }
    int queryLpos(int pos, int len) {
        int l = 1, r = pos - 1, ans = pos;
        while(l <= r) {
            int m = (l + r) >> 1;
            if(query(m + 1, pos) >= len)
                ans = m, r = m - 1;
            else
                l = m + 1;
        }
        return ans;
    }
    int queryRpos(int pos, int len) {
        int l = pos + 1, r = siz, ans = pos;
        while(l <= r) {
            int m = (l + r) >> 1;
            if(query(pos + 1, m) >= len)
                ans = m, l = m + 1;
            else
                r = m - 1;
        }
        return ans;
    }
}  // namespace LCP
namespace SegTree {
    struct Node {
        int l, r, siz;
    } T[maxn * 20];
    int tcnt = 0, root[size];
    int insert(int l, int r, int src, int p) {
        int id = ++tcnt;
        T[id] = T[src];
        ++T[id].siz;
        if(l != r) {
            int m = (l + r) >> 1;
            if(p <= m)
                T[id].l = insert(l, m, T[id].l, p);
            else
                T[id].r = insert(m + 1, r, T[id].r, p);
        }
        return id;
    }
    int tsiz;
    void build(int siz, int n) {
        tsiz = n;
        for(int i = 1; i <= siz; ++i)
            if(SA::sa[i] <= n)
                root[i] = insert(1, n, root[i - 1],
                                 SA::sa[i]);
            else
                root[i] = root[i - 1];
    }
    int queryImpl(int l, int r, int a, int b, int lp) {
        if(T[a].siz == T[b].siz)
            return 0;
        if(l == r)
            return l;
        int m = (l + r) >> 1, res;
        if(lp <= m &&
           (res = queryImpl(l, m, T[a].l, T[b].l, lp)))
            return res;
        return queryImpl(m + 1, r, T[a].r, T[b].r, lp);
    }
    int query(int l, int r, int lp) {
        return queryImpl(1, tsiz, root[l - 1], root[r],
                         lp);
    }
}  // namespace SegTree
struct Query {
    int id, s, t, lp, rp, len;
    bool operator<(const Query& rhs) const {
        return len == rhs.len ? lp < rhs.lp :
                                len < rhs.len;
    }
} Q[maxn];
Int64 ans[maxn];
int pos[maxn], nxt[20][maxn];
Int64 sum[20][maxn];
int rebuild(int n, int k, int len, int l, int r) {
    int cnt = 0;
    for(int i = l; i <= r; ++i)
        if(SA::sa[i] <= n)
            pos[++cnt] = SA::sa[i];
    std::sort(pos + 1, pos + cnt + 1);
    pos[0] = pos[cnt + 1] = 1 << 30;
    for(int i = 1, id = 1; i <= cnt; ++i) {
        while(pos[i] + len > pos[id])
            ++id;
        nxt[0][i] = (id == cnt + 1 ? 0 : id);
        sum[0][i] = k - pos[i];
    }
    int d = LCP::lg2[cnt];
    for(int i = 1; i <= d; ++i) {
        int end = cnt - (1 << i) + 1;
        for(int j = 1; j <= end; ++j) {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
            sum[i][j] = sum[i - 1][j] +
                sum[i - 1][nxt[i - 1][j]];
        }
        memset(nxt[i] + end + 1, 0,
               sizeof(int) * (cnt - end));
        memset(sum[i] + end + 1, 0,
               sizeof(Int64) * (cnt - end));
    }
    return cnt;
}
void solveShort(int n, int k, int len, int& cur) {
    if(Q[cur].len != len)
        return;
    int cnt = 0, d = 0;
    for(; Q[cur].len == len; ++cur) {
        if(Q[cur].lp == Q[cur].rp)
            continue;
        if(Q[cur].len != Q[cur - 1].len ||
           Q[cur].lp != Q[cur - 1].lp) {
            int l = Q[cur].lp, r = Q[cur].rp;
            cnt = rebuild(n, k, len, l, r);
            d = LCP::lg2[cnt];
        }
        int id =
            std::lower_bound(pos + 1, pos + cnt + 1,
                             Q[cur].s) -
            pos;
        if(pos[id] > Q[cur].t)
            continue;
        Int64 res = 0;
        for(int i = d; i >= 0; --i) {
            int nid = nxt[i][id];
            if(pos[nid] <= Q[cur].t) {
                res += sum[i][id];
                id = nid;
            }
        }
        ans[Q[cur].id] = res + sum[0][id];
    }
}
int main() {
    int n = read();
    int k = read();
    scanf("%s", buf + 1);
    buf[n + 1] = '@';
    scanf("%s", buf + n + 2);
    int siz = 2 * n + 1;
    SA::calcSA(siz);
    LCP::buildST(siz);
    int q = read();
    for(int i = 1; i <= q; ++i) {
        Q[i].id = i;
        Q[i].s = read();
        Q[i].t = read();
        int l = read();
        int r = read();
        int len = r - l + 1;
        int rkl = SA::rk[n + 1 + l];
        Q[i].lp = LCP::queryLpos(rkl, len);
        Q[i].rp = LCP::queryRpos(rkl, len);
        Q[i].len = len;
        Q[i].t -= len - 1;
    }
    std::sort(Q + 1, Q + q + 1);
    int cur = 1;
    for(int i = 1; i <= block && cur <= q; ++i)
        solveShort(n, k, i, cur);
    SegTree::build(siz, n);
    for(int i = cur; i <= q; ++i) {
        int lp = Q[i].s;
        Int64 res = 0;
        while(true) {
            lp = SegTree::query(Q[i].lp, Q[i].rp, lp);
            if(lp == 0 || lp > Q[i].t)
                break;
            res += k - lp;
            lp += Q[i].len;
        }
        ans[Q[i].id] = res;
    }
    for(int i = 1; i <= q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
