#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 300005, maxS = size * 2, inf = 1 << 30;
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
struct Nan {};
class Info {
   private:
    int max1, max2, min1, min2;
    void updateMax(int x) {
        max2 = std::max(max2, x);
        if (max2 > max1) std::swap(max1, max2);
    }
    void updateMin(int x) {
        min2 = std::min(min2, x);
        if (min2 < min1) std::swap(min1, min2);
    }

   public:
    Info() {}
    Info(int x) : max1(x), max2(-inf), min1(x), min2(inf) {}
    void update(const Info &rhs) {
        updateMax(rhs.max1);
        updateMax(rhs.max2);
        updateMin(rhs.min1);
        updateMin(rhs.min2);
    }
    Int64 calcMaxv() const {
        Int64 a = asInt64(max1) * max2;
        Int64 b = asInt64(min1) * min2;
        return a > b ? a : b;
    }
    static Info nan() {
        Info res;
        res.max1 = res.max2 = -inf;
        res.min1 = res.min2 = inf;
        return res;
    }
};
struct SAM {
    struct State {
        int len, link, cnt, nxt[26];
        Info info;
    } st[maxS];
    int siz, last;
    SAM() {
        siz = last = 1;
    }
    void extend(int c, int w) {
        int id = ++siz;
        st[id].len = st[last].len + 1;
        st[id].info = Info(w);
        st[id].cnt = 1;
        int p = last;
        while (p && !st[p].nxt[c]) {
            st[p].nxt[c] = id;
            p = st[p].link;
        }
        if (p) {
            int q = st[p].nxt[c];
            if (st[p].len + 1 == st[q].len)
                st[id].link = q;
            else {
                int cq = ++siz;
                st[cq] = st[q];
                st[cq].info = Info::nan();
                st[cq].cnt = 0;
                st[cq].len = st[p].len + 1;
                while (p && st[p].nxt[c] == q) {
                    st[p].nxt[c] = cq;
                    p = st[p].link;
                }
                st[q].link = st[id].link = cq;
            }
        } else
            st[id].link = 1;
        last = id;
    }
    int lcnt[size], q[maxS];
    Int64 cnt[size], maxv[size];
    void solve(int n) {
        for (int i = 1; i <= siz; ++i) ++lcnt[st[i].len];
        for (int i = 1; i <= n; ++i) lcnt[i] += lcnt[i - 1];
        for (int i = siz; i >= 1; --i) q[lcnt[st[i].len]--] = i;

        memset(maxv, 0xc0, sizeof(Int64) * (n + 1));

        for (int i = siz; i >= 1; --i) {
            int u = q[i];
            int siz = st[u].cnt;
            int len = st[u].len;
            int fa = st[u].link;
            if (siz > 1) {
                Int64 ucnt = asInt64(siz - 1) * siz / 2;
                cnt[len] += ucnt;
                if (fa) cnt[st[fa].len] -= ucnt;
                maxv[len] = std::max(maxv[len], st[u].info.calcMaxv());
            }
            st[fa].cnt += st[u].cnt;
            st[fa].info.update(st[u].info);
        }

        for (int i = n - 1; i >= 0; --i) cnt[i] += cnt[i + 1];
        for (int i = n - 1; i >= 0; --i) maxv[i] = std::max(maxv[i], maxv[i + 1]);
        for (int i = 0; i < n; ++i) {
            Int64 a = cnt[i];
            Int64 b = a ? maxv[i] : 0;
            printf("%lld %lld\n", a, b);
        }
    }
} sam;
char buf[size];
int A[size];
int main() {
    int n;
    scanf("%d%s", &n, buf + 1);
    for (int i = 1; i <= n; ++i) A[i] = read();
    for (int i = n; i >= 1; --i) sam.extend(buf[i] - 'a', A[i]);
    sam.solve(n);
    return 0;
}
