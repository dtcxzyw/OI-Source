// TODO:3207
#include <algorithm>
#include <cstdio>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 100005;
int cnt[size << 2], div, rem;
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void build(int l, int r, int id) {
    if(l == r)
        cnt[id] = div + (l <= rem);
    else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        cnt[id] = std::max(cnt[id << 1], cnt[id << 1 | 1]);
    }
}
int pos[size];
Int64 foo() {
    int n, s, q, p, m, d;
    scanf("%d%d%d%d%d%d", &n, &s, &q, &p, &m, &d);
    div = n / d, rem = n % d;
    build(0, d - 1, 1);
    Int64 c = 0;
    for(int i = 1; i < n; ++i) {
        c = (c * q + p) % m;
    }
    return 0;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--)
        printf("%lld\n", foo());
    return 0;
}
