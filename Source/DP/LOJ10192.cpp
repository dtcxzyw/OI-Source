#include <algorithm>
#include <cstdio>
typedef long long Int64;
Int64 read() {
    Int64 res = 0;
    int c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int size = 200005;
const Int64 inf = 1LL << 60;
Int64 w[size], d[size], sd[size], f[size], g[size];
void solve(int l, int r, int b, int e, Int64 sw,
           Int64 sf) {
    if(l > r)
        return;
    int m = (l + r) >> 1, end = std::min(e, m), tp;
    Int64 csw = sw, csf = sf;
    for(int i = l; i <= m; ++i) {
        csf += csw * d[i];
        csw += w[i];
    }
    Int64 nsw = csw, nsf = csf, minv = inf;
    for(int i = b; i <= end; ++i) {
        Int64 val = f[i - 1] + csf;
        if(val < minv)
            minv = val, tp = i;
        csw -= w[i];
        csf -= w[i] * (sd[m] - sd[i]);
    }
    g[m] = minv;
    solve(l, m - 1, b, tp, sw, sf);
    for(int i = b; i < tp; ++i) {
        nsw -= w[i];
        nsf -= w[i] * (sd[m] - sd[i]);
    }
    solve(m + 1, r, tp, e, nsw, nsf);
}
int main() {
    int n = read() + 1;
    Int64 sw = 0;
    for(int i = 1; i < n; ++i) {
        w[i] = read();
        d[i + 1] = read();
        sd[i + 1] = sd[i] + d[i + 1];
        f[i] = f[i - 1] + sw * d[i];
        sw += w[i];
    }
    f[n] = f[n - 1] + sw * d[n];
    solve(1, n, 1, n, 0, 0);
    Int64 res = inf, csf = 0, csd = 0;
    for(int i = n; i >= 1; --i) {
        csd += d[i + 1];
        csf += w[i] * csd;
        res = std::min(res, g[i - 1] + csf);
    }
    printf("%lld\n", res);
    return 0;
}
