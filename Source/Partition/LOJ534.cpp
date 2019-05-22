#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int size = 15005;
int n, maxv, t, d, dp[20][size];
typedef std::pair<int, int> Item;
std::vector<Item> item[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void insert(int l, int r, int id, int nl, int nr,
            const Item& it) {
    if(nl <= l && r <= nr)
        item[id].push_back(it);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert(ls, nl, nr, it);
        if(m < nr)
            insert(rs, nl, nr, it);
    }
}
void solve(int l, int r, int id, int dep) {
    if(item[id].size()) {
        ++dep;
        memcpy(dp[dep], dp[dep - 1],
               sizeof(int) * maxv);
        int* cdp = dp[dep];
        for(Item it : item[id]) {
            int v = it.first, w = it.second;
            for(int i = maxv; i >= v; --i)
                cdp[i] =
                    std::max(cdp[i], cdp[i - v] + w);
        }
    }
    if(l == r) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int v, w, e;
            scanf("%d%d%d", &v, &w, &e);
            v -= d, w -= d, e -= d;
            if(l < e)
                insert(1, n, 1, l + 1, e, Item(v, w));
        } else {
            int v;
            scanf("%d", &v);
            v -= d;
            int res = dp[dep][v];
            if(res >= 0) {
                printf("1 %d\n", res);
                if(t)
                    d = res ^ 1;
            } else
                puts("0 0"), d = 0;
        }
    } else {
        int m = (l + r) >> 1;
        solve(ls, dep);
        solve(rs, dep);
    }
}
int main() {
    scanf("%d%d%d", &n, &maxv, &t);
    ++maxv;
    memset(dp, 0xc0, sizeof(dp));
    dp[0][0] = 0;
    solve(1, n, 1, 0);
    return 0;
}
