#include <cstdio>
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
const int size = 100005, mod = 998244353;
typedef long long Int64;
#define asInt64 static_cast<Int64>
const Int64 inv2 = (mod + 1) / 2;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int F[size << 2], G[size << 2], sum[size << 2],
    tag[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void update(int id, bool nleaf) {
    sum[id] = F[id];
    if(nleaf)
        sum[id] = add(sum[id], add(sum[id << 1],
                                   sum[id << 1 | 1]));
}
void color(int id, Int64 fac) {
    G[id] = (fac * G[id] + 1 - fac) % mod;
    if(G[id] < 0)
        G[id] += mod;
    tag[id] = fac * tag[id] % mod;
}
void pushDown(int id) {
    if(tag[id]) {
        color(id << 1, tag[id]);
        color(id << 1 | 1, tag[id]);
        tag[id] = 1;
    }
}
void modify(int l, int r, int id, int nl, int nr) {
    if(nl > r || nr < l) {
        F[id] = inv2 * (F[id] + G[id]) % mod;
        update(id, l < r);
    } else if(nl <= l && r <= nr) {
        F[id] = inv2 * (F[id] + 1) % mod;
        color(id, inv2);
        update(id, l < r);
    } else {
        int m = (l + r) >> 1;
        pushDown(id);
        F[id] = F[id] * inv2 % mod;
        G[id] = G[id] * inv2 % mod;
        modify(ls, nl, nr);
        modify(rs, nl, nr);
        update(id, true);
    }
}
void build(int l, int r, int id) {
    tag[id] = 1;
    if(l != r) {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
    }
}
int main() {
    int n = read();
    build(1, n, 1);
    int m = read();
    int cnt = 1;
    for(int i = 1; i <= m; ++i) {
        int op = read();
        if(op == 1) {
            int l = read();
            int r = read();
            modify(1, n, 1, l, r);
            cnt = add(cnt, cnt);
        } else
            printf("%lld\n",
                   asInt64(sum[1]) * cnt % mod);
    }
    return 0;
}
